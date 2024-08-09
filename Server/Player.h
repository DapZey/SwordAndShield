//
// Created by benra on 7/16/2024.
//

#ifndef SERVER_PLAYER_H
#define SERVER_PLAYER_H

#include "winsock2.h"
#define BUFFER_SIZE 40
class Player {
    bool init = false;
public:
    int levelID = 0;
    SOCKET socket;
    sockaddr_in address;
    int addressLength = sizeof(address);
    char buffer[BUFFER_SIZE];
    bool establishConnection();
};


#endif //SERVER_PLAYER_H
