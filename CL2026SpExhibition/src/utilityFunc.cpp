#include "QueueObject.h"
#include "Group.h"
#include <string>
#include <vector>
#include <random>
#include <iostream>
#include <winsock2.h> //socket library
#include <ws2tcpip.h> //needed for ipv6
using namespace std;

int generate4digNum(){
    random_device rd;
    mt19937 gen(rd());
    uniform_int_distribution<> distrib(1,9999);

    return distrib(gen);
}

void printGroup(Group group){
    //name, primary and seecondary phone numbers, awaiting project
    cout << "Group Name: " << group.getPrimaryName() << endl;
    cout << "Awaiting Project: " << group.getAwaitingProject() << endl;
    cout << "------------------------------" << endl;
    cout << "Primary Phone Number: " << group.getNumber() << endl;
    cout << "Secondary Phone Numbers: " << endl;
    vector<string> secondaryNumbers = group.getSecondaryNumbers();
    for(int i = 0; i < secondaryNumbers.size(); i++){
        cout << secondaryNumbers[i] << endl;
    }
    cout << "------------------------------" << endl << endl;
}

struct sockaddr_in6 IPv6SpecifiedDestination(string hostIP, int portNumber){
    struct sockaddr_in6 retServerAddress;

    retServerAddress.sin6_family = AF_INET6; //use AF_INET6 as the address family format
    retServerAddress.sin6_port = htons(portNumber);
    inet_pton(AF_INET6, hostIP.c_str(), &retServerAddress.sin6_addr); //typically, we will run the parser on the same device, so grab the local-link ipv6
    
    return retServerAddress;
}

struct sockaddr_in IPv4SpecifiedDestination(string hostIP, int portNumber){
    struct sockaddr_in retServerAddress;

    retServerAddress.sin_family = AF_INET; //use AF_INET as the address family format
    retServerAddress.sin_port = htons(portNumber);
    inet_pton(AF_INET, hostIP.c_str(), &retServerAddress.sin_addr); //grab public IP in IPv4
    
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