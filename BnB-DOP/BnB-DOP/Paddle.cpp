#include "Paddle.h"

//Move the paddle to the left if not already all the way to the left
void Paddle::MoveLeft(int speed) {

	if (x > 10)
		x -= speed;

};

//Move the paddle to the right if not already all the way to the right, while checking for the width of the paddle
void Paddle::MoveRight(int speed, int width) {

	if (x < (WINDOW_WIDTH - width) - speed)
		x += speed;

};

