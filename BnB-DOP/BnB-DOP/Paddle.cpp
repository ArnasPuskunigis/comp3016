#include "Paddle.h"

void Paddle::MoveLeft(int speed) {

	if (x > 0)
		x -= speed;

};

void Paddle::MoveRight(int speed) {

	if (x < WINDOW_WIDTH - speed)
		x += speed;

};

