#pragma once
#include "GlobalVariables.h"
#include "Brick.h"

class Ball
{

public:
	Ball(int x, int y, int velX, int velY) : x(x), y(y), velX(velX), velY(velY) {};
	void update(int leftX, int leftY, Brick allBricks[]);
	int getX() const { return x; }
	int getY() const { return y; }

private:
	int x;
	int y;
	int velX;
	int velY;

};
