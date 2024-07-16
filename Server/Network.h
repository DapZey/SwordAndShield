//
// Created by benra on 7/16/2024.
//

#ifndef CLIENT_NETWORK_H
#define CLIENT_NETWORK_H
#include "winsock2.h"
#include "iostream"
#include "Player.h"
class Network {
    int iResult;
    WSADATA wsadata;
public:
    Network();
    void SendMessageTo(const std::string& s, Player& p);
    void ReceiveMessageFrom(Player& p);
    void CreateSocket(Player& player, const int& port);
    bool SetNonBlocking(SOCKET& sock);
    bool BindSocketToPort(Player& p, const int& port);
    void Startup();
    void Kill(Player& p);
    void Shutdown();
};


#endif //CLIENT_NETWORK_H
