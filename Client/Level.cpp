//
// Created by benra on 8/9/2024.
//

#include "Level.h"
void Level::render() {
    DrawRectangle(playerSpawnPoint.x,playerSpawnPoint.y,SPAWN_POINT_SIZE,SPAWN_POINT_SIZE, RED);
    DrawRectangleRec(exit,GREEN);
}
void Level::setSpawnPoint(Vector2 point) {
    this ->playerSpawnPoint = point;
}
void Level::setExit(RaylibRectangle rectangle) {
    this->exit =rectangle;
}