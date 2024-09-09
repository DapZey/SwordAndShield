#include <iostream>

#include "MenuWindow.h"
#include "raylib.h"
#include "Network.h"
#include "Protocol.h"
#include "GameWindow.h"
#define WINDOW_WIDTH 1280
#define WINDOW_HEIGHT 720
#define DEFAULT_IP "127.0.0.1"
#define DEFAULT_FPS_TARGET 1000
enum windowState {MENU, GAME};

int main() {
    windowState winState = GAME;//should be menu when connecting
    InitWindow(WINDOW_WIDTH, WINDOW_HEIGHT, "SwordAndSheild");
    SetTargetFPS(DEFAULT_FPS_TARGET);
    Network n;
//    ToggleFullscreen();
    Protocol p(n);
    // init window vars
    MenuWindow menuWindow(WINDOW_WIDTH, WINDOW_HEIGHT, p);
    GameWindow gameWindow(p);
    while (!WindowShouldClose()) {
        switch (winState) {
            case MENU:
                menuWindow.run();
            if (menuWindow.connected())
                winState = GAME;
            break;
            case GAME:
                gameWindow.run();
                break;
        }
    }
    RaylibCloseWindow();
    return 0;
}