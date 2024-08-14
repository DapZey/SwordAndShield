//
// Created by benra on 7/16/2024.
//

#include "Player.h"

void Player::draw() {
    DrawRectangle(activeWorldPosition.x,activeWorldPosition.y,PLAYER_SIZE, PLAYER_SIZE,BLUE);
}