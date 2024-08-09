//
// Created by benra on 7/22/2024.
//

#include "GameWindow.h"
GameWindow::GameWindow(Protocol &p) {
    this->protocol = &p;
}
void GameWindow::draw() {
    BeginDrawing();
    this->world.currentLevel->render();
    ClearBackground(WHITE);
    EndDrawing();
}
void GameWindow::calculate() {
}
void GameWindow::update() {
    int level = world.SwitchLevel();
    bool levelFlag = false;
    if (prevLevel != level){
        levelFlag = true;
        prevLevel = level;
    }
    this->protocol->GameRun(levelFlag,level);
}
void GameWindow::run(){
    update();
    calculate();
    draw();
}