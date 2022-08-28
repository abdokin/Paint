#include "Grid.h"
#include <raylib.h>
#include <random>
#include <iostream>

extern int screenHeight;
extern int screenWidth;
int SQUARE_SIZE = 20;
static Vector2 offset;
Color generateRandomColor()
{
    std::random_device dev;
    std::mt19937 rng(dev());
    std::uniform_int_distribution<std::mt19937::result_type> dist255(0, 255);// distribution in range [1, 6]
    int r, g, b;
    r = dist255(rng);
    g = dist255(rng);
    b = dist255(rng);
    //std::cout << r << " " << b << " " << " " << g << " \n";
    Color res = { r,g,b,1 };
    return res;
}
Grid::Grid(int row,int col)
{
    this->row = row;
    this->col = col;
    this->start = 100;
    offset.x = screenWidth % SQUARE_SIZE;
    offset.y = screenHeight % SQUARE_SIZE;
    for (int i = 0; i < row; i++)
    {
        for (int j = 0; j < col; j++)
        {
            Vector2 tmp = { i * SQUARE_SIZE ,j * SQUARE_SIZE };
            data t = { tmp,generateRandomColor() };
            gridData.push_back(t);
        }
    }
}

struct gridData {
        
};
void Grid::draw()
{
    DrawRectangleLines(-1,-1,SQUARE_SIZE *col +2,SQUARE_SIZE *row +2,BLACK);

    for (auto &it : gridData)
    {
            DrawRectangle(it.vec.x,it.vec.y,20,20, it.color);
    }
}
