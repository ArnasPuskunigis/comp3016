#pragma once
#include "GlobalVariables.h"

class Paddle
{

public:
	Paddle(int x, int y) : x(x), y(y) {};
	void MoveLeft();
	void MoveRight();
	int getX() const { return x; }
	int getY() const { return y; }

private:
	int x;
	int y;

};

