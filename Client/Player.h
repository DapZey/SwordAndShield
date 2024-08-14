//
// Created by benra on 7/16/2024
//

#ifndef CLIENT_PLAYER_H
#define CLIENT_PLAYER_H
#include "raylib.h"
#define PLAYER_SIZE 50
enum direction{
    up,down,left,right,upRight,upLeft,downRight,downLeft,idle
};
class Player {
    static Vector2 directionMapper(direction d){
        if (d == idle){
            return {0,0};
        }
        if (d == down){
            return {0,1};
        }
        if (d == left){
            return {-1,0};
        }
        if (d == right){
            return {1,0};
        }
        if (d == up){
            return {0,-1};
        }
        if (d == upLeft){
            return {-1,-1};
        }
        if (d == upRight){
            return {1,-1};
        }
        if (d == downRight){
            return {1,1};
        }
        if (d == downLeft){
            return {-1,1};
        }
        return {0,0};
    }
public:
    Vector2 activeWorldPosition = {0,0};
    int level;
    void draw();
    void move();
};


#endif //CLIENT_PLAYER_H
