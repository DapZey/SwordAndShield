//
// Created by Moshe on 7/16/2024.
//

#include "MenuWindow.h"

#include <vector>
#include <external/glad.h>

MenuWindow::MenuWindow(const int windowWidth, const int windowHeight, Protocol& p)
    : windowWidth(windowWidth), windowHeight(windowHeight) {
    this->protocol = &p;
}

void MenuWindow::update() {
    bool connectionTryFlag = false;
    if (IsKeyDown(KEY_R)){
        std::string ip = DEFAULT_IP;
        this->protocol->network->Init(ip);
    }
    if (IsKeyDown(KEY_SPACE)){
        connectionTryFlag = true;
    }
    this->protocol->run(connectionTryFlag);
    if (!this->protocol->disconnected){
        playerConnected = true;
        connectionStatus = CONNECTION_STATUS_C;
    }
    updateTextField();
}

void MenuWindow::updateTextField() {
    // check if selected
    if (IsMouseButtonPressed(MOUSE_BUTTON_LEFT)) {
        isTxtFieldSelected = true;
    }
    if (!isTxtFieldSelected)
        return;
    int key = GetCharPressed();
    if (IsKeyDown(KEY_BACKSPACE)) {
        if (!textFieldBuffer.empty()) {
            textFieldBuffer.pop_back();
        }
    }
    // can't add chars if >= max_length
    if (textFieldBuffer.length() >= MAX_IP_INPUT)
        return;

    if (key == KEY_ZERO)
        textFieldBuffer += "0";
    else if (key == KEY_ONE)
        textFieldBuffer += "1";
    else if (key == KEY_TWO)
        textFieldBuffer += "2";
    else if (key == KEY_THREE)
        textFieldBuffer += "3";
    else if (key == KEY_FOUR)
        textFieldBuffer += "4";
    else if (key == KEY_FIVE)
        textFieldBuffer += "5";
    else if (key == KEY_SIX)
        textFieldBuffer += "6";
    else if (key == KEY_SEVEN)
        textFieldBuffer += "7";
    else if (key == KEY_EIGHT)
        textFieldBuffer += "8";
    else if (key == KEY_NINE)
        textFieldBuffer += "9";
    else if (key == KEY_PERIOD)
        textFieldBuffer += ".";
}

void MenuWindow::calculate() {
}

void MenuWindow::draw() {
    // things to draw:
    // conn status
    // text field
    // connect button
    BeginDrawing();
    ClearBackground(YELLOW);
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
    // draw text field box
    const int fieldW = ceil(windowWidth * 0.70);
    const int fieldH = FONT_SIZE; // i.e. text height
    const int fieldX = (windowWidth / 2) - (fieldW / 2);
    const int fieldY = ceil(windowHeight * 0.50);

    if (isTxtFieldSelected)
        // draw just the outline
        DrawRectangleLines(fieldX, fieldY, fieldW, fieldH, RED);
    else
        DrawRectangle(fieldX, fieldY, fieldW, fieldH, WHITE);

    // draw text from text field buffer
    const int textWidth = MeasureText(textFieldBuffer.c_str(), FONT_SIZE);
    const int x = fieldX + (fieldW / 2) - (textWidth / 2);
    const int y = fieldY;
    RaylibDrawText(textFieldBuffer.c_str(), x, y, FONT_SIZE, BLACK);
}

void MenuWindow::drawButton() {
    // draw button
    const int buttonWidth = ceil(windowWidth * 0.20);
    const int buttonHeight = ceil(windowHeight * 0.05);
    const int buttonX = (windowWidth / 2) - (buttonWidth / 2);
    const int buttonY = ceil(windowHeight * 0.70);

    DrawRectangle(buttonX, buttonY, buttonWidth, buttonHeight, WHITE);

    // draw button text
    std::string btnTxt = "Connect";
    const int textW = MeasureText(btnTxt.c_str(), FONT_SIZE);
    const int textX = buttonX + (buttonWidth / 2) - (textW / 2);
    const int textY = buttonY;
    RaylibDrawText(btnTxt.c_str(), textX, textY, FONT_SIZE, BLACK);
}

bool MenuWindow::connected() {
    return playerConnected;
}

void MenuWindow::run() {
    calculate();
    update();
    draw();
}