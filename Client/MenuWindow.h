//
// Created by Moshe on 7/16/2024.
//


#ifndef MENUWINDOW_H
#define MENUWINDOW_H

#define FONT_SIZE 40
#define MAX_IP_INPUT 15 // XXX.XXX.XXX.XXX
#define CONNECTION_STATUS_U "Unconnected"
#define CONNECTION_STATUS_C "Connected"
#include "Protocol.h"
#include "raylib.h"
#include  <iostream>
#include <cmath>


class MenuWindow {
private:
    float fieldW;
    float fieldH;
    float fieldX;
    float fieldY;
    float buttonWidth;
    float buttonHeight;
    float buttonX;
    float buttonY;
    bool playerConnected = false;
    const int windowWidth;
    const int windowHeight;
    bool textFieldToggle = false;
    std::string connectionStatus = CONNECTION_STATUS_U;
    std::string textFieldBuffer = DEFAULT_IP;
    bool isTxtFieldSelected = false;
    Protocol* protocol;
    void update();
    void updateTextField();
    void calculate();
    void draw();
    void drawConnectionStatus();
    void drawTextField();
    void drawButton();
public:
    MenuWindow(int windowWidth, int windowHeight, Protocol& p);
    void run();
    bool connected();
};



#endif //MENUWINDOW_H
