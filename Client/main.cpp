#include <iostream>

#include "MenuWindow.h"
#include "raylib.h"
#include "Network.h"
#include "Protocol.h"
#define WINDOW_WIDTH 1280
#define WINDOW_HEIGHT 720
#define DEFAULT_IP "127.0.0.1"

enum windowState {MENU, GAME};

int main() {
    windowState winState = MENU;
    InitWindow(WINDOW_WIDTH, WINDOW_HEIGHT, "SwordAndSheild");
    // init window vars
    MenuWindow menuWindow(WINDOW_WIDTH, WINDOW_HEIGHT);
    std::string ip = DEFAULT_IP;
    SetTargetFPS(60);
    Network connection(ip);
    Protocol p(connection);
    while (!WindowShouldClose()) {
        p.run();
        switch (winState) {
            case MENU:
                menuWindow.run();
            if (menuWindow.connected())
                winState = GAME;
            break;
            case GAME:

                break;
        }
    }
    RaylibCloseWindow();
    return 0;
}