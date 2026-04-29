#include "App.h"
#include "utilityFunc.h"
#include <tabulate/table.hpp>
#include <sstream>
#include <thread>
#include <winsock2.h> //socket library
#include <ws2tcpip.h> //needed for ipv6
#include <string> //required for string comparison
// Source - https://stackoverflow.com/a/2340697
// Posted by Yacoby, modified by community. See post 'Timeline' for change history
// Retrieved 2026-04-22, License - CC BY-SA 3.0
#include <ctype.h>
#include "FormContainer.h"
#include "Group.h"
#include <nlohmann/json.hpp>

using namespace tabulate;
using namespace std;


//construct an app holding a set of group managers with their projectID's and names of projects they are managing
/*
projID
1 = 86!
2 = Frission
3 = Desk Drawer
*/
App::App(string* projects, int numProj){
    // construct and assign two threads as the designated client threads of the APP. These two will perform the work
    // https://en.cppreference.com/cpp/thread/thread/thread
    this->_currProtocol = -1;
    this->_clientSocket = INVALID_SOCKET;
    this->_connected = false;
    this->_paused = true;
    this->_alive = true;


    this->_IPv4serverAddress = {};
    this->_IPv6serverAddress = {};

    for(int i = 0; i < numProj; i++){
        GroupManager manager = GroupManager(i+1, projects[i]); //create a set of group managers with their projectIds and names. add to the vector.
        _managers.push_back(manager);
    }
    ///////////////////////////////

    this->_arduinoListening = true; // *** ADDED
    

}

App::~App(){ // *** ADDED
    stopArduino();
    disconnect(); // *** ADDED: ensure socket thread is also cleaned up
}

void App::displayOptions(){
    cout << "=============================================" << endl;
    cout << "  CLI CONTROL INTERFACE" << endl;
    cout << "=============================================" << endl;
    cout << "  STATUS" << endl;
    cout << "    1. Program status" << endl; //frontend table library
    cout << "    2. Group manager status  <manager_id>" << endl; //done
    cout << "    3. Check connection status" << endl; //done
    cout << "---------------------------------------------" << endl;
    cout << "  PARSING" << endl;
    cout << "    4. Send Signal (s = start parse or p = pause parse)" << endl; //userSendStream, done
    cout << "    5. Send confirmation to Java parser" << endl; //sendConfirmation
    cout << "---------------------------------------------" << endl;
    cout << "  SERVERS" << endl;
    cout << "    6. Connect to Java server  <host> <port> <IP Protocol>" << endl;
    cout << "    7. Reconnect to Java server" << endl;
    cout << "    8. Disconnect from Java server" << endl;
    cout << "---------------------------------------------" << endl;
    cout << "    9. Pop from project queue  <project_id>" << endl; //done
    cout << "    10. Show all active groups <project_id>" << endl; //done? i think?
    cout << "    11. Exit program" << endl; //done? i think?
    cout << "    12. Start Arduino Listener" << endl; 
    cout << "    13. Stop Arduino Listener" << endl; 
    cout << "=============================================" << endl;
    cout << "Enter command number: ";
}

void App::handle(string input){
    stringstream ss(input);
    string token;
    vector<string> tokens;
    while(ss >> token){
        tokens.push_back(token);
    }
    if(tokens.size() == 0){
        cout << "! Invalid command" << endl;
        return;
    }

    try{
        int command = stoi(tokens[0]);
        if(command == 1){
            programStatus();
        } else if(command == 2){
            if(tokens.size() < 2){
                cout << "! Invalid command: missing manager_id" << endl;
                return;
            }
            string manager_id = tokens[1];
            groupManagerStatus(stoi(manager_id));
        } else if(command == 3){
            cout << "Connected: " << boolalpha << isConnected() << endl;
        } else if(command == 4){
            if(tokens.size() < 2){
                cout << "! Invalid command: missing s or p" << endl;
                return;
            }
            string cmd = tokens[1];
            userSendStream(cmd);
        } else if(command == 5){
            if(tokens.size() < 2){
                cout << "! Invalid command: missing msgID" << endl;
                return;
            }
            sendConfirmation(stoi(tokens[1]));
        } else if(command == 6){
            if(tokens.size() < 4){
                cout << "! Invalid command: need hostIP, port number, protocol" << endl;
                return;
            }
            connectToJavaServer(tokens[1], stoi(tokens[2]), tokens[3]);
        } else if(command == 7){
            reconnect();
        } else if(command == 8){
            disconnect();
        } else if(command == 9){
            if(tokens.size() < 2){
                cout << "! Invalid command: missing project_id" << endl;
                return;
            }
            pop(stoi(tokens[1]));
        } else if(command == 10){
            if(tokens.size() < 2){
                cout << "! Invalid command: missing manager_id" << endl;
                return;
            }
            showActiveGroups(stoi(tokens[1]));
        } else if(command == 11){
            exit(0);
        }else if(command == 12){ // *** ADDED
            startArduino();
        }else if(command == 13){ // *** ADDED
            stopArduino();
        } else {
            cout << "Invalid command" << endl;
            return;
        }
    }
    catch(const exception& e){
        cout << "! Detected invalid input: Please check your input and enter numeric values for commands and IDs." << endl;
        return;
    }
    return;
} 

void App::pop(int project_id){  
    for (int i = 0; i < _managers.size(); i++){
        if (_managers[i].getProjectId() == project_id){
            Group poppedGroup = _managers[i].popGroup();
            if (poppedGroup._validObj == false){
                return;
            }
            printGroup(poppedGroup);
            return;
        }
    }

    cout << "! No GroupManager for projectID: " << project_id << " found" << endl;
    return;
}

void App::showActiveGroups(int project_id){
    for(int i = 0; i < _managers.size(); i++){
        if(_managers[i].getProjectId() == project_id){
            vector<Group> activeGroups = _managers[i].getActiveGroups();
            cout << "For Project: " << _managers[i].getProjectName() << endl;
            for(int j = 0; j < activeGroups.size(); j++){
                printGroup(activeGroups[j]);
            }
        }
    }
}

/*** THE RULE OF THUMB IS THAT UPON CONNECTION TO SERVER, BEGIN LSITENING FOR DATA BY STARTING RECEIVESTREAM THREAD */
bool App::attemptConnection(int IPprotocol, struct sockaddr* addr, size_t addrLen){
    if(this->_clientSocket != INVALID_SOCKET){  //if the client is already connected, 
        disconnect();
    }

    this->_clientSocket = socket(IPprotocol, SOCK_STREAM, 0);
    if(this->_clientSocket == INVALID_SOCKET){
        this->_connected = false;
        return false;
    }

    int connectTest = connect(this->_clientSocket, addr, addrLen);
    if(connectTest == SOCKET_ERROR){
        closesocket(this->_clientSocket);
        this->_clientSocket = INVALID_SOCKET;
        this->_connected = false;
        return false;
    }

    this->_connected = true;
    return true;
}

void App::connectToJavaServer(string hostIP, int portNumber, string protocol){
    if(_connected == true){
        cout << "! Already connected to a server host! Please disconnected before connecting." << endl;
        return;
    }
    //we will be using ipv6 for local connections, and ipv4 for outside network connections
    //because we are connecting to a java program on a local or remote device, the host ip, it's protocol, and port is known

    // The following was devised using 
    // https://medium.com/@smumtaz.bscs24seecs/setting-up-a-client-and-server-using-c-sockets-c3ddbc1742f8 and
    // the man pages of socket documentation @ https://beej.us/guide/bgnet/html/#man-pages

    // create client socket on domain AF_INET or AF_INET6, type SOCK_STREAM for TCP streams, protocol 0 to autoset protocol
    //https://beej.us/guide/bgnet/html/#socketman
    int connectMode = parseProtocol(protocol);
    if(connectMode == -1){
        cout << "! Bad protocol" << endl;
        return;
    }
    //specifying the address we are setting up the temporary data to feed to and be used by the OS once we call connect()
    //These will tell the OS the necessary protocols and info to be used to connect to the destination
    //Think of them like a buffer value
    /*
        for learning sake, say that we are given a HOSTNAME like "google.com" and a port. 
        This hostname is ambiguous, it is not clear what protocol it is. It could also be a host name that map to multiple IP addresses either ipv6 or ipv4 (which it is)
        We would need to loop through all possible IP's under this host that are currently listening on the specified port until we find the right connection
        in this scenario, use getaddrinfo()
            getaddrinfo() supports both IPv4 and IPv6 protocols 
        see getaddrinfo() here: https://beej.us/guide/bgnet/html/#getaddrinfoman
        
        in our case, the public IP the server is being hosted on is known ahead of time. the port is also known as well. there is no need for looping thru all possible ips
        we can simply directly tell the OS the destination the socket will connect to. 
        -> HOWEVER, let's say that the public IP is a different network, as if the device is on a network like maybe at a different location
            -> There could be some issues with routing/port forwarding/CGNAT so/firewalls/etc this is option function may not work in this scenario
    */
    
    //https://beej.us/guide/bgnet/html/#structsockaddrman
    bool isConnected = false;
    if(connectMode == AF_INET){
        //if IPv4
        //grab IPv4 Public Address for hostIP
        this->_currProtocol = AF_INET;
        this->_IPv4serverAddress = IPv4SpecifiedDestination(hostIP, portNumber);
        isConnected = attemptConnection(connectMode, (struct sockaddr *)&_IPv4serverAddress, sizeof(_IPv4serverAddress));
    }
    else if(connectMode == AF_INET6){
        //if IPv6,
        //typically, we will run the parser on the same device, so grab the local-link ipv6 for hostIP
        this->_currProtocol = AF_INET6;
        this->_IPv6serverAddress = IPv6SpecifiedDestination(hostIP, portNumber);
        isConnected = attemptConnection(connectMode, (struct sockaddr *)&_IPv6serverAddress, sizeof(_IPv6serverAddress));
    }
    if(isConnected == false){
        cout << "! Failed to connect, please input valid host IP, port number, and protocol";
        return;
    }

    startReceiveThread();
    return;
}

void App::reconnect(){
    disconnect();
    if(this->_currProtocol == -1){
        cout << "! There is no previous connection to reconnect to" << endl;
        return;
    }

    bool isConnected = false;
    if(this->_currProtocol == AF_INET){
        isConnected = attemptConnection(this->_currProtocol, (struct sockaddr *)&_IPv4serverAddress, sizeof(_IPv4serverAddress));
    }
    else if(this->_currProtocol == AF_INET6){
        isConnected = attemptConnection(this->_currProtocol, (struct sockaddr *)&_IPv6serverAddress, sizeof(_IPv6serverAddress));
    }
    if(isConnected == false){
        cout << "! Reconnect failed, please check host IP, port number, and protocol" << endl;
        this->_connected = false;
        return;
    }
    this->_connected = true;
    startReceiveThread();
    return;
}

void App::disconnect(){
    //shut down the connection, kill recievethread by joining, Close the socket
    //this order of disconnecting is important to prevent undefined behavior.
    if(this->_connected == false){ cout << "! Already disconnected!" << endl;}
    this->_paused = true;
    this->_connected = false;    
    this->_alive = false;
    if (_clientSocket != INVALID_SOCKET) {
    // wakes recv() called in receivingStream(), tells it to stop blocking _receiveThread() while waiting to receive data.
    // (Recieve could be waiting for another stream and blocks the thread until it gets something)
    // calling disconnect() without properly stopping recv from "listening" will cause a deadlock where 
    // the thread calling disconenct() waits for recv to finish listening but it never does.
        shutdown(_clientSocket, SD_BOTH);
        if (_receiveThread.joinable()){_receiveThread.join(); }
        closesocket(_clientSocket);
        this->_clientSocket = INVALID_SOCKET;
    }
    return;
}

void App::receivingStream(){
    char buffer_recv[1024] ;
    int byte_count;
    string builtJsonString;
    size_t pos = string::npos;
    string extractString;
    int confirmID;
    ns::FormContainer fc;
    int currentclientSocket = this->_clientSocket;
    if (currentclientSocket == INVALID_SOCKET) return;
    while((this->_alive == true) && (this->_connected == true) ){
        if(this->_paused == true){
            Sleep(100);
            continue;
        }
        byte_count = recv(currentclientSocket, buffer_recv, sizeof(buffer_recv)-1, 0);
        if(byte_count == -1){ 
            cout << "! Error within receive stream. Disconnecting and pausing parse... please reconnect again" << endl;
            this->_alive = false;
            this->_connected = false;
            // hi check this error messge//check for _connected, call disconnect() within main thread
            return;
        }
        else if(byte_count == 0){ 
            cout << "! Connected server has closed! Disconnecting and pausing parse... please reconnect again" << endl;
            this->_alive = false;
            this->_connected = false;
            // hi check this error messge//check for _connected, call disconnect() within MAIN thread
            return;
        }

        builtJsonString.append(buffer_recv, byte_count);
        //It is possible to recieve fragmented data such that the first loop does not contain a full json string. 
        //So we much check for \n in multiple loops
        while((pos = builtJsonString.find('\n')) != string::npos){
            //find() should return the index of the first occurence of "\n" which we will denote as the end of a json string send by the java parser
            //otherwise it will return string::npos if no char is found
            //we will extract this json string
            extractString = builtJsonString.substr(0, pos);
            builtJsonString.erase(0, pos+1);
            
            try{
                fc = this->CParser.parseJsonString(extractString);
            }
            catch(...){ //catch all exceptions syntax: if json::parse throws for any reason, we can safely assume this is bad data and we skip it
                continue;
            }



            if(!fc.getFullName().empty() && !fc.getPrimaryNumber().empty()){
                //create new group, add to corresponding groupmanager
                Group newGroup = this->CParser.convertFormContainerToGroup(fc);
                for(int i = 0; i < this->_managers.size(); i++){
                    if(_managers[i].getProjectId() == newGroup.getProjectID()){
                        this->_managers[i].addGroup(newGroup);
                        break;
                    }
                }
            }
            else if(fc.getFullName().empty() || fc.getPrimaryNumber().empty()) { //skip bad data
                continue;
            }
            if(fc.getMsgID() >= 0){
                confirmID = fc.getMsgID();
                sendConfirmation(confirmID);
            }
        }        
    }

    //when paused/not alive anymore, the thread will finish work and die. Ensure that upon unpausing, threads are constructed once again
    return;
}

void App::startReceiveThread() {
    this->_alive = false; //pause execution of this curr Receivethread, so that it can exit
    if (_receiveThread.joinable()){ 
        /*
            ensure the thread is joinable before we start/construct a new thread
            have the main thread wait until the current _recieveThread finishes it's execution (receivingStream()) before joining it and reassigning _receiveThread 
            to a new execution.
            if you do not join before starting and reassigning a new one,
                CPP documentation states that it will call std::terminate() on the program
                once the old execution that is without a threadobject finishes
        */
        _receiveThread.join();
    }
    this->_alive = true;
    this->_paused = false;
    this->_receiveThread = thread(&App::receivingStream, this); 
        //cite: https://en.cppreference.com/cpp/thread/thread/thread
        //example: std::thread t5(&foo::bar, &f); // t5 runs foo::bar() on object f
}

////there will be two valid types of user defined that can be sent, a pause parser command (p), a start parser command(s)
void App::userSendStream(string cmd){
    string message = cmd;
    // if(message.empty() == true && (message.size() > 1)){
    //     cout << "! Empty command, type a valid command" << endl;
    //     return;   
    // } check is implemented in handle functinon already, also this is wrong lol 
    if( message[0] == 'p'){
        this->_paused = true;
    }
    else if(message[0] == 's'){
        if(this->_connected == false){
            this->_paused = true;
            cout << "! No connecion to the JAVA parser found! Please connected before starting CPP parser" << endl;
            return;
        }
        this->_paused = false;
        

    }
    else{ cout << "! Unrecognized command, please enter a valid cmd" << endl; return;}

    if(this->_clientSocket == INVALID_SOCKET){
        cout << "! No connected server to send command to. Please connect to a server" << endl;
        return;
    }
    message.append("\n");
    
    if(sendWholeMessage(this->_clientSocket, message) == false){ cout << "! Could not send command: " << message << endl; return;}
    else{cout << "! Internal CMD sent Sucessfully" << endl;}
    return;
}

//internal command to confirm recieved JSON string is parsed in the format "c-msgID"
void App::sendConfirmation(int ID){
    
    string message = "c-" + to_string(ID);

    if(this->_clientSocket == INVALID_SOCKET){
        cout << "! No connected server to send command to. Please connect to a server" << endl;
        return;
    }
    message.append("\n");
    if(sendWholeMessage(this->_clientSocket, message) == false){cout << "! Could not send confirmation signal for command: " << message << endl; return;}
    return;
}

bool App::isConnected(){
    return _connected;
}

void App::groupManagerStatus(int projID){
    for(int i = 0; i < (int)_managers.size(); i++){
        if(_managers[i].getProjectId() == projID){
            cout << "Manager [" << projID << "] " << _managers[i].getProjectName() << endl;
            vector<Group> groups = _managers[i].getActiveGroups();
            cout << "  Queue size: " << groups.size() << endl;
            for(int j = 0; j < (int)groups.size(); j++){
                printGroup(groups[j]);
            }
            return;
        }
    }
    cout << "! No GroupManager for projectID: " << projID << " found" << endl;
}

void App::programStatus(){
    cout << "Connected: " << boolalpha << _connected.load() << endl;
    cout << "Paused:    " << boolalpha << _paused.load() << endl;
    cout << "Managers:  " << _managers.size() << endl;

    Table groups;
    groups.add_row({"Group Name", "Project", "Group Size","Primary Phone", "Secondary Phones" });
    groups[0].format().font_style({FontStyle::bold});
    cout << groups;
    for(int i = 0; i < (int)_managers.size(); i++){
        const GroupManager& curr = _managers[i];
        const vector<Group>& currProject = curr.getActiveGroups();
        for(int j = 0; j < (int)currProject.size(); j++){
            const Group& g = currProject[j];
            string secondaryNums = secondaryNumHelper(g.getSecondaryNumbers());
            groups.add_row({g.getPrimaryName(), g.getAwaitingProject(), to_string(g.getGroupSize()), g.getPrimaryNumber(), secondaryNums});
        }
    }
    cout << groups;
}

string App::secondaryNumHelper(vector<std::string> numbers){
    string nums = "";
    for(int i = 0; i < numbers.size(); i++){
        nums += numbers[i];
        if(i < numbers.size() - 1){
            nums += "\n";
        }
    }
    return nums;
}
//////////////////////////////////////////////////////////////////////////////////////////////////

void App::listenArduino() {
    HANDLE serial = openSerial(); // *** ADDED: correct port format

    if (serial == INVALID_HANDLE_VALUE) {
        cout << "! Failed to open serial port" << endl;
        return;
    }

    if (!configureSerial(serial)) {
        cout << "! Failed to configure serial port" << endl;
        CloseHandle(serial);
        return;
    }

    Sleep(2000); // *** ADDED: allow Arduino reset

    while (_arduinoListening.load()) {

        std::string msg = readLine(serial);

        // *** ADDED: remove ALL newline / carriage return junk
        msg.erase(std::remove_if(msg.begin(), msg.end(),
            [](unsigned char c) {
                return c == '\r' || c == '\n';
            }),
            msg.end());

        // *** ADDED: debug output
        cout << "Received: [" << msg << "] size=" << msg.size() << endl;

        // *** ADDED: robust matching (DO NOT use ==)
        if (msg.find("8") != std::string::npos) {
            pop(1);
            cout << "! hi confirm" << endl;
        }
        else if (msg.find("F") != std::string::npos) {
            pop(2);
        }
        else if (msg.find("D") != std::string::npos) {
            pop(3);
        }
    }

    CloseHandle(serial);
}

void App::startArduino(){ // *** ADDED
    if (_arduinoListening){
        cout << "! Arduino listener already running\n";
        return;
    }

    _arduinoListening = true;
    _listenArduino = std::thread(&App::listenArduino, this);

    cout << "! Arduino listener started\n";
}


void App::stopArduino(){ // *** ADDED
    if (!_arduinoListening){
        cout << "! Arduino listener already stopped\n";
        return;
    }

    _arduinoListening = false;

    if (_listenArduino.joinable()){
        _listenArduino.join();
    }

    cout << "! Arduino listener stopped\n";
}

