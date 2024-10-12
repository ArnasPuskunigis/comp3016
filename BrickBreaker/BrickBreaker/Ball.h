#pragma once
#include "GlobalVariables.h"

class Ball
{

public:
	Ball(int x, int y, int velX, int velY) : x(x), y(y), velX(velX), velY(velY) {};
	void update(int leftX, int leftY, int brickX, int brickY);
	int getX() const { return x; }
	int getY() const { return y; }

private:
	int x;
	int y;
	int velX;
	int velY;

};
