#pragma once
#include "GlobalVariables.h"

class Brick
{
public:
	Brick(int x, int y, int health, bool destroyed) : x(x), y(y), health(health), destroyed(false) {};
	Brick() = default;
	void TakeDamage();
	int getX() const { return x; }
	int getY() const { return y; }
	int getHealth() { return health; }
	bool getDestroyed() { return destroyed; }
	void setX(int xIn) { x = xIn; }
	void setY(int yIn) { y = yIn; }
	void setHealth(int healthIn) { health = healthIn; }
	void setDestroyed(bool destroyIn) { destroyed = destroyIn; }

private:
	int x;
	int y;
	int health;
	bool destroyed;
};

