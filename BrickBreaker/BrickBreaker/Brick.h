#pragma once
#include "GlobalVariables.h"

class Brick
{
public:
	Brick(int x, int y, int health, bool destroyed) : x(x), y(y), health(1), destroyed(false) {};
	void TakeDamage();
	int getX() const { return x; }
	int getY() const { return y; }
	int getHealth() { return health; }
	bool getDestroyed() { return destroyed; }

private:
	int x;
	int y;
	int health;
	bool destroyed;
};

