#include "Game.h"
#include "SDL.h"
#include <array>
#include <iostream>
#include <random>
#include <SDL_image.h>

Game::Game() {
	gameState = 2;

	SDL_Init(SDL_INIT_VIDEO);
	window = SDL_CreateWindow("Pong", SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, WINDOW_WIDTH, WINDOW_HEIGHT, SDL_WINDOW_SHOWN);
	renderer = SDL_CreateRenderer(window, -1, SDL_RENDERER_ACCELERATED);
	
	paddle = new Paddle(WINDOW_WIDTH / 2 - PADDLE_WIDTH / 2, WINDOW_HEIGHT - 20);
	//ball = new Ball(WINDOW_WIDTH / 2 - BALL_SIZE / 2, WINDOW_HEIGHT / 2 - BALL_SIZE / 2, BALL_SPEED, BALL_SPEED, false);
	//ball2 = new Ball(50, 500, BALL_SPEED, BALL_SPEED, false);
	diceValue = rand() % 12 + 1;
	ballCount = diceValue;

	std::random_device myRandomDevice;
	std::mt19937 eng(myRandomDevice());
	std::uniform_int_distribution<> distr(WINDOW_WIDTH / 3, WINDOW_WIDTH - WINDOW_WIDTH / 3);

	std::random_device myRandomDevice2;
	std::mt19937 eng2(myRandomDevice2());
	std::uniform_int_distribution<> distr2(1, 4);

	int random_number_X;
	int random_number_Y;
	int randomMinus;

	for (int i = 1; i < 11; i++) {
		bricks[i - 1] = Brick((i * BRICK_WIDTH) + 20, i * 20, 2, false);
	}

	//brick = new Brick(WINDOW_WIDTH / 2 - BRICK_WIDTH / 2, 100, 1, false);
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

		if (gameState == 1) {
			for (int i = 0; i < ballCount; i++) {
				if (!balls[i].getDestroyed()) {
					balls[i].update(paddle->getX(), paddle->getY(), Game::bricks);
				}
			}

			if (GetActiveBalls(balls, ballCount) == 0) {
				SDL_Quit();
				exit(0);
			};
		}

		//ball->update(paddle->getX(), paddle->getY(), Game::bricks);
		//ball2->update(paddle->getX(), paddle->getY(), Game::bricks);
		//ball->update(paddle->getX(), paddle->getY(), brick->getX(), brick->getY());
		Render();
	}
};

void Game::Input() {
	SDL_Event event;
	const Uint8* state = SDL_GetKeyboardState(NULL);
	while (SDL_PollEvent(&event)) {

		if (gameState == 1) {
			if (state[SDL_SCANCODE_X]) {
				SDL_Quit();
				exit(0);
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



	}
};
void Game::Render() {
	
	if (gameState == 1) {

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

		//SDL_Rect ballRect = { ball->getX(), ball->getY(), BALL_SIZE, BALL_SIZE };
		//SDL_RenderFillRect(renderer, &ballRect);

		//SDL_Rect ball2Rect = { ball2->getX(), ball2->getY(), BALL_SIZE, BALL_SIZE };
		//SDL_RenderFillRect(renderer, &ball2Rect);


		SDL_RenderPresent(renderer);
		SDL_Delay(5);

	}
	else if (gameState == 2) {
		// Load an image
		SDL_Surface* surface = IMG_Load("C:/Users/apuskunigis/Downloads/sprite.png"); // Use your actual image path here

			if (SDL_Init(SDL_INIT_VIDEO) < 0) {
				std::cerr << "SDL could not initialize! SDL_Error: " << SDL_GetError() << std::endl;
				exit;
			}

			// Initialize SDL_image
			if (!(IMG_Init(IMG_INIT_PNG) & IMG_INIT_PNG)) {
				std::cerr << "SDL_image could not initialize! IMG_Error: " << IMG_GetError() << std::endl;
				SDL_Quit();
				exit;
			}

			// Create a window
			SDL_Window* window = SDL_CreateWindow("Load Image Example", SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, 800, 600, 0);
			if (!window) {
				std::cerr << "Window could not be created! SDL_Error: " << SDL_GetError() << std::endl;
				IMG_Quit();
				SDL_Quit();
				exit;
			}

			// Create a renderer
			SDL_Renderer* renderer = SDL_CreateRenderer(window, -1, SDL_RENDERER_ACCELERATED);
			if (!renderer) {
				std::cerr << "Renderer could not be created! SDL_Error: " << SDL_GetError() << std::endl;
				SDL_DestroyWindow(window);
				IMG_Quit();
				SDL_Quit();
				exit;
			}

			// Load an image from the specified path
			if (!surface) {
				std::cerr << "Unable to load image! IMG_Error: " << IMG_GetError() << std::endl;
				SDL_DestroyRenderer(renderer);
				SDL_DestroyWindow(window);
				IMG_Quit();
				SDL_Quit();
				exit;
			}

			// Create a texture from the surface
			SDL_Texture* texture = SDL_CreateTextureFromSurface(renderer, surface);
			SDL_FreeSurface(surface); // Free the surface as we no longer need it

			if (!texture) {
				std::cerr << "Unable to create texture! SDL_Error: " << SDL_GetError() << std::endl;
				SDL_DestroyRenderer(renderer);
				SDL_DestroyWindow(window);
				IMG_Quit();
				SDL_Quit();
				exit;
			}

			// Main loop
			bool running = true;
			SDL_Event event;
			while (running) {
				while (SDL_PollEvent(&event)) {
					if (event.type == SDL_QUIT) {
						running = false;
					}
				}

				// Clear the screen
				SDL_RenderClear(renderer);

				// Render the texture
				SDL_RenderCopy(renderer, texture, NULL, NULL);

				// Present the renderer
				SDL_RenderPresent(renderer);
			}

			// Clean up
			SDL_DestroyTexture(texture);
			SDL_DestroyRenderer(renderer);
			SDL_DestroyWindow(window);
			IMG_Quit();
			SDL_Quit();

			exit;
		}

		//SDL_Texture* spriteTexture = NULL;
		//if (spriteTexture == NULL) {
		//	spriteTexture = IMG_LoadTexture(renderer, "C:/Users/apuskunigis/Downloads/sprite.png");
		//}
		//if (!spriteTexture) {
		//	std::cerr << "Failed to load texture! IMG_Error: " << IMG_GetError() << std::endl;
		//}
		//else {
		//	SDL_RenderCopy(renderer, spriteTexture, nullptr, nullptr); // Render at the default position

		//}

	
};


