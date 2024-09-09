//
// Created by benra on 7/22/2024.
//

#include "GameWindow.h"
#define CAMERA_LERP_RATE 20.0f
#define TICK_RATE_DELTA 0.0069f
#define LERP_DISTANCE_THRESHOLD 0.1f
#define SCREEN_WIDTH 1280
#define SCREEN_HEIGHT 720
GameWindow::GameWindow(Protocol &p) {
    this->protocol = &p;
    this->world.user.activeWorldPosition = this->world.currentLevel->playerSpawnPoint;
    playerFollowCamera = {0};
    playerFollowCamera.target={float(SCREEN_WIDTH)/ 2,float (SCREEN_HEIGHT) / 2};
    playerFollowCamera.offset = (Vector2){ float(SCREEN_WIDTH)/ 2, float (SCREEN_HEIGHT) / 2 };
    playerFollowCamera.rotation = 0.0f;
    playerFollowCamera.zoom = 1.0f;
}
void GameWindow::draw() {
    BeginDrawing();
    ClearBackground(WHITE);
    RaylibDrawText(TextFormat("FPS: %i", GetFPS()),50,50,20,GREEN);
    BeginMode2D(playerFollowCamera);
    this->world.currentLevel->render();
    this->world.user.draw();
    if (this->world.user.level == this->world.other.level){
        this->world.other.drawStatic();
    }
    EndMode2D();
    EndDrawing();
}
void GameWindow::calculate() {
}
void GameWindow::update() {
    std::chrono::time_point<std::chrono::steady_clock> currentFrameTime = std::chrono::steady_clock::now();
    int elapsed = std::chrono::duration_cast<std::chrono::milliseconds>(currentFrameTime - gameTime).count();
    int ticksPassed = std::floor(elapsed / TICK_RATE_MS);
    int moveFlag = 0;
    Vector2 dir = {0,0};
    // Update gameTime to the last processed tick time
    if (ticksPassed > 0) {
        gameTime += std::chrono::milliseconds(ticksPassed * TICK_RATE_MS);
    }
    for (int i = 0; i< ticksPassed; i++){
//        std::string con = "connected!";
//        protocol->network->send(con);
        moveFlag = world.user.move();
        world.other.moveStatic();
        if (moveFlag == 1){
            dir = Player::directionMapper(world.user.activeDirection);
        }
        if (MathUtils::Vector2Distance(playerFollowCamera.target, {world.user.activeWorldPosition.x,world.user.activeWorldPosition.y}) < LERP_DISTANCE_THRESHOLD) {
            playerFollowCamera.target = {world.user.activeWorldPosition.x,world.user.activeWorldPosition.y};
        }
        else {
            playerFollowCamera.target = MathUtils::Vector2Lerp(playerFollowCamera.target, {world.user.activeWorldPosition.x,world.user.activeWorldPosition.y}, CAMERA_LERP_RATE * TICK_RATE_DELTA);
        }
        playerFollowCamera.offset = (Vector2){ float(SCREEN_WIDTH)/ 2, float (SCREEN_HEIGHT) / 2 };
    }
    int level = world.SwitchLevel(); //TO BE CHANGED ONCE DOORS ARE MADE
    bool levelFlag = false;
    if (prevLevel != level){
        levelFlag = true;
        prevLevel = level;
    }
    this->protocol->GameRun(levelFlag,level, moveFlag, dir, world.user, world.other);
}
void GameWindow::run(){
    update();
    calculate();
    draw();
}