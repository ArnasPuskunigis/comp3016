#include "Ball.h"
#include <iostream>
#include "Brick.h"

using namespace std;

void Ball::update(int paddleX, int paddleY, Brick allBricks[], int paddleWidth, bool affectSpeed, bool doubleSpeed) {

	if (affectSpeed) {
		x += velX;
		y += velY;
		if (doubleSpeed) {
			x += velX;
			y += velY;
		}
	}

	//Check for if this should increase the speed of the ball (character specific issue)
	if (affectSpeed) {

		//Ceiling bounce
		if (y <= 10) {
			velY = -velY;
			exit;
		}

		//Floor collision/game over
		if (y >= (WINDOW_HEIGHT - 200) - BALL_SIZE) {
			destroyBall();
			exit;
		}

		//wall bounce
		if (x <= 0 + 10 || x >= (WINDOW_WIDTH - BALL_SIZE) - 10) {
			velX = -velX;
			exit;
		}

		int tempBrickX;
		int tempBrickY;
		bool brickDestroyed;
		bool interacted = false;

		for (int i = 0; i < 64; i++) {
			
			if (!interacted) {
				tempBrickX = allBricks[i].getX();
				tempBrickY = allBricks[i].getY();
				brickDestroyed = allBricks[i].getDestroyed();

				//brick bounce (bottom part)
				if (y <= tempBrickY + BRICK_HEIGHT && y >= tempBrickY + BRICK_HEIGHT - 1 && x >= tempBrickX - BALL_SIZE && x <= ((tempBrickX + BRICK_WIDTH) - 1) + BALL_SIZE && brickDestroyed == false) {
					//brick to take damage
					velY = -velY;
					allBricks[i].TakeDamage();
					interacted = true;
					exit;
				}
				//brick bounce (top part)
				else if (y <= tempBrickY + 1 && y >= tempBrickY - BALL_SIZE && x >= tempBrickX + 1 && x <= ((tempBrickX + BRICK_WIDTH) - 1) + BALL_SIZE && brickDestroyed == false) {
					//brick to take damage
					velY = -velY;
					allBricks[i].TakeDamage();
					interacted = true;
					exit;
				}
				//brick bounce (left part)
				else if (y <= tempBrickY + BRICK_HEIGHT - 1 && y >= tempBrickY + 1 && x >= tempBrickX - BALL_SIZE && x <= tempBrickX + BRICK_WIDTH / 2 && brickDestroyed == false && velX >= 0) {
					//brick to take damage
					velX = -velX;
					allBricks[i].TakeDamage();
					interacted = true;
					exit;
				}
				//brick bounce (right part)
				else if (y <= tempBrickY + BRICK_HEIGHT - 1 && y >= tempBrickY + 1 && x >= tempBrickX + BRICK_WIDTH / 2 && x <= tempBrickX + BRICK_WIDTH && brickDestroyed == false && velX <= 0) {
					//brick to take damage
					velX = -velX;
					allBricks[i].TakeDamage();
					interacted = true;
					exit;
				}
			}

			//Ball bounce off paddle
			if (y >= (WINDOW_HEIGHT - (WINDOW_HEIGHT - paddleY)) - BALL_SIZE && x >= paddleX && x <= paddleX + paddleWidth && velY >= 0 && y <= paddleY + PADDLE_HEIGHT) {
				velY = -velY;
				exit;
			}

		};
	}
	else {
		//Ball bounce off paddle
		if (y >= (WINDOW_HEIGHT - (WINDOW_HEIGHT - paddleY)) - BALL_SIZE && x >= paddleX && x <= paddleX + paddleWidth && velY >= 0 && y <= paddleY + PADDLE_HEIGHT) {
			velY = -velY;
			exit;
		}
	}

};
