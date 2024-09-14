//
// Created by benra on 9/9/2024.
//

#include "Animation.h"
#include "iostream"
RaylibRectangle Animation::getAnimationPositions() {
    return {textureSize.x,textureSize.y, currentPosition.x,currentPosition.y};
}
Animation::Animation(std::string animSource, Vector2 size, std::vector<Vector2> positions, int speed, bool loop) {
    texture = LoadTexture(animSource.c_str());
    textureSize = size;
    texturePositions = positions;
    animationSpeed = speed;
    currentPosition = texturePositions[0];
    numSteps = positions.size();
    this->loop = loop;
}
bool Animation::runAnimation() {
    if (!startLock){
        animationStart = std::chrono::steady_clock::now();
        startLock = true;
    }
    animationTimeCurrent = std::chrono::steady_clock::now();
    int elapsed = std::chrono::duration_cast<std::chrono::milliseconds>(animationTimeCurrent -animationStart).count();
    if ((elapsed) > animationSpeed){
        animationTimeCurrent = animationStart = std::chrono::steady_clock::now();
        animationStep++;
        if (animationStep > (numSteps -1)){
            animationStep = 0;
            if (!loop){
                this->resetAnimation();
                return false;
            }
        }
        currentPosition = texturePositions[animationStep];
    }
//    std::cout<<"step: "<<animationStep<<"\n";
    return true;
}
void Animation::resetAnimation() {
    animationStep = 0;
    currentPosition = texturePositions[0];
    startLock = false;
//    std::cout<<"anim reset!\n";
}
