#pragma once
#include "GlobalVariables.h"

class Brick
{
public:
	Brick(int x, int y, int health, bool destroyed) : x(x), y(y), health(health), destroyed(false) {};
	Brick() = default;
	void TakeDamage();
	//Getters
	int getX() const { return x; }
	int getY() const { return y; }
	int getHealth() { return health; }
	bool getDestroyed() { return destroyed; }
	//Setters
	void setX(int xIn) { x = xIn; }
	void setY(int yIn) { y = yIn; }
	void setHealth(int healthIn) { health = healthIn; }
	void setDestroyed(bool destroyIn) { destroyed = destroyIn; }

private:
	//Default values
	int x = -100;
	int y = -100;
	int health;
	bool destroyed = true;
};

