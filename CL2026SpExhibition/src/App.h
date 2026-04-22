#include <iostream>
#include <string>
#include <vector>
#include <thread>
#include <winsock2.h> //socket library
#include <ws2tcpip.h> //needed for ipv6
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
    void connectToJavaServer(std::string hostIP, int portNumber, std::string protocol);
    void reconnect();
    void disconnect();
    void recieveingStream();
    void sendingStream();

    //todo: disconnect and reconnect funcs

    bool _paused;


    private:
    std::thread _recieveThread;
    std::thread _sendThread;
    int _currProtocol;
    struct sockaddr_in6 _IPv6serverAddress;
    struct sockaddr_in _IPv4serverAddress;
    int clientSocket;
    vector<GroupManager> _managers;
    

};