#include "Ball.h"
#include <iostream>
#include "Brick.h"

using namespace std;

void Ball::update(int paddleX, int paddleY, Brick allBricks[]) {

	x += velX;
	y += velY;

	//Ceiling bounce
	if (y <= 0) {
		velY = -velY;
		exit;
	}

	//Floor bouce/game over
	if (y >= WINDOW_HEIGHT - BALL_SIZE) {
		velY = -velY;
		cout << "game over";
		destroyBall();
		exit;
	}

	//wall bounce
	if (x <= 0 || x >= WINDOW_WIDTH - BALL_SIZE) {
		velX = -velX;
		exit;
	}

	int tempBrickX;
	int tempBrickY;
	bool brickDestroyed;

	for (int i = 0; i < 10; i++) {
		tempBrickX = allBricks[i].getX();
		tempBrickY = allBricks[i].getY();
		brickDestroyed = allBricks[i].getDestroyed();

		//brick bounce (bottom part)
		if (y <= tempBrickY + BRICK_HEIGHT && y >= tempBrickY + BRICK_HEIGHT - 1 && x >= tempBrickX - BALL_SIZE && x <= ((tempBrickX + BRICK_WIDTH) - 1) + BALL_SIZE && brickDestroyed == false) {
			//brick to take damage
			velY = -velY;
			allBricks[i].TakeDamage();
			exit;
		}

		//brick bounce (top part)
		if (y <= tempBrickY + 1 && y >= tempBrickY - BALL_SIZE && x >= tempBrickX + 1 && x <= ((tempBrickX + BRICK_WIDTH) - 1) + BALL_SIZE && brickDestroyed == false) {
			//brick to take damage
			velY = -velY;
			allBricks[i].TakeDamage();
			exit;
		}

		//brick bounce (left part)
		if (y <= tempBrickY + BRICK_HEIGHT - 1 && y >= tempBrickY + 1 && x >= tempBrickX - BALL_SIZE && x <= tempBrickX + BRICK_WIDTH / 2 && brickDestroyed == false && velX >= 0) {
			//brick to take damage
			velX = -velX;
			allBricks[i].TakeDamage();
			exit;
		}

		//brick bounce (right part)
		if (y <= tempBrickY + BRICK_HEIGHT - 1 && y >= tempBrickY + 1 && x >= tempBrickX + BRICK_WIDTH / 2 && x <= tempBrickX + BRICK_WIDTH && brickDestroyed == false && velX <= 0) {
			//brick to take damage
			velX = -velX;
			allBricks[i].TakeDamage();
			exit;
		}

	};

	//paddle bounce
	if (y >= (WINDOW_HEIGHT - (WINDOW_HEIGHT - paddleY)) - BALL_SIZE && x >= paddleX && x <= paddleX + PADDLE_WIDTH) {
		velY = -velY;
		exit;
	}

	//if (x <= PADDLE_WIDTH && y >= leftY && y <= leftY + PADDLE_HEIGHT) {
	//	velX = BALL_SPEED;
	//}

	//if (x >= WINDOW_WIDTH - PADDLE_WIDTH - BALL_SIZE && y >= rightY && y <= rightY + PADDLE_HEIGHT) {
	//	velX = -BALL_SPEED;
	//}

};
