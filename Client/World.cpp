//
// Created by benra on 8/9/2024.
//

#include "World.h"
World::World() {
    home.setSpawnPoint({50,50});
    home.setExit({200,200,50,50});
    levelMap[0] = &home;
    level1.setSpawnPoint({100,50});
    level1.setExit({200,250,50,50});
    levelMap[1] = &level1;
    currentLevel = levelMap[currentLevelId];
    user.level = 0;
}

int World::SwitchLevel() {
    if (IsKeyDown(KEY_RIGHT)){
        if (currentLevelId < levelLimitUpper){
            currentLevelId++;
            currentLevel = levelMap[currentLevelId];
            user.activeWorldPosition = {currentLevel->playerSpawnPoint};
            user.level = currentLevelId;
        }
    }
    if (IsKeyDown(KEY_LEFT)){
        if (currentLevelId > levelLimitLower){
            currentLevelId--;
            currentLevel = levelMap[currentLevelId];
            user.activeWorldPosition = {currentLevel->playerSpawnPoint};
            user.level = currentLevelId;
        }
    }
    return currentLevelId;
}