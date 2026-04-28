#pragma once
#include "QueueObject.h"
#include "Group.h"
#include <string>
#include <vector>
#include <random>
#include <iostream>
#include <winsock2.h>
#include <ws2tcpip.h>

int generate4digNum();

void printGroup(Group group);

struct sockaddr_in6 IPv6SpecifiedDestination(std::string hostIP, int portNumber);

struct sockaddr_in IPv4SpecifiedDestination(std::string hostIP, int portNumber);

int parseProtocol(std::string protocol);

bool sendWholeMessage(SOCKET socket, std::string msg);

#endif
