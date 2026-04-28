    #include "App.h"
    #include <sstream>
    #include "utilityFunc.h"
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


//remember manager_ID is the manager of all groups for one project 
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
    cout << "Enter command number: ";
}


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
    cout << "    3. Pause CPP parsing" << endl;
    cout << "    4. Resume CPP parsing" << endl;
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
            if (!poppedGroup._validObj){
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

void App::programStatus(){
    // groups in each queue, pause status, server host
    //# projects, total groups, connected to server house 

    /*per project summary: id of project, name of project, # groups in project, 
        id of next group, size of next group, priority value of next group
    -longest waiting group id, how long they've been waiting 

    any invalid groups - add functionality for that 
        
    //pause status */
    for(int i = 0; i < _managers.size(); i++){
        // cout << "Project: " << _managers[i].ge()
        cout << "Number of Groups: " << _managers[i].getActiveGroups().size() << endl;
        cout << "------------------------------" << endl;
        cout << boolalpha << "Pause Status: " << _paused << endl;
    }
}
