#pragma once
class Game
{
private:
public:
	Game(int screenWidth, int screenHeight, const char* title);
	void init(int screenWidth, int screenHeight, const char * title);
	void draw();
	void update();
	void zoomInOut();
};

