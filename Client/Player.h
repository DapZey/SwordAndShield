//
// Created by benra on 7/16/2024
//

#ifndef CLIENT_PLAYER_H
#define CLIENT_PLAYER_H
#include "raylib.h"
#include "MathUtils.h"
#include "chrono"
#include "vector"
#include "Mapper.h"
#define PLAYER_SIZE 50
#define MOVEMENT_SPEED 15
enum Direction{
    up,down,left,right,upRight,upLeft,downRight,downLeft,idle
};
class Player {
public:
    Vector2 activeWorldPosition = {0,0};
    Vector2 smoothedWorldPosition = {0,0};
    int level = 0;
    Direction activeDirection = idle;
    void draw();
    int move();
    static Direction vectorMapper(Vector2 v) {
        if (v.x == 0 && v.y == 0) {
            return idle;
        }
        if (v.x == 0 && v.y == 1) {
            return down;
        }
        if (v.x == -1 && v.y == 0) {
            return left;
        }
        if (v.x == 1 && v.y == 0) {
            return right;
        }
        if (v.x == 0 && v.y == -1) {
            return up;
        }
        if (v.x == -1 && v.y == -1) {
            return upLeft;
        }
        if (v.x == 1 && v.y == -1) {
            return upRight;
        }
        if (v.x == 1 && v.y == 1) {
            return downRight;
        }
        if (v.x == -1 && v.y == 1) {
            return downLeft;
        }
        return idle;
    }
    static Vector2 directionMapper(Direction d){
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
};


#endif //CLIENT_PLAYER_H
