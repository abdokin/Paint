#pragma once
#include <raylib.h>
extern int screenHeight;
extern int screenWidth;
class Eyes
{
public:
    Vector2 scleraLeftPosition = { screenWidth / 2.0f -100,screenHeight / 2.0f };
    Vector2 scleraRightPosition = { screenWidth / 2.0f +100 , screenHeight / 2.0f };
    float scleraRadius = 80;
    Vector2 irisLeftPosition = { screenWidth / 2.0f -100, screenHeight / 2.0f };
    Vector2 irisRightPosition = { screenWidth / 2.0f +100, screenHeight / 2.0f };
    float irisRadius = 24;

    float angle = 0.0f;
    float dx = 0.0f, dy = 0.0f, dxx = 0.0f, dyy = 0.0f;
    void update();
    void draw();
};

