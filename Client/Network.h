//
// Created by benra on 7/16/2024.
//

#ifndef CLIENT_NETWORK_H
#define CLIENT_NETWORK_H
#include "winsock2.h"
#include <ws2tcpip.h>
#include "iostream"
#define PORT_1  54000
#define PORT_2 54001
#define CONNECTION_TRY '?'
#define CONNECTION_FAIL '!'
#define CONNECTION_SUCCEED '^'
#define BUFFER_SIZE 40
class Network {
    int iResult;
    WSADATA wsadata;
    SOCKET sock;
public:
    sockaddr_in address;
    int addressLength = sizeof(address);
    char buffer[BUFFER_SIZE];
    Network(std::string& ip);
    void createSocket();
    void startup();
    std::string receive();
    void send(std::string& message);
    ~Network();
};


#endif //CLIENT_NETWORK_H
