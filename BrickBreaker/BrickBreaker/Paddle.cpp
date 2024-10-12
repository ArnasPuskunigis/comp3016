#include "Paddle.h"

void Paddle::MoveLeft() {

	if (x > 0)
		x -= PADDLE_SPEED;

};

void Paddle::MoveRight() {

	if (x < WINDOW_WIDTH - PADDLE_SPEED)
		x += PADDLE_SPEED;

};

