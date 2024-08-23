//
// Created by benra on 8/20/2024.
//

#include "World.h"
#include "math.h"
#include "iostream"
#define TICK_RATE_MS 16
void World::setPlayers(Player& p1, Player& p2) {
    this->player1 = &p1;
    this->player2 = &p2;
}
void World::run() {
    std::chrono::time_point<std::chrono::steady_clock> currentFrameTime = std::chrono::steady_clock::now();
    int elapsed = std::chrono::duration_cast<std::chrono::milliseconds>(currentFrameTime - gameTime).count();
    int ticksPassed = std::floor(elapsed / TICK_RATE_MS);

    // Update gameTime to the last processed tick time
    if (ticksPassed > 0) {
        gameTime += std::chrono::milliseconds(ticksPassed * TICK_RATE_MS);
    }
    for (int i = 0; i < ticksPassed; i++){
        player1->move();
        player2->move();
        if (player1->direction.x != 0){
            std::cout<<player1->x<<"\n";
        }
    }
}