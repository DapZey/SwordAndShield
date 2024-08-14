//
// Created by benra on 7/22/2024.
//

#include "GameWindow.h"
GameWindow::GameWindow(Protocol &p) {
    this->protocol = &p;
    this->world.user.activeWorldPosition = this->world.currentLevel->playerSpawnPoint;
}
void GameWindow::draw() {
    BeginDrawing();
    this->world.currentLevel->render();
    this->world.user.draw();
    ClearBackground(WHITE);
    EndDrawing();
}
void GameWindow::calculate() {
}
void GameWindow::update() {
    int level = world.SwitchLevel(); //TO BE CHANGED ONCE DOORS ARE MADE
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