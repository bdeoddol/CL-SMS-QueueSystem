#ifndef APP_H
#define APP_H

#include <iostream>
#include <string>
#include <vector>
#include <thread>
#include <atomic>
#include <winsock2.h>
#include <ws2tcpip.h>
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
    App(std::string* projects, int numProj);
    ~App();
    void displayOptions();
    void handle(std::string input);

  private:

    void programStatus();
    void groupManagerStatus(int projID);

    bool pauseParse();
    bool startParse();

    void pop(int project_id);
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

    //helper for userSendStream, execution function for receivingthread
    void receivingStream();

    //helper for userSendStream, start up a new receive thread
    void startReceiveThread();
    
    //given a command, sends to the serversocket thru stream
    void userSendStream(std::string cmd);
    void sendConfirmation(int ID);
    bool isConnected();

    //from chatgpt
    void listenArduino(); 
    void startArduino();   // *** ADDED
    void stopArduino();    // *** ADDED
    std::atomic<bool> _arduinoListening;

    std::atomic<bool> _paused;
    std::atomic<bool> _alive;
    std::atomic<bool> _connected;
    
    std::thread _receiveThread;
    std::thread _listenArduino;
    int _currProtocol;
    struct sockaddr_in6 _IPv6serverAddress;
    struct sockaddr_in _IPv4serverAddress;
    SOCKET _clientSocket;
    std::vector<GroupManager> _managers;
    CParser CParser;
};
#endif
