#pragma once
#include<vector>
#include "raylib.h"
class Grid
{
private:

public:
	float start;
	int row, col;
	struct data {
		Vector2 vec;
		Color color;
	};
	std::vector<data> gridData;
	Grid(int row,int col);
	void draw();
};

