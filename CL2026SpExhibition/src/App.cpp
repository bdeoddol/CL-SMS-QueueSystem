#include "App.h"
#include <sstream>
#include "utilityFunc.h"

using namespace std;

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
        cout << "Invalid command" << endl;
        return;
    }

    int command = stoi(tokens[0]);
    if(command == 1){
        programStatus();
    } else if(command == 2){
        if(tokens.size() < 2){
            cout << "Invalid command: missing manager_id" << endl;
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
            cout << "Invalid command: missing project_id" << endl;
            return;
        }
        pop(stoi(tokens[1]));
    } else if(command == 6){
        if(tokens.size() < 2){
            cout << "Invalid command: missing manager_id" << endl;
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
