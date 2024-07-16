//
// Created by Moshe on 7/16/2024.
//


#ifndef MENUWINDOW_H
#define MENUWINDOW_H

#include "raylib.h"
#include  <iostream>


class MenuWindow {
private:
    bool playerConnected = false;
    unsigned const int windowWidth;
    unsigned const int windowHeight;
    void update();
    void calculate();
    void draw();
public:
    MenuWindow(unsigned int windowWidth, unsigned int windowHeight);
    void run();
    bool connected();
};



#endif //MENUWINDOW_H
