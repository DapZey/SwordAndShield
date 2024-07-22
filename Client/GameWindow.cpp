//
// Created by benra on 7/22/2024.
//

#include "GameWindow.h"
GameWindow::GameWindow(Protocol &p) {
    this->protocol = &p;
}
void GameWindow::draw() {
    BeginDrawing();
    ClearBackground(WHITE);
    EndDrawing();
}
void GameWindow::calculate() {}
void GameWindow::update() {}
void GameWindow::run(){
    update();
    calculate();
    draw();
}