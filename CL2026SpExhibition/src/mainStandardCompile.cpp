#include <iostream>
#include <string>
#include <winsock2.h>
#include "../lib/App.h"

using namespace std;

int main(){
    WSADATA wsaData;
    if(WSAStartup(MAKEWORD(2, 2), &wsaData) != 0){
        cout << "! WSAStartup failed" << endl;
        return 1;
    }

    string projects[] = {"86!", "Frisson", "Desk Drawer"};
    App app(projects, 3);

    string input;
    while(true){
        app.displayOptions();
        if(!getline(cin, input)) break;
        app.handle(input);
    }

    WSACleanup();
    return 0;
}

