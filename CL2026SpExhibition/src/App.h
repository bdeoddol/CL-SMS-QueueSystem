#include <iostream>
#include <string>
#include <vector>
#include <thread>
#include <winsock2.h> //socket library
#include <ws2tcpip.h> //needed for ipv6
#include <atomic> //atomic is like "static" in java
#include "GroupManager.h"


class App{
  public:
    App();
    void displayOptions();
    void handle(std::string input);

  private:
    
    void programStatus();
    void groupManagerStatus(std::string manager_id);
    bool pauseParse();
    bool startParse();
    void pop(int project_id);
    void showActiveGroups(int project_id);

    //*** THE RULE OF THUMB IS THAT UPON CONNECTION TO SERVER, BEGIN LSITENING FOR DATA */
    void connectToJavaServer(std::string hostIP, int portNumber, std::string protocol);
    void reconnect();
    bool attemptConnection(int protocol, struct sockaddr* addr, size_t addrLen);
    void disconnect();

    void receivingStream();
    void userSendStream(std::string cmd);
    void sendConfirmation(int ID);


    atomic<bool> _paused;
    atomic<bool> _alive;


    private:
    atomic<bool> _connected;
    std::thread _receiveThread;
    // std::thread _sendThread;
    int _currProtocol;
    struct sockaddr_in6 _IPv6serverAddress;
    struct sockaddr_in _IPv4serverAddress;
    int _clientSocket;
    vector<GroupManager> _managers;
    

};