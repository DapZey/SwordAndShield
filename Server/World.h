//
// Created by benra on 8/20/2024.
//

#ifndef SERVER_WORLD_H
#define SERVER_WORLD_H
#include "chrono"
#include "Player.h"
class World {
    std::chrono::time_point<std::chrono::steady_clock> gameTime = std::chrono::steady_clock::now();
    Player* player1;
    Player* player2;
public:
    void setPlayers(Player& p1, Player& p2);
    void run();
};


#endif //SERVER_WORLD_H
