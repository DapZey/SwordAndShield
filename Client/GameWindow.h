//
// Created by benra on 7/22/2024.
//

#ifndef CLIENT_GAMEWINDOW_H
#define CLIENT_GAMEWINDOW_H

#include "raylib.h"
#include "Protocol.h"
#include "World.h"
class GameWindow {
public:
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
