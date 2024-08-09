//
// Created by benra on 8/9/2024.
//

#ifndef CLIENT_LEVEL_H
#define CLIENT_LEVEL_H

#include "raylib.h"
#define SPAWN_POINT_SIZE 50
class Level {
public:
    void setSpawnPoint(Vector2 point);
    Vector2 playerSpawnPoint;
    void render();
};


#endif //CLIENT_LEVEL_H
