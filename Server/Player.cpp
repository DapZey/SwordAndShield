//
// Created by benra on 7/16/2024.
//

#include "Player.h"
#include "iostream"
void Player::move() {
    this->x += this->direction.x;
    if (xPrev != x){
        std::cout<<xPrev<<"\n";
        xPrev = x;
    }
    this->y += this->direction.y;
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