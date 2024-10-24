#include "Game.h"
#include "SDL.h"
#include <array>
#include <iostream>
#include <random>
#include <SDL_image.h>

Game::Game() {
	gameState = 1;
	init = false;
	ballsInit = false;
	/*if (gameState == 1) {
		init = true;
		SDL_Init(SDL_INIT_VIDEO);
		window = SDL_CreateWindow("Pong Main Menu", SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, WINDOW_WIDTH, WINDOW_HEIGHT, SDL_WINDOW_SHOWN);
		renderer = SDL_CreateRenderer(window, -1, SDL_RENDERER_ACCELERATED);
	}
	else if (gameState == 2) {
		init = true;
		SDL_Init(SDL_INIT_VIDEO);
		window = SDL_CreateWindow("Pong Dice Roll", SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, WINDOW_WIDTH, WINDOW_HEIGHT, SDL_WINDOW_SHOWN);
		renderer = SDL_CreateRenderer(window, -1, SDL_RENDERER_ACCELERATED);
	}
	else if (gameState == 3) {
		init = true;
		SDL_Init(SDL_INIT_VIDEO);
		window = SDL_CreateWindow("Pong", SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, WINDOW_WIDTH, WINDOW_HEIGHT, SDL_WINDOW_SHOWN);
		renderer = SDL_CreateRenderer(window, -1, SDL_RENDERER_ACCELERATED);
	}
	else if (gameState == 4) {
		init = true;
		SDL_Init(SDL_INIT_VIDEO);
		window = SDL_CreateWindow("Pong Game Over", SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, WINDOW_WIDTH, WINDOW_HEIGHT, SDL_WINDOW_SHOWN);
		renderer = SDL_CreateRenderer(window, -1, SDL_RENDERER_ACCELERATED);
	}*/

	paddle = new Paddle(WINDOW_WIDTH / 2 - PADDLE_WIDTH / 2, WINDOW_HEIGHT - 20);
	for (int i = 1; i < 11; i++) {
		bricks[i - 1] = Brick((i * BRICK_WIDTH) + 20, i * 20, 2, false);
	}

	//brick = new Brick(WINDOW_WIDTH / 2 - BRICK_WIDTH / 2, 100, 1, false);
	
};

Game::~Game() {

	SDL_DestroyRenderer(renderer);
	SDL_DestroyWindow(window);
	SDL_Quit();
};

int GetActiveBalls(Ball allBalls[], int ballCount) {
	int balls = ballCount;
	for (int i = 0; i < 12; i++) {
		if (allBalls[i].getDestroyed()) {
			balls--;
		}
	}
	return balls;
}

void Game::Run() {

	while (true) {
		Input();

		if (gameState == 3) {
			if (ballsInit == false) {
				ballCount = die1 + die2;
				GenerateBalls();
				ballsInit = true;
			};
			for (int i = 0; i < ballCount; i++) {
				if (!balls[i].getDestroyed()) {
					balls[i].update(paddle->getX(), paddle->getY(), Game::bricks);
				}

			};

			if (GetActiveBalls(balls, ballCount) == -1) {
				gameState = 4;
				init = false;
				SDL_Quit();
			};

		}

		//ball->update(paddle->getX(), paddle->getY(), Game::bricks);
		//ball2->update(paddle->getX(), paddle->getY(), Game::bricks);
		//ball->update(paddle->getX(), paddle->getY(), brick->getX(), brick->getY());
		Render();
	}
};

void Game::GenerateBalls() {

	std::random_device myRandomDevice;
	std::mt19937 eng(myRandomDevice());
	std::uniform_int_distribution<> distr(WINDOW_WIDTH / 3, WINDOW_WIDTH - WINDOW_WIDTH / 3);

	std::random_device myRandomDevice2;
	std::mt19937 eng2(myRandomDevice2());
	std::uniform_int_distribution<> distr2(1, 4);

	int random_number_X;
	int random_number_Y;
	int randomMinus;
	
	for (int i = 0; i < ballCount; i++) {

		random_number_X = distr(eng);
		random_number_Y = distr(eng);
		randomMinus = distr2(eng2);

		if (randomMinus == 1) {
			balls[i] = Ball(random_number_X, random_number_Y, -BALL_SPEED, -BALL_SPEED, false);
		}
		else if (randomMinus == 2) {
			balls[i] = Ball(random_number_X, random_number_Y, BALL_SPEED, -BALL_SPEED, false);
		}
		else if (randomMinus == 3) {
			balls[i] = Ball(random_number_X, random_number_Y, -BALL_SPEED, BALL_SPEED, false);
		}
		else {
			balls[i] = Ball(random_number_X, random_number_Y, BALL_SPEED, BALL_SPEED, false);
		};
	};
}

void Game::Input() {
	SDL_Event event;
	const Uint8* state = SDL_GetKeyboardState(NULL);
	while (SDL_PollEvent(&event)) {

		if (gameState == 1) {
			if (state[SDL_SCANCODE_1]) {
				init = false;
				characterClass = 1;
				gameState = 2;
				SDL_Quit();
			}
			else if (state[SDL_SCANCODE_2]) {
				init = false;
				characterClass = 2;
				gameState = 2;
				SDL_Quit();
			}
			else if (state[SDL_SCANCODE_3]) {
				init = false;
				characterClass = 3;
				gameState = 2;
				SDL_Quit();
			}
			else if (state[SDL_SCANCODE_X]) {
				SDL_Quit();
				exit;
			}
		}
		else if (gameState == 2) {
			if (state[SDL_SCANCODE_R]) {
				GenerateDice();
				init = false;
				gameState = 3;
				SDL_Quit();
			}
		}
		else if (gameState == 3) {
			if (state[SDL_SCANCODE_X]) {
				gameState = 4;
				init = false;
				SDL_Quit();
			}
			else {
				if (state[SDL_SCANCODE_A]) {
					paddle->MoveLeft();
				}
				if (state[SDL_SCANCODE_D]) {
					paddle->MoveRight();
				}
			}
		}
		else if (gameState == 4) {
			if (state[SDL_SCANCODE_R]) {
				gameState = 1;
				init = false;
				SDL_Quit();
			}
			else if (state[SDL_SCANCODE_X]) {
				init = false;
				gameState = 5;
				SDL_Quit();
				exit;
			}
		}

	}
};

void Game::GenerateDice() {
	std::random_device myRandomDevice;
	std::mt19937 eng(myRandomDevice());
	std::uniform_int_distribution<> distr(1, 6);

	die1 = distr(eng);
	die2 = distr(eng);
}

void Game::Render() {
	
	
	if (gameState == 1) {

		if (init == false) {
			SDL_Surface* surface = IMG_Load("C:/Users/apuskunigis/Downloads/Main.png");

			SDL_DestroyWindow(window);
			init = true;
			SDL_Init(SDL_INIT_VIDEO);
			window = SDL_CreateWindow("Pong Main Menu", SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, WINDOW_WIDTH, WINDOW_HEIGHT, SDL_WINDOW_SHOWN);
			renderer = SDL_CreateRenderer(window, -1, SDL_RENDERER_ACCELERATED);

			if (!(IMG_Init(IMG_INIT_PNG) & IMG_INIT_PNG)) {
				std::cerr << "No png init";
				SDL_Quit();
				exit;
			}

			if (!surface) {
				std::cerr << "No image";
				SDL_DestroyRenderer(renderer);
				SDL_DestroyWindow(window);
				IMG_Quit();
				SDL_Quit();
				exit;
			}

			SDL_Texture* texture = SDL_CreateTextureFromSurface(renderer, surface);
			SDL_FreeSurface(surface);

			if (!texture) {
				std::cerr << "No texture";
				SDL_DestroyRenderer(renderer);
				SDL_DestroyWindow(window);
				IMG_Quit();
				SDL_Quit();
				exit;
			}

			SDL_RenderCopy(renderer, texture, NULL, NULL);

			SDL_RenderPresent(renderer);
			SDL_Delay(5);
		}


		

	}
	else if (gameState == 2) {

		if (init == false) {
			SDL_Surface* surface = IMG_Load("C:/Users/apuskunigis/Downloads/Dice.png");

			SDL_DestroyWindow(window);
			init = true;
			SDL_Init(SDL_INIT_VIDEO);
			window = SDL_CreateWindow("Pong Dice Roll", SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, WINDOW_WIDTH, WINDOW_HEIGHT, SDL_WINDOW_SHOWN);
			renderer = SDL_CreateRenderer(window, -1, SDL_RENDERER_ACCELERATED);

			if (!(IMG_Init(IMG_INIT_PNG) & IMG_INIT_PNG)) {
				std::cerr << "No png init";
				SDL_Quit();
				exit;
			}

			if (!surface) {
				std::cerr << "No image";
				SDL_DestroyRenderer(renderer);
				SDL_DestroyWindow(window);
				IMG_Quit();
				SDL_Quit();
				exit;
			}

			SDL_Texture* texture = SDL_CreateTextureFromSurface(renderer, surface);
			SDL_FreeSurface(surface);

			if (!texture) {
				std::cerr << "No texture";
				SDL_DestroyRenderer(renderer);
				SDL_DestroyWindow(window);
				IMG_Quit();
				SDL_Quit();
				exit;
			}

			SDL_RenderCopy(renderer, texture, NULL, NULL);

			SDL_RenderPresent(renderer);
		}


		

	}
	else if (gameState == 3) {

		if (init == false) {
			SDL_DestroyWindow(window);
			init = true;
			SDL_Init(SDL_INIT_VIDEO);
			window = SDL_CreateWindow("Pong", SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, WINDOW_WIDTH, WINDOW_HEIGHT, SDL_WINDOW_SHOWN);
			renderer = SDL_CreateRenderer(window, -1, SDL_RENDERER_ACCELERATED);
		}

		SDL_SetRenderDrawColor(renderer, 0, 0, 0, 255);
		SDL_RenderClear(renderer);

		SDL_SetRenderDrawColor(renderer, 255, 255, 255, 255);

		SDL_Rect paddleRect = { paddle->getX(), paddle->getY(), PADDLE_WIDTH,PADDLE_HEIGHT };
		SDL_RenderFillRect(renderer, &paddleRect);

		//SDL_Rect brickRect = { brick->getX(), brick->getY(), BRICK_WIDTH,BRICK_HEIGHT };
		//SDL_RenderFillRect(renderer, &brickRect);

		for (int i = 0; i < 10; i++) {
			if (bricks[i].getDestroyed() == false) {
				if (bricks[i].getHealth() == 2) {
					SDL_SetRenderDrawColor(renderer, 255, 0, 0, 255);
					SDL_Rect brickRect = { bricks[i].getX(), bricks[i].getY(), BRICK_WIDTH,BRICK_HEIGHT };
					SDL_RenderFillRect(renderer, &brickRect);
				}
				else {
					SDL_SetRenderDrawColor(renderer, 255, 255, 255, 255);
					SDL_Rect brickRect = { bricks[i].getX(), bricks[i].getY(), BRICK_WIDTH,BRICK_HEIGHT };
					SDL_RenderFillRect(renderer, &brickRect);
				};
			}
		};

		SDL_SetRenderDrawColor(renderer, 0, 255, 0, 255);

		for (int i = 0; i < ballCount; i++) {
			if (!balls[i].getDestroyed()) {
				SDL_Rect ballRect = { balls[i].getX(), balls[i].getY(), BALL_SIZE, BALL_SIZE };
				SDL_RenderFillRect(renderer, &ballRect);
			}
		}

		SDL_RenderPresent(renderer);
		SDL_Delay(5);

	}
	else if (gameState == 4) {

		if (init == false) {
			SDL_Surface* surface = IMG_Load("C:/Users/apuskunigis/Downloads/End.png");

			SDL_DestroyWindow(window);
			init = true;
			SDL_Init(SDL_INIT_VIDEO);
			window = SDL_CreateWindow("Pong Game Over", SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, WINDOW_WIDTH, WINDOW_HEIGHT, SDL_WINDOW_SHOWN);
			renderer = SDL_CreateRenderer(window, -1, SDL_RENDERER_ACCELERATED);

			if (!(IMG_Init(IMG_INIT_PNG) & IMG_INIT_PNG)) {
				std::cerr << "No png init";
				SDL_Quit();
				exit;
			}

			if (!surface) {
				std::cerr << "No image";
				SDL_DestroyRenderer(renderer);
				SDL_DestroyWindow(window);
				IMG_Quit();
				SDL_Quit();
				exit;
			}

			SDL_Texture* texture = SDL_CreateTextureFromSurface(renderer, surface);
			SDL_FreeSurface(surface);

			if (!texture) {
				std::cerr << "No texture";
				SDL_DestroyRenderer(renderer);
				SDL_DestroyWindow(window);
				IMG_Quit();
				SDL_Quit();
				exit;
			}

			SDL_RenderCopy(renderer, texture, NULL, NULL);

			SDL_RenderPresent(renderer);
			SDL_Delay(5);
		}

		

	}
	

	//else if (gameState == 4) {
	//SDL_Surface* surface = IMG_Load("C:/Users/apuskunigis/Downloads/End.png");

	//if (!(IMG_Init(IMG_INIT_PNG) & IMG_INIT_PNG)) {
	//	std::cerr << "No png init";
	//	SDL_Quit();
	//	exit;
	//}

	//if (!surface) {
	//	std::cerr << "No image";
	//	SDL_DestroyRenderer(renderer);
	//	SDL_DestroyWindow(window);
	//	IMG_Quit();
	//	SDL_Quit();
	//	exit;
	//}

	//SDL_Texture* texture = SDL_CreateTextureFromSurface(renderer, surface);
	//SDL_FreeSurface(surface);

	//if (!texture) {
	//	std::cerr << "No texture";
	//	SDL_DestroyRenderer(renderer);
	//	SDL_DestroyWindow(window);
	//	IMG_Quit();
	//	SDL_Quit();
	//	exit;
	//}

	//SDL_RenderCopy(renderer, texture, NULL, NULL);

	//SDL_RenderPresent(renderer);
	//SDL_Delay(5);

	//}
	//else if (gameState == 3) {

	//if (init == false) {
	//	SDL_DestroyWindow(window);
	//	init = true;
	//	SDL_Init(SDL_INIT_VIDEO);
	//	window = SDL_CreateWindow("Pong", SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, WINDOW_WIDTH, WINDOW_HEIGHT, SDL_WINDOW_SHOWN);
	//	renderer = SDL_CreateRenderer(window, -1, SDL_RENDERER_ACCELERATED);
	//}


	//SDL_SetRenderDrawColor(renderer, 0, 0, 0, 255);
	//SDL_RenderClear(renderer);

	//SDL_SetRenderDrawColor(renderer, 255, 255, 255, 255);

	//SDL_Rect paddleRect = { paddle->getX(), paddle->getY(), PADDLE_WIDTH,PADDLE_HEIGHT };
	//SDL_RenderFillRect(renderer, &paddleRect);

	////SDL_Rect brickRect = { brick->getX(), brick->getY(), BRICK_WIDTH,BRICK_HEIGHT };
	////SDL_RenderFillRect(renderer, &brickRect);

	//for (int i = 0; i < 10; i++) {
	//	if (bricks[i].getDestroyed() == false) {
	//		if (bricks[i].getHealth() == 2) {
	//			SDL_SetRenderDrawColor(renderer, 255, 0, 0, 255);
	//			SDL_Rect brickRect = { bricks[i].getX(), bricks[i].getY(), BRICK_WIDTH,BRICK_HEIGHT };
	//			SDL_RenderFillRect(renderer, &brickRect);
	//		}
	//		else {
	//			SDL_SetRenderDrawColor(renderer, 255, 255, 255, 255);
	//			SDL_Rect brickRect = { bricks[i].getX(), bricks[i].getY(), BRICK_WIDTH,BRICK_HEIGHT };
	//			SDL_RenderFillRect(renderer, &brickRect);
	//		};
	//	}
	//};



	//SDL_SetRenderDrawColor(renderer, 0, 255, 0, 255);

	//for (int i = 0; i < ballCount; i++) {
	//	if (!balls[i].getDestroyed()) {
	//		SDL_Rect ballRect = { balls[i].getX(), balls[i].getY(), BALL_SIZE, BALL_SIZE };
	//		SDL_RenderFillRect(renderer, &ballRect);
	//	}
	//}

	////SDL_Rect ballRect = { ball->getX(), ball->getY(), BALL_SIZE, BALL_SIZE };
	////SDL_RenderFillRect(renderer, &ballRect);

	////SDL_Rect ball2Rect = { ball2->getX(), ball2->getY(), BALL_SIZE, BALL_SIZE };
	////SDL_RenderFillRect(renderer, &ball2Rect);


	//SDL_RenderPresent(renderer);
	//SDL_Delay(5);

};


