#include <raylib.h>

enum Direction {
    UP = 1, 
    DOWN = 0, 
    LEFT = 2, 
    RIGHT = 3
};

const int screenWidth = 1000;
const int screenHeight = 480;
bool running = true;
Color bgColor = {147, 211, 196, 255};
Texture2D grassSprite;
Texture2D playerSprite;
Rectangle playerSrc;
Rectangle playerDest;
float playerSpeed = 3.0f;
bool musicPaused;
Music music;
Camera2D cam;
bool playerMoving = false;
enum Direction playerDir;
bool playerUp, playerDown, playerRight, playerLeft;
int frameCount;
int playerFrame;