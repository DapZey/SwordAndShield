//
// Created by benra on 8/9/2024.
//

#ifndef CLIENT_WORLD_H
#define CLIENT_WORLD_H
#include <map>
#include "Level.h"
class World {
    std::map<int, Level*> levelMap;
    int currentLevelId = 0;
    int levelLimitUpper = 1;
    int levelLimitLower = 0;
    Level home;
    Level level1;
public:
    Level* currentLevel;
    World();
    void SwitchLevel();
};


#endif //CLIENT_WORLD_H
