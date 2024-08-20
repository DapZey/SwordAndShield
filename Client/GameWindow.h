//
// Created by benra on 7/22/2024.
//

#ifndef CLIENT_GAMEWINDOW_H
#define CLIENT_GAMEWINDOW_H
#define TICK_RATE_MS 16
#include "raylib.h"
#include "Protocol.h"
#include "World.h"
#include <chrono>
class GameWindow {
    std::chrono::time_point<std::chrono::steady_clock> gameTime = std::chrono::steady_clock::now();
public:
    Camera2D playerFollowCamera = {0};
    World world;
    int prevLevel = 0;
    Protocol* protocol;
    void draw();
    void calculate();
    void update();
    void run();
    GameWindow(Protocol& p);

};


#endif //CLIENT_GAMEWINDOW_H
