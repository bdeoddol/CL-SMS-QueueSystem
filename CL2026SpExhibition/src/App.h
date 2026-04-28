#include <iostream>
#include <string>
#include <vector>
#include <thread>
#include <winsock2.h> //socket library
#include <ws2tcpip.h> //needed for ipv6
#include <atomic> //atomic is like "static" in java
#include "GroupManager.h"
#include "CParser.h"


class App{
  public:

      /*
    projID
    1 = 86!
    2 = Frission
    3 = Desk Drawer
    */
    App(string* projects, int numProj);
    void displayOptions();
    void handle(std::string input);

  private:
    
    void programStatus();
    //displays the status of a group manager given it's id (the projectID),
    void groupManagerStatus(int projID);
    
    bool pauseParse();
    bool startParse();

    //pops from the queue of a given managers project ID
    void pop(int project_id);

    //displays all the actives groups of a given managers project ID
    void showActiveGroups(int project_id);

    //*** THE RULE OF THUMB IS THAT UPON CONNECTION TO SERVER, BEGIN LSITENING FOR DATA */
    //connects to a given hostIP, portNum, and protocol (ipv4 or ipv6), calls the actual connect() func
    //starts receivingthread
    void connectToJavaServer(std::string hostIP, int portNumber, std::string protocol);
    
    //helper function for connectToJavaServer that makes connection with the ServerSocket
    bool attemptConnection(int IPprotocol, struct sockaddr* addr, size_t addrLen);

    //attempts to reconnect to the same serversocket using the last saved parameters given to connectToJavaServer
    //starts receivingthread  
    void reconnect();

    //disconnects from the server. shut down connection, kills the receiver thread via .join(), closes _clientSocket
    void disconnect();

    //execution function for receivingthread
    void receivingStream();

    //start up a new receive thread
    void startReceiveThread();
    
    //given a command, sends to the serversocket thru stream
    void userSendStream(std::string cmd);

    //sends a confirmation message to javaparser on serversocket to pop the JSON data corresponding to the given msgID 
    void sendConfirmation(int ID);

    //check if the app is connected
    bool isConnected();

    std::atomic<bool> _paused;
    std::atomic<bool> _alive;


    private:
    std::atomic<bool> _connected;
    std::thread _receiveThread;
    // std::thread _sendThread;
    int _currProtocol;
    struct sockaddr_in6 _IPv6serverAddress;
    struct sockaddr_in _IPv4serverAddress;
    int _clientSocket;
    vector<GroupManager> _managers;
    CParser CParser;

};