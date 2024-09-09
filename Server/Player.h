//
// Created by benra on 7/16/2024.
//

#ifndef SERVER_PLAYER_H
#define SERVER_PLAYER_H

#include "winsock2.h"
#include "chrono"
#include "string"
#define BUFFER_SIZE 200
struct Vector2{
    float x;
    float y;
};
class Player {
public:
    u_short portDest = 0;
    std::chrono::time_point<std::chrono::steady_clock> playerCorrectionTime = std::chrono::steady_clock::now();
    int id;
    std::string messageToSend;
    bool correctionFlag = false;
    bool init = false;
    bool switchFlag = false;
    int levelID = 0;
    bool directionFlag = false;
    SOCKET socket;
    sockaddr_in address;
    int addressLength = sizeof(address);
    char buffer[BUFFER_SIZE];
    bool establishConnection();
    void spawnPointMapper();
    float x = 50;
    float y = 50;
    Vector2 direction = {0,0};
    Vector2 inputs = {0,0};
    void move();
};


#endif //SERVER_PLAYER_H
