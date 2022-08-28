#include "Game.h"
#include <raylib.h>
#include <iostream>
#include <vector>
#include <utility>
#include <set>
#include <unordered_set>
#include "Grid.h"
#include "rlgl.h"
#include "raymath.h"
#include "raygui.h"
#define MAX_COLORS_COUNT    21          // Number of colors available

struct ColorPalet {
    Color colors[MAX_COLORS_COUNT] = {
        DARKGRAY, MAROON, ORANGE, DARKGREEN, DARKBLUE, DARKPURPLE, DARKBROWN,
        GRAY, RED, GOLD, LIME, BLUE, VIOLET, BROWN, LIGHTGRAY, PINK, YELLOW,
        GREEN, SKYBLUE, PURPLE, BEIGE };

    
    Rectangle colorsRecs[MAX_COLORS_COUNT] = { 0 };     // Rectangles array
    int colorState[MAX_COLORS_COUNT] = { 0 };           // Color state: 0-DEFAULT, 1-MOUSE_HOVER
    Vector2 mousePoint = { 0.0f, 0.0f };

    // Fills colorsRecs data (for every rectangle)
    ColorPalet()
    {
        for (int i = 0; i < MAX_COLORS_COUNT; i++)
        {
            colorsRecs[i].x = 1000.0f + 40.0f * (i % 7) + 5.0f * (i % 7);
            colorsRecs[i].y = 20.0f + 40.0f * (i / 7) + 5.0f * (i / 7);
            colorsRecs[i].width = 40.0f;
            colorsRecs[i].height = 40.0f;
        }
   }
    Color update()
    {
        mousePoint = GetMousePosition();

        for (int i = 0; i < MAX_COLORS_COUNT; i++)
        {
            if (CheckCollisionPointRec(mousePoint, colorsRecs[i])) {
                colorState[i] = 1;
                return colors[i];
            }
        }
        return RAYWHITE;
       
    }
    void draw()
    {
        for (int i = 0; i < MAX_COLORS_COUNT; i++)    // Draw all rectangles
        {
            DrawRectangleRec(colorsRecs[i], Fade(colors[i], colorState[i] ? 0.6f : 1.0f));
            
        }
    }

};
// drawing color 
Color mainColor = BLACK;
ColorPalet palet;
Grid grid(10,10);
Camera2D cam;
Vector2 prevMousePos = GetMousePosition();
Vector2 mapGrid ;
std::set<std::pair<int,int>> rects;
Game::Game( int screenWidth,  int screenHeight, const char* title)
{
    cam.zoom = 1;
    cam.target = {100,100};
    cam.offset.x = GetScreenWidth() / 2.0f;
    cam.offset.y = GetScreenHeight() / 2.0f;
    init(screenWidth,screenHeight,title);
}

void Game::init(int screenWidth,int screenHeight,const char * title)
{
    InitWindow(screenWidth, screenHeight,title);

	SetTargetFPS(60);               
	while (!WindowShouldClose())    
    {
        // Update
        update();
        // draw 
        draw();
    }
    CloseWindow();
}

void Game::draw()
{
    BeginDrawing();
    ClearBackground(RAYWHITE);
    BeginMode2D(cam);
    grid.draw();
    int index = grid.row * (mapGrid.x / 20) + (mapGrid.y / 20);
    if (floor(mapGrid.x / 20) >= 0 && floor(mapGrid.x / 20) < grid.col && floor(mapGrid.y / 20) >= 0 && floor(mapGrid.y / 20) < grid.row) {

        DrawRectangle(mapGrid.x, mapGrid.y, 20, 20, BLUE);
    }
    EndMode2D();
    palet.draw();

    DrawText(TextFormat("rects red size :%d", rects.size()), 10,30,26, DARKGREEN);
    DrawFPS(10, 10);

    EndDrawing();
}
bool colorCheck(Color x, Color y)
{
    return (x.r == y.r) && (x.a == y.a) && (x.g == y.g) && (x.b == y.b);
}
void Game::update()
{
    if (IsMouseButtonDown(2))
    {
        Color tmp = palet.update();
        mainColor = (colorCheck(tmp, RAYWHITE)) ? mainColor : tmp;
    }
    zoomInOut();
}

void Game::zoomInOut()
{
    float mouseDelta = GetMouseWheelMove();

    float newZoom = cam.zoom + mouseDelta * 0.01f;
    if (newZoom <= 0)
        newZoom = 0.01f;

    cam.zoom = newZoom;

    Vector2 thisPos = GetMousePosition();

    Vector2 delta = Vector2Subtract(prevMousePos, thisPos);
    prevMousePos = thisPos;

    if (IsMouseButtonDown(0))
        cam.target = GetScreenToWorld2D(Vector2Add(cam.offset, delta), cam);

    if (IsKeyPressed(KEY_LEFT))
        cam.rotation += 10;
    else if (IsKeyPressed(KEY_RIGHT))
        cam.rotation -= 10;
    mapGrid = GetScreenToWorld2D(GetMousePosition(), cam);
    mapGrid.x = floorf(mapGrid.x / 20) * 20.0f;
    mapGrid.y = floorf(mapGrid.y / 20) * 20.0f;

    if (IsMouseButtonDown(1))
    {
       //    array[width * row + col] = value;  
        int index = grid.row * (mapGrid.x / 20) + (mapGrid.y / 20);
        if (floor(mapGrid.x / 20) >=0 && floor(mapGrid.x / 20) < grid.col && floor(mapGrid.y / 20) >= 0 && floor(mapGrid.y / 20) < grid.row) {
            grid.gridData[index].color = mainColor;
            std::cout << mapGrid.x << " " << mapGrid.y << std::endl;
        }
 
    }
    

}
