//
// Created by benra on 7/16/2024.
//

#ifndef SERVER_PLAYER_H
#define SERVER_PLAYER_H

#include "winsock2.h"
class Player {
public:
    SOCKET socket;
    sockaddr_in address;
    int addressLength = sizeof(address);
    char buffer[40]; // Separate buffer for each client
};


#endif //SERVER_PLAYER_H
