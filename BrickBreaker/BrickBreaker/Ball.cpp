#include "Ball.h"
#include <iostream>

using namespace std;

void Ball::update(int paddleX, int paddleY, int brickX, int brickY) {

	x += velX;
	y += velY;

	//Ceiling bounce
	if (y <= 0) {
		velY = -velY;
	}

	//Floor bouce/game over
	if (y >= WINDOW_HEIGHT - BALL_SIZE) {
		velY = -velY;
		cout << "game over";
	}

	//wall bounce
	if (x <= 0 || x >= WINDOW_WIDTH - BALL_SIZE) {
		velX = -velX;
	}

	//paddle bounce
	if (y >= (WINDOW_HEIGHT - (WINDOW_HEIGHT - paddleY)) - BALL_SIZE && x >= paddleX && x <= paddleX + PADDLE_WIDTH) {
		velY = -velY;
	}

	//brick bounce (bottom part)
	if (y <= brickY + BRICK_HEIGHT && y >= brickY + BRICK_HEIGHT / 2) {
		//brick to take damage
		velY = -velY;
	}

	//brick bounce (top part)
	if (y <= brickY + BRICK_HEIGHT / 2 && y >= brickY) {
		//brick to take damage
		velY = -velY;
	}

	//if (x <= PADDLE_WIDTH && y >= leftY && y <= leftY + PADDLE_HEIGHT) {
	//	velX = BALL_SPEED;
	//}

	//if (x >= WINDOW_WIDTH - PADDLE_WIDTH - BALL_SIZE && y >= rightY && y <= rightY + PADDLE_HEIGHT) {
	//	velX = -BALL_SPEED;
	//}

};
