//
// Created by benra on 7/16/2024.
//

#ifndef CLIENT_PROTOCOL_H
#define CLIENT_PROTOCOL_H
#define DEFAULT_IP "127.0.0.1"
#include "Network.h"
#include "ParsingUtils.h"

class Protocol {
    int port_1 = PORT_1;
    int port_2 = PORT_2;
public:
    bool disconnected = true;
    Network* network;
    void preConnection(bool flag);
    Protocol(Network& connection);
    void MenuRun(bool connectTryFlag);
    void GameRun(bool levelSwitchFlag, int level);
    void checkTry(std::string& data);
};


#endif //CLIENT_PROTOCOL_H
