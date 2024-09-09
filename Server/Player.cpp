//
// Created by benra on 7/16/2024.
//

#include "Player.h"
#include "iostream"
#include "MathUtils.h"
#define MOVEMENT_SPEED 5
void Player::move() {
    this->x += this->direction.x* MOVEMENT_SPEED;
    this->y += this->direction.y* MOVEMENT_SPEED;
}
void Player::spawnPointMapper() {
    if (levelID == 0){
        this->x = 50;
        this->y = 50;
    }
    if (levelID == 1){
        this->x = 100;
        this-> y = 50;
    }
}
bool Player::establishConnection() {
    if (!init){
        init = true;
        return true;
    }
    else {
        return false;
    }
}