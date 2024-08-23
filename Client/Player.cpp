//
// Created by benra on 7/16/2024.
//

#include "Player.h"
#define PLAYER_LERP_RATE 0.5f
#define LERP_DISTANCE_THRESHOLD 1.0f
#include "iostream"
void Player::draw() {
    DrawRectangle(smoothedWorldPosition.x,smoothedWorldPosition.y,PLAYER_SIZE, PLAYER_SIZE,BLUE);
}
int Player::move() {
    Vector2 inputDirection = {0,0};
    int changed = 0;
    if (IsKeyDown(KEY_W)){
        inputDirection.y--;
    }
    if (IsKeyDown(KEY_S)){
        inputDirection.y++;
    }
    if (IsKeyDown(KEY_A)){
        inputDirection.x--;
    }
    if (IsKeyDown(KEY_D)){
        inputDirection.x++;
    }
    if (activeDirection != vectorMapper(inputDirection)){
        activeDirection = vectorMapper(inputDirection);
        changed = 1;
    }
    inputDirection = MathUtils::normalize(inputDirection);
    activeWorldPosition.x += inputDirection.x * MOVEMENT_SPEED;
    activeWorldPosition.y += inputDirection.y* MOVEMENT_SPEED;
    smoothedWorldPosition = MathUtils::Vector2Lerp(smoothedWorldPosition, activeWorldPosition, PLAYER_LERP_RATE);
    if (MathUtils::Vector2Distance(smoothedWorldPosition, activeWorldPosition) < LERP_DISTANCE_THRESHOLD) {
        smoothedWorldPosition = activeWorldPosition;
    }
    if (inputDirection.x != 0){
        std::cout<<activeWorldPosition.x<<"\n";
    }
    return changed;
}