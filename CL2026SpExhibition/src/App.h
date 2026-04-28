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
    void displayOptions();
    void handle(std::string input);

  private:

    void programStatus();
    void groupManagerStatus(int projID);

    bool pauseParse();
    bool startParse();

    void pop(int project_id);
    void showActiveGroups(int project_id);

    void connectToJavaServer(std::string hostIP, int portNumber, std::string protocol);
    bool attemptConnection(int IPprotocol, struct sockaddr* addr, size_t addrLen);
    void reconnect();
    void disconnect();
    void receivingStream();
    void startReceiveThread();
    void userSendStream(std::string cmd);
    void sendConfirmation(int ID);
    bool isConnected();

    std::atomic<bool> _paused;
    std::atomic<bool> _alive;
    std::atomic<bool> _connected;
    std::thread _receiveThread;
    int _currProtocol;
    struct sockaddr_in6 _IPv6serverAddress;
    struct sockaddr_in _IPv4serverAddress;
    SOCKET _clientSocket;
    std::vector<GroupManager> _managers;
    CParser _cparser;
};

#endif
