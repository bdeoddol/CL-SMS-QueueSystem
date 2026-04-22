#include "App.h"
#include <sstream>
#include "utilityFunc.h"
#include <thread>
#include <winsock2.h> //socket library
#include <ws2tcpip.h> //needed for ipv6
#include <unistd.h>

using namespace std;

App::App(){
    // construct and assign two threads as the designated client threads of the APP. These two will perform the work
    // https://en.cppreference.com/cpp/thread/thread/thread
    this->_recieveThread = thread(some args here); 
    this->_sendThread = thread(some args here); 
    this->_currProtocol = -1;
    this->clientSocket = -1;

    this->_IPv4serverAddress = {};
    this->_IPv6serverAddress = {};
}

void App::displayOptions(){
    cout << "=============================================" << endl;
    cout << "  CLI CONTROL INTERFACE" << endl;
    cout << "=============================================" << endl;
    cout << "  STATUS" << endl;
    cout << "    1. Program status" << endl;
    cout << "    2. Group manager status  <manager_id>" << endl;
    cout << "---------------------------------------------" << endl;
    cout << "  PARSING" << endl;
    cout << "    3. Pause parsing" << endl;
    cout << "    4. Resume parsing" << endl;
    cout << "---------------------------------------------" << endl;
    cout << "    5. Pop from project queue  <project_id>" << endl;
    cout << "    6. Show all active groups <manager_id>" << endl;
    cout << "    7. Connect to Java server  <host> <port>" << endl;
    cout << "    0. Exit" << endl;
    cout << "=============================================" << endl;
    cout << "Enter command: ";
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

    int command = stoi(tokens[0]);
    if(command == 1){
        programStatus();
    } else if(command == 2){
        if(tokens.size() < 2){
            cout << "! Invalid command: missing manager_id" << endl;
            return;
        }
        string manager_id = tokens[1];
        groupManagerStatus(manager_id);
    } else if(command == 3){
        pauseParse();
    } else if(command == 4){
        resumeParse();
    } else if(command == 5){
        if(tokens.size() < 2){
            cout << "! Invalid command: missing project_id" << endl;
            return;
        }
        pop(stoi(tokens[1]));
    } else if(command == 6){
        if(tokens.size() < 2){
            cout << "! Invalid command: missing manager_id" << endl;
            return;
        }
        showActiveGroups(stoi(tokens[1]));
    } else if(command == 7){
        connectToJavaServer();
    } else if(command == 0){
        exit(0);
    } else {
        cout << "Invalid command" << endl;
        return;
    }
} 

void App::pop(int project_id){
    for(int i = 0; i < _managers.size(); i++){
        if(_managers[i].getProjectId() == project_id){
            Group poppedGroup = _managers[i].popGroup();
            if(poppedGroup._validObj == false){
                return;
            }
            printGroup(poppedGroup);
            break;
        }
    }
}

void App::showActiveGroups(int project_id){
    for(int i = 0; i < _managers.size(); i++){
        if(_managers[i].getProjectId() == project_id){
            vector<Group> activeGroups = _managers[i].getActiveGroups();
            for(int j = 0; j < activeGroups.size(); j++){
                printGroup(activeGroups[j]);
            }
        }
    }
}

void App::connectToJavaServer(string hostIP, int portNumber, std::string protocol){
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

    if(connectMode == AF_INET){
        this->clientSocket = socket(AF_INET, SOCK_STREAM, 0);
    }
    else if(connectMode == AF_INET6){
        this->clientSocket = socket(AF_INET6, SOCK_STREAM, 0);
    }
    
    if(this->clientSocket == -1){
        cout << "! Failed to create socket" << endl;
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
    int connectTest = -1;
    if(connectMode == AF_INET){
        //if IPv4
        //grab IPv4 Public Address for hostIP
        this->_currProtocol = AF_INET;
        this->_IPv4serverAddress = IPv4SpecifiedDestination(hostIP, portNumber);
        connectTest = connect(clientSocket, (struct sockaddr *)&_IPv4serverAddress, sizeof(_IPv4serverAddress));

    }
    else if(connectMode == AF_INET6){
        //if IPv6,
        //typically, we will run the parser on the same device, so grab the local-link ipv6 for hostIP
        this->_currProtocol = AF_INET6;
        this->_IPv6serverAddress = IPv6SpecifiedDestination(hostIP, portNumber);
        connectTest = connect(clientSocket, (struct sockaddr *)&_IPv6serverAddress, sizeof(_IPv6serverAddress));
    }
    if(connectTest == -1){
        cout << "! Failed to connect, please input valid host IP, port number, and protocol";
        close(clientSocket);
        this->clientSocket = -1;
        return;
    }

    return;
}

void App::reconnect(){
    if(this->_currProtocol == -1){
        cout << "! There is no previous connection to reconnect to" << endl;
        return;
    }

    int connectTest;
    if(this->_currProtocol == AF_INET){
        this->clientSocket = socket(AF_INET, SOCK_STREAM, 0);
        connectTest = connect(clientSocket, (struct sockaddr *)&_IPv4serverAddress, sizeof(_IPv4serverAddress));
        if(clientSocket == -1){
            cout << "! Failed to reconnnect to IPv4 server socket!" << endl;
        }
    }
    else if(this->_currProtocol == AF_INET6){
        this->clientSocket = socket(AF_INET6, SOCK_STREAM, 0);
        connectTest = connect(clientSocket, (struct sockaddr *)&_IPv6serverAddress, sizeof(_IPv6serverAddress));
        if(clientSocket == -1){
            cout << "! Failed to reconnnect to IPv6 server socket!" << endl;
        }
    }
    
    if(connectTest == -1){
        cout << "! Reconnect failed, please check host IP, port number, and protocol" << endl;
        this->clientSocket = -1;
    }
}

void App::disconnect(){
    close(this->clientSocket);
    this->clientSocket = -1;
    this->_currProtocol = -1;

    //todo
    stop the recieve and sending threads here!
}
