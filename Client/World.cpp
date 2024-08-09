//
// Created by benra on 8/9/2024.
//

#include "World.h"
World::World() {
    home.setSpawnPoint({50,50});
    levelMap[0] = &home;
    level1.setSpawnPoint({100,50});
    levelMap[1] = &level1;
    currentLevel = levelMap[currentLevelId];
}

void World::SwitchLevel() {
    if (IsKeyDown(KEY_RIGHT)){
        if (currentLevelId < levelLimitUpper){
            currentLevelId++;
            currentLevel = levelMap[currentLevelId];
        }
    }
    if (IsKeyDown(KEY_LEFT)){
        if (currentLevelId > levelLimitLower){
            currentLevelId--;
            currentLevel = levelMap[currentLevelId];
        }
    }
}