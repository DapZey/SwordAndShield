#include <iostream>

#include "MenuWindow.h"
#include "raylib.h"

#define WINDOW_WIDTH 1280
#define WINDOW_HEIGHT 720

enum windowState {MENU, GAME};

int main() {
    windowState winState = MENU;
    InitWindow(WINDOW_WIDTH, WINDOW_HEIGHT, "SwordAndSheild");
    // init window vars
    MenuWindow menuWindow(WINDOW_WIDTH, WINDOW_HEIGHT);

    SetTargetFPS(60);
    while (!WindowShouldClose()) {
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
