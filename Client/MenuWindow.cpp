//
// Created by Moshe on 7/16/2024.
//

#include "MenuWindow.h"

MenuWindow::MenuWindow(unsigned int windowWidth, unsigned int windowHeight)
    : windowWidth(windowWidth), windowHeight(windowHeight) {
    // idk
}

void MenuWindow::update() {
}

void MenuWindow::calculate() {
    if (IsKeyDown(KEY_SPACE)) {
        playerConnected = true;
    }
}

void MenuWindow::draw() {
    BeginDrawing();
    ClearBackground(RED);
    EndDrawing();
}

bool MenuWindow::connected() {
    return playerConnected;
}

void MenuWindow::run() {
    calculate();
    update();
    draw();
}