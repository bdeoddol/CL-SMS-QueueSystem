#include "utilityFunc.h"
#include "Group.h"
#include <string>
#include <vector>
#include <random>
#include <iostream>
#include <winsock2.h>
#include <ws2tcpip.h>
#include <windows.h> //connect, set up, and configure serial



using namespace std;

int generate4digNum(){
    random_device rd;
    mt19937 gen(rd());
    uniform_int_distribution<> distrib(1,9999);

    return distrib(gen);
}

void printGroup(Group group){
    cout << "Group Name: " << group.getPrimaryName() << endl;
    cout << "Awaiting Project: " << group.getAwaitingProject() << endl;
    cout << "------------------------------" << endl;
    cout << "Primary Phone Number: " << group.getNumber() << endl;
    cout << "Secondary Phone Numbers: " << endl;
    vector<string> secondaryNumbers = group.getSecondaryNumbers();
    for(int i = 0; i < (int)secondaryNumbers.size(); i++){
        cout << secondaryNumbers[i] << endl;
    }
    cout << "------------------------------" << endl << endl;
}

struct sockaddr_in6 IPv6SpecifiedDestination(string hostIP, int portNumber){
    struct sockaddr_in6 retServerAddress = {};

    retServerAddress.sin6_family = AF_INET6;
    retServerAddress.sin6_port = htons(portNumber);
    inet_pton(AF_INET6, hostIP.c_str(), &retServerAddress.sin6_addr);

    return retServerAddress;
}

struct sockaddr_in IPv4SpecifiedDestination(string hostIP, int portNumber){
    struct sockaddr_in retServerAddress = {};

    retServerAddress.sin_family = AF_INET;
    retServerAddress.sin_port = htons(portNumber);
    inet_pton(AF_INET, hostIP.c_str(), &retServerAddress.sin_addr);

    return retServerAddress;
}

int parseProtocol(string protocol){
    if(protocol == "ipv4" || protocol == "IPv4"){
        return AF_INET;
    }
    else if(protocol == "ipv6" || protocol == "IPv6"){
        return AF_INET6;
    }
    else{
        return -1;
    }
}

bool sendWholeMessage(SOCKET socket, string msg){
    int bytesSent;
    int totalSent = 0;

    while(totalSent < (int)msg.size()){
        bytesSent = send(socket, msg.c_str() + totalSent, (int)(msg.size() - totalSent), 0);
        if(bytesSent == SOCKET_ERROR){
            return false;
        }
        totalSent += bytesSent;
    }

    return true;
}

//from chatgpt /////////////////////////////////////////////////////////////////

HANDLE openSerial() {
    HANDLE hSerial = CreateFileW(
        L"\\\\.\\COM7",   //for COM3
        GENERIC_READ | GENERIC_WRITE,
        0,
        0,
        OPEN_EXISTING,
        0,
        0
    );

    if (hSerial == INVALID_HANDLE_VALUE) {
        cout << "Error opening serial port\n";
        return INVALID_HANDLE_VALUE;
    }

    return hSerial;
}

bool configureSerial(HANDLE hSerial) {
    DCB dcbSerialParams = {0};
    dcbSerialParams.DCBlength = sizeof(dcbSerialParams);

    if (!GetCommState(hSerial, &dcbSerialParams)) {
        cout << "Error getting state\n";
        return false;
    }

    dcbSerialParams.BaudRate = CBR_9600;
    dcbSerialParams.ByteSize = 8;
    dcbSerialParams.StopBits = ONESTOPBIT;
    dcbSerialParams.Parity   = NOPARITY;

    if (!SetCommState(hSerial, &dcbSerialParams)) {
        cout << "Error setting state\n";
        return false;
    }

    return true;
}

string readLine(HANDLE serial) {
    char c;
    DWORD bytesRead;
    std::string result;

    while (true) {
        if (ReadFile(serial, &c, 1, &bytesRead, NULL) && bytesRead > 0) {
            if (c == '\n') break;
            result += c;
        }
    }

    return result;
}