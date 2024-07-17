//
// Created by Moshe on 7/16/2024.
//

#include "MenuWindow.h"

MenuWindow::MenuWindow(const int windowWidth, const int windowHeight)
    : windowWidth(windowWidth), windowHeight(windowHeight) {
}

void MenuWindow::update() {
}

void MenuWindow::calculate() {
    if (IsKeyDown(KEY_SPACE)) {
        playerConnected = true;
        connectionStatus = "Connected";
    }
}

void MenuWindow::draw() {
    // things to draw:
    // conn status
    // text field
    // connect button
    BeginDrawing();
    ClearBackground(WHITE);
    drawConnectionStatus();
    drawButton();
    drawTextField();
    EndDrawing();
}

void MenuWindow::drawConnectionStatus() {
    const int textLength = MeasureText(connectionStatus.c_str(), FONT_SIZE);
    const int x = (windowWidth / 2) - (textLength / 2);
    const int y = ceil(windowHeight * 0.10); // starting at 10% of the window height
    RaylibDrawText(connectionStatus.c_str(), x, y, FONT_SIZE,
        playerConnected ? GREEN : RED);
}

void MenuWindow::drawTextField() { }
void MenuWindow::drawButton() {

}

bool MenuWindow::connected() {
    return false;
}

void MenuWindow::run() {
    calculate();
    update();
    draw();
}