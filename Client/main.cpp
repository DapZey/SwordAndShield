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
    std:: cout << "test\n";
    windowState winState = MENU;
    InitWindow(WINDOW_WIDTH, WINDOW_HEIGHT, "SwordAndSheild");
    SetTargetFPS(DEFAULT_FPS_TARGET);
    Network n;
    Protocol p(n);
    // init window vars
    MenuWindow menuWindow(WINDOW_WIDTH, WINDOW_HEIGHT, p);
    GameWindow gameWindow(p);
    while (!WindowShouldClose()) {
//        int x = GetFPS();
//        std::cout<<x<<"\n";
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