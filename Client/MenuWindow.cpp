//
// Created by Moshe on 7/16/2024.
//

#include "MenuWindow.h"

#include <vector>

MenuWindow::MenuWindow(const int windowWidth, const int windowHeight)
    : windowWidth(windowWidth), windowHeight(windowHeight) {
}

void MenuWindow::update() {
    if (IsKeyDown(KEY_SPACE)) {
        playerConnected = true;
        connectionStatus = "Connected";
    }
}

void MenuWindow::calculate() {
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

void MenuWindow::drawTextField() {
    // draw text field outline

    const int fieldW = ceil(windowWidth * 0.70);
    const int fieldH = FONT_SIZE; // aka text height
    const int fieldX = (windowWidth / 2) - (fieldW / 2);
    const int fieldY = ceil(windowHeight * 0.50);
    DrawRectangleLines(fieldX, fieldY, fieldW, fieldH, BLACK);

    // draw text from text field buffer
    const int ipTextLength = MeasureText(textFieldBuffer.c_str(), FONT_SIZE);
    const int x = (fieldW / 2);
    const int y = fieldY;
    DrawText(textFieldBuffer.c_str(), x, y, FONT_SIZE, RED);
}

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