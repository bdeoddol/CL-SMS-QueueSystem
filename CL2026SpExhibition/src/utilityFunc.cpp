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

bool sendWholeMessage(int socket, string msg){
    //because TCP streams do not guarantee that all of the sent data will be whole, it's possible that the stream sends in partial data
    //send() will return the number of bytes sent,
    //if the number of bytes sent == the size of your message, the data has been sent whole
    //if the number of bytes sent < the size of our message, the data has been sent partially and must be looped again to send the remaining message
    //      while by default, the 2nd arg, msg.c_str() will return a pointer to the first character of the c_string array, 
    //      you must modify the second arg such that the argument will return a pointer to the start of the REMAINING data to be sent in the c_string array
    //      the same is true for the msg.size(), as you are no longer sending the whole, but a part of it. Therefore, subtract the total bytes sent from msg.size()
    //if the number of bytes sent == -1, an error has occured while sending the message. abort.

    ssize_t bytesSent;
    ssize_t totalSent = 0;

    while(totalSent < msg.size()){
        bytesSent = send(socket, msg.c_str()+totalSent, msg.size()-totalSent, 0);
        if(bytesSent == -1){
            return false;
        }
        totalSent += bytesSent;
    }

    return true;
}