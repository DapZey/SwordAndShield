//
// Created by Moshe on 7/16/2024.
//


#ifndef MENUWINDOW_H
#define MENUWINDOW_H

#define FONT_SIZE 40
#define MAX_IP_INPUT 15 // XXX.XXX.XXX.XXX

#include "raylib.h"
#include  <iostream>
#include <cmath>


class MenuWindow {
private:
    bool playerConnected = false;
    const int windowWidth;
    const int windowHeight;
    std::string connectionStatus = "Unconnected";
    std::string textFieldBuffer = "255.255.255.255";

    void update();
    void updateTextField();
    void calculate();
    void draw();
    void drawConnectionStatus();
    void drawTextField();
    void drawButton();
public:
    MenuWindow(int windowWidth, int windowHeight);
    void run();
    bool connected();
};



#endif //MENUWINDOW_H
