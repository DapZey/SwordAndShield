//
// Created by benra on 7/16/2024.
//

#ifndef SERVER_PLAYER_H
#define SERVER_PLAYER_H

#include "winsock2.h"
#define BUFFER_SIZE 40
struct Vector2{
    float x;
    float y;
};
class Player {
    bool init = false;
public:
    int levelID = 0;
    SOCKET socket;
    sockaddr_in address;
    int addressLength = sizeof(address);
    char buffer[BUFFER_SIZE];
    bool establishConnection();
    void spawnPointMapper();
    float x = 50;
    float xPrev = 50;
    float y = 50;
    Vector2 direction = {0,0};
    void move();
};


#endif //SERVER_PLAYER_H
