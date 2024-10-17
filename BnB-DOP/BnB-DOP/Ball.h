#pragma once
#include "GlobalVariables.h"
#include "Brick.h"

class Ball
{

public:
	Ball(int x, int y, int velX, int velY, bool destroyed) : x(x), y(y), velX(velX), velY(velY), destroyed(destroyed) {};
	Ball() = default;
	void update(int leftX, int leftY, Brick allBricks[]);
	int getX() { return x; }
	int getY() { return y; }
	bool getDestroyed() { return destroyed; }
	void destroyBall() { destroyed = true; }

private:
	int x;
	int y;
	int velX;
	int velY;
	bool destroyed;
};
