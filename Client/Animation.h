//
// Created by benra on 9/9/2024.
//

#ifndef CLIENT_ANIMATION_H
#define CLIENT_ANIMATION_H

#include "Player.h"
#include "string"
#include "cstring"
class Animation {
    //player has animation manager that has animations, in the players draw function it
    // will get the texture and rectangle by calling the function to get the animation state
    //when a players input changes it calls the animation manager to change its state there
    //player has animationManager
    //animationmanager has a list of animations and can change animation state and return state
    //animation has texture data, and cycles through texture positions based on time
    //running non-looped animations
    //Animation a("Xmove.png",{0,0},{{},{},{}},1000,false);
    //    bool x = true;
    //        if (x){
    //            x = a.runAnimation();
    //        }
    Vector2 textureSize = {0,0};
    Vector2 currentPosition = {0,0};
    int animationSpeed = 0;
    int animationStep = 0;
    int numSteps = 0;
    std::vector<Vector2> texturePositions;
    std::chrono::time_point<std::chrono::steady_clock> animationStart = std::chrono::steady_clock::now();
    std::chrono::time_point<std::chrono::steady_clock> animationTimeCurrent = std::chrono::steady_clock::now();
    bool loop = false;
    bool startLock = false;
public:
    Texture2D texture;
    Animation(std::string animSource, Vector2 size, std::vector<Vector2> positions, int speed, bool loop);
    RaylibRectangle getAnimationPositions();
    bool runAnimation();
    void resetAnimation();
};


#endif //CLIENT_ANIMATION_H
