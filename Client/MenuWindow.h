//
// Created by Moshe on 7/16/2024.
//


#ifndef MENUWINDOW_H
#define MENUWINDOW_H

#define FONT_SIZE 75

#include "raylib.h"
#include  <iostream>
#include <cmath>


class MenuWindow {
private:
    bool playerConnected = false;
    const int windowWidth;
    const int windowHeight;
    std::string connectionStatus = "Unconnected";

    void update();
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
