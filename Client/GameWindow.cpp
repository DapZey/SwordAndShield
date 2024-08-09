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
    std::cout<<world.currentLevel->playerSpawnPoint.x<<"\n";
    ClearBackground(WHITE);
    EndDrawing();
}
void GameWindow::calculate() {
    world.SwitchLevel();
}
void GameWindow::update() {}
void GameWindow::run(){
    update();
    calculate();
    draw();
}