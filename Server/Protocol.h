//
// Created by benra on 7/16/2024.
//

#ifndef SERVER_PROTOCOL_H
#define SERVER_PROTOCOL_H
#include "Network.h"
#include "Player.h"
#include "ParsingUtils.h"
#include "World.h"
#define PORT_1  54000
#define PORT_2 54001
#define PLAYER_COUNT 2
#define CONNECTION_TRY '?'
#define CONNECTION_FAIL '!'
#define CONNECTION_SUCCEED '^'
class Protocol {
    std::chrono::time_point<std::chrono::steady_clock> protocolTime = std::chrono::steady_clock::now();
    std::chrono::time_point<std::chrono::steady_clock> playerCorrectionTime = std::chrono::steady_clock::now();
    int port_1 = PORT_1;
    int port_2 = PORT_2;
    Network network;
    Player players[2];
    World world;
    void tryConnection(std::string& data,Player& currentPlayer, std::string& messageToSendCurrent);
public:
    ~Protocol();
    Protocol();
    void Run();
    void sendCorrection(Player& p,std::string& toSend, std::string& toAdd);
};


#endif //SERVER_PROTOCOL_H
