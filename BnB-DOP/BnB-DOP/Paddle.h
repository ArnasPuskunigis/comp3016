#pragma once
#include "GlobalVariables.h"

class Paddle
{

public:
	Paddle(int x, int y) : x(x), y(y) {};
	Paddle() = default;
	void MoveLeft(int speed);
	void MoveRight(int speed, int width);
	//Getters for paddle x and y
	int getX() const { return x; }
	int getY() const { return y; }

private:
	int x;
	int y;

};

