#include "game.h"
#include <stdio.h>

void drawScene() {
    DrawTexture(grassSprite, 100, 50, WHITE);
    DrawTexturePro(playerSprite, playerSrc, playerDest, (Vector2){playerDest.width, playerDest.height}, 0, WHITE);
}

void input() {
    if (IsKeyDown(KEY_W) || IsKeyDown(KEY_UP)) {
        playerMoving = true;
        playerDir = UP;
        playerUp = true;
    }
    if(IsKeyDown(KEY_S) || IsKeyDown(KEY_DOWN)) {
        playerMoving = true;
        playerDir = DOWN;
        playerDown = true;
    }
    if(IsKeyDown(KEY_A) || IsKeyDown(KEY_LEFT)) {
        playerMoving = true;
        playerDir = LEFT;
        playerLeft = true;
    }
    if(IsKeyDown(KEY_D) || IsKeyDown(KEY_RIGHT)) {
        playerMoving = true;
        playerDir = RIGHT;
        playerRight = true;
    }
    if(IsKeyDown(KEY_Q)) {
        musicPaused = !musicPaused;
    }
    
}
void update() {
    
    running = !WindowShouldClose();

    if(playerMoving) {
        if(playerUp) playerDest.y -= playerSpeed;
        if(playerDown) playerDest.y += playerSpeed;
        if(playerLeft) playerDest.x -= playerSpeed;
        if(playerDown) playerDest.x += playerSpeed;
        if(frameCount % 8 == 1) playerFrame++;
    }

    frameCount++;
    if(playerFrame > 3) playerFrame = 0;

    printf("%s", playerDir);
    playerSrc.x = 0;
    playerSrc.x = playerSrc.width * playerFrame;
    playerSrc.y = playerSrc.height * playerDir;
    
    UpdateMusicStream(music);
    if(musicPaused) {
        PauseMusicStream(music);
    } else {
        ResumeMusicStream(music);
    }
    cam.target = (Vector2) {playerDest.x - (playerDest.width / 2), playerDest.y - (playerDest.height / 2)};
}
void render() {
    BeginDrawing();
        ClearBackground(bgColor);
        BeginMode2D(cam);
        drawScene();
        EndMode2D();
    EndDrawing();
}

void init() {
    InitWindow(screenWidth, screenHeight, "Sproutlings");
    SetExitKey(0);
    SetTargetFPS(60);
    grassSprite = LoadTexture("res/Tilesets/Grass.png");
    playerSprite = LoadTexture("res/Characters/BasicCharakterSpritesheet.png");
    playerSrc = (Rectangle){0, 0, 48, 48};
    playerDest = (Rectangle) {200, 200, 100, 100};
    InitAudioDevice();
    music = LoadMusicStream("res/music.mp3");
    musicPaused = false;
    PlayMusicStream(music);
    cam = (Camera2D){
        {screenWidth / 2, screenHeight / 2}, 
        {playerDest.x - (playerDest.width / 2), playerDest.y - (playerDest.height / 2)}, 
        0.0f, 
        1.0f 
    };
}

void quit() {
    UnloadTexture(grassSprite);
    UnloadTexture(playerSprite);
    UnloadMusicStream(music);
    CloseAudioDevice();
    CloseWindow();
}

int main() {
    
    init();
    
    while(running) {
        input();
        update();
        render();
    }

    quit();
    return 0;
}