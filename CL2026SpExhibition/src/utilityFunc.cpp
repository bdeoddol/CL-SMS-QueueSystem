#include "utilityFunc.h"
#include "Group.h"
#include <string>
#include <vector>
#include <random>
#include <iostream>
#include <winsock2.h>
#include <ws2tcpip.h>
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
