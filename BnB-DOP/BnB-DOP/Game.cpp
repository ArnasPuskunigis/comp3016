#include "Game.h"
#include "SDL.h"
#include <array>
#include <iostream>
#include <random>
#include <SDL_image.h>
#include <fstream>
#include <string>

Game::Game() {
	gameState = 0;
	characterClass = 0; // 1 = speed, 2 = 
	init = false;
	ballsInit = false;
	paddleWidth = PADDLE_WIDTH * 1;
	brickCount = 0;
	fileInit = false;
	paddleSpeed = PADDLE_SPEED * 1;
	level = 1;
	
};

Game::~Game() {

	SDL_DestroyRenderer(renderer);
	SDL_DestroyWindow(window);
	SDL_Quit();
};

int GetActiveBalls(Ball allBalls[], int ballCount) {
	int balls = 0;
	for (int i = 0; i < 12; i++) {
		if (allBalls[i].getDestroyed() == false) {
			balls++;
		}
	}
	return balls;
}

int GetActiveBricks(Brick allBricks[], int brickCount) {
	int bricks = brickCount;
	for (int i = 0; i < 64; i++) {
		if (allBricks[i].getDestroyed()) {
			bricks--;
		}
	}
	return bricks;
}

void Game::Run() {

	while (true) {
		Input();

		if (gameState == 3) {
			if (fileInit == false) {
				std::string line;

				if (level == 1) {
					std::ifstream file("C:/Users/Arnas/GIT/comp3016/level1.txt");
					while (std::getline(file, line)) {  // Read the file line by line
					}
					file.close();  // Close the file
				}
				else if (level == 2) {
					std::ifstream file("C:/Users/Arnas/GIT/comp3016/level2.txt");
					while (std::getline(file, line)) {  // Read the file line by line
					}
					file.close();  // Close the file
				}
				else if (level == 3) {
					std::ifstream file("C:/Users/Arnas/GIT/comp3016/level3.txt");
					while (std::getline(file, line)) {  // Read the file line by line
					}
					file.close();  // Close the file
				}
				else if (level == 4) {
					std::ifstream file("C:/Users/Arnas/GIT/comp3016/level4.txt");
					while (std::getline(file, line)) {  // Read the file line by line
					}
					file.close();  // Close the file
				}
				
				
				fileInit = true;
				int stringCounter = 0;

				if (line.size() <= 64) {

					for (int i = 1; i < 5; i++) {
						for (int j = 0; j < 16; j++) {
							if (line[stringCounter] == 'X') {

								bricks[stringCounter] = Brick((j * BRICK_WIDTH), i * 40, 1, false);
								brickCount++;
							}
							else if (line[stringCounter] == 'C') {

								bricks[stringCounter] = Brick((j * BRICK_WIDTH), i * 40, 2, false);
								brickCount++;
							}
							else if (line[stringCounter] == 'V') {

								bricks[stringCounter] = Brick((j * BRICK_WIDTH), i * 40, 3, false);
								brickCount++;
							}
							else if (line[stringCounter] == 'B') {

								bricks[stringCounter] = Brick((j * BRICK_WIDTH), i * 40, 4, false);
								brickCount++;
							}
							stringCounter++;
						}
					}
				}
			}

		}

		if (gameState == 3) {
			if (ballsInit == false) {
				ballCount = die1 + die2;
				GenerateBalls();
				ballsInit = true;
			};
			for (int i = 0; i < ballCount; i++) {
				if (!balls[i].getDestroyed()) {
					if (characterClass == 1) {
						balls[i].update(paddles[0].getX(), paddles[0].getY(), Game::bricks, paddleWidth, true, true);
					}
					else if (characterClass == 2) {
						balls[i].update(paddles[0].getX(), paddles[0].getY(), Game::bricks, paddleWidth, true, false);
						balls[i].update(paddles[1].getX(), paddles[1].getY(), Game::bricks, paddleWidth, false, false);
					}
					else if (characterClass == 3) {
						balls[i].update(paddles[0].getX(), paddles[0].getY(), Game::bricks, paddleWidth, true, false);
					}
				}

			};

			if (GetActiveBalls(balls, ballCount) == 0) {
				gameState = 4;
				init = false;
				SDL_Quit();
			};

			if (GetActiveBricks(bricks, 64) == 0) {
				gameState = 5;
				level++;
				init = false;
				SDL_Quit();
			};
		}

		if (gameState == 2) {
			if (characterClass == 2) {
				paddles[0] = Paddle(WINDOW_WIDTH / 2 - paddleWidth / 2, WINDOW_HEIGHT - 240);
				paddles[1] = Paddle(WINDOW_WIDTH / 2 - paddleWidth / 2, WINDOW_HEIGHT - 320);
			}
			else {
				paddles[0] = Paddle(WINDOW_WIDTH / 2 - paddleWidth / 2, WINDOW_HEIGHT - 240);
			}
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

		if (gameState == 0) {
			if (state[SDL_SCANCODE_S]) {
				init = false;
				gameState = 1;
				SDL_Quit();
			}
			else if (state[SDL_SCANCODE_X]) {
				SDL_Quit();
				exit;
			}
		}
		else if (gameState == 1) {
			if (state[SDL_SCANCODE_1]) {
				init = false;
				characterClass = 1;
				paddleSpeed = PADDLE_SPEED * 2;
				paddleWidth = PADDLE_WIDTH * 1;
				gameState = 2;
				SDL_Quit();
			}
			else if (state[SDL_SCANCODE_2]) {
				init = false;
				characterClass = 2;
				paddleSpeed = PADDLE_SPEED * 1;
				paddleWidth = PADDLE_WIDTH * 1;
				gameState = 2;
				SDL_Quit();
			}
			else if (state[SDL_SCANCODE_3]) {
				init = false;
				characterClass = 3;
				paddleSpeed = PADDLE_SPEED * 1;
				paddleWidth = PADDLE_WIDTH * 2;
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
			
				if (characterClass == 2) {
					if (state[SDL_SCANCODE_A]) {
						paddles[0].MoveLeft(paddleSpeed);
						paddles[1].MoveLeft(paddleSpeed);
					}
					if (state[SDL_SCANCODE_D]) {
						paddles[0].MoveRight(paddleSpeed);
						paddles[1].MoveRight(paddleSpeed);
					}
				}
				else {
					if (state[SDL_SCANCODE_A]) {
						paddles[0].MoveLeft(paddleSpeed);
					}
					if (state[SDL_SCANCODE_D]) {
						paddles[0].MoveRight(paddleSpeed);
					}
				}

			}
		}
		else if (gameState == 4) {
			if (state[SDL_SCANCODE_R]) {
				gameState = 1;
				characterClass = 0; // 1 = speed, 2 = 
				init = false;
				ballsInit = false;
				paddleWidth = PADDLE_WIDTH * 1;
				brickCount = 0;
				ballCount = 0;
				fileInit = false;
				paddleSpeed = PADDLE_SPEED * 1;
				SDL_Quit();
			}
			else if (state[SDL_SCANCODE_X]) {
				init = false;
				gameState = -1;
				SDL_Quit();
				exit;
			}
		}
		else if (gameState == 5) {
			if (state[SDL_SCANCODE_N]) {
				gameState = 2;
				init = false;
				ballsInit = false;
				paddleWidth = PADDLE_WIDTH * 1;
				brickCount = 0;
				ballCount = 0;
				fileInit = false;
				paddleSpeed = PADDLE_SPEED * 1;
				SDL_Quit();
			}
			else if (state[SDL_SCANCODE_X]) {
				init = false;
				gameState = -1;
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
	
	if (gameState == 0) {

		if (init == false) {
			SDL_Surface* surface = IMG_Load("C:/Users/Arnas/GIT/comp3016/StartScreen.png");

			SDL_DestroyWindow(window);
			init = true;
			SDL_Init(SDL_INIT_VIDEO);
			window = SDL_CreateWindow("Bricks & Breakers: Dice of Power - Main Menu", SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, WINDOW_WIDTH, WINDOW_HEIGHT, SDL_WINDOW_SHOWN);
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
	else if (gameState == 1) {

		if (init == false) {
			SDL_Surface* surface = IMG_Load("C:/Users/Arnas/GIT/comp3016/ChooseCharacterScreen.png");

			SDL_DestroyWindow(window);
			init = true;
			SDL_Init(SDL_INIT_VIDEO);
			window = SDL_CreateWindow("Bricks & Breakers: Dice of Power - Character Select", SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, WINDOW_WIDTH, WINDOW_HEIGHT, SDL_WINDOW_SHOWN);
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
			SDL_Surface* surface = IMG_Load("C:/Users/Arnas/GIT/comp3016/RollDiceScreen.png");

			SDL_DestroyWindow(window);
			init = true;
			SDL_Init(SDL_INIT_VIDEO);
			window = SDL_CreateWindow("Bricks & Breakers: Dice of Power - Dice Roll", SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, WINDOW_WIDTH, WINDOW_HEIGHT, SDL_WINDOW_SHOWN);
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
		static SDL_Texture* texture = nullptr; // Static texture to retain its value
		SDL_Surface* surface = nullptr;

		if (!init) {
			SDL_DestroyWindow(window);
			init = true;

			// Initialize SDL
			SDL_Init(SDL_INIT_VIDEO);
			window = SDL_CreateWindow("Bricks & Breakers: Dice of Power", SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, WINDOW_WIDTH, WINDOW_HEIGHT, SDL_WINDOW_SHOWN);
			renderer = SDL_CreateRenderer(window, -1, SDL_RENDERER_ACCELERATED);

			// Load the image
			surface = IMG_Load("C:/Users/Arnas/GIT/comp3016/GameScreen.png");
			if (!surface) {
				// Handle error (e.g., log it)
				printf("IMG_Load Error: %s\n", IMG_GetError());
				return;
			}

			// Create texture from the surface
			texture = SDL_CreateTextureFromSurface(renderer, surface);
			SDL_FreeSurface(surface);  // Free the surface after creating the texture

			if (!texture) {
				// Handle error (e.g., log it)
				printf("SDL_CreateTextureFromSurface Error: %s\n", SDL_GetError());
				return;
			}
		}

		SDL_SetRenderDrawColor(renderer, 0, 0, 0, 255);
		SDL_RenderClear(renderer);

		// Render the texture
		SDL_Rect destRect1 = { 0, 0, 800, 800 }; // Set position and size as needed
		SDL_RenderCopy(renderer, texture, nullptr, &destRect1);

		SDL_SetRenderDrawColor(renderer, 255, 255, 255, 255);

		SDL_Rect paddleRect = { paddles[0].getX(), paddles[0].getY(), paddleWidth, PADDLE_HEIGHT };
		SDL_RenderFillRect(renderer, &paddleRect);

		if (characterClass == 2) {
			SDL_Rect paddleRect2 = { paddles[1].getX(), paddles[1].getY(), paddleWidth, PADDLE_HEIGHT };
			SDL_RenderFillRect(renderer, &paddleRect2);
		}
		
		//SDL_Rect brickRect = { brick->getX(), brick->getY(), BRICK_WIDTH,BRICK_HEIGHT };
		//SDL_RenderFillRect(renderer, &brickRect);

		for (int i = 0; i < 64; i++) {
			if (bricks[i].getDestroyed() == false) {
				if (bricks[i].getHealth() == 2) {
					SDL_SetRenderDrawColor(renderer, 255, 0, 0, 255);
					SDL_Rect brickRect = { bricks[i].getX(), bricks[i].getY(), BRICK_WIDTH,BRICK_HEIGHT };
					SDL_RenderFillRect(renderer, &brickRect);
				}
				else if (bricks[i].getHealth() == 1) {
					SDL_SetRenderDrawColor(renderer, 255, 255, 255, 255);
					SDL_Rect brickRect = { bricks[i].getX(), bricks[i].getY(), BRICK_WIDTH,BRICK_HEIGHT };
					SDL_RenderFillRect(renderer, &brickRect);
				}
				else if (bricks[i].getHealth() == 3) {
					SDL_SetRenderDrawColor(renderer, 0, 255, 0, 255);
					SDL_Rect brickRect = { bricks[i].getX(), bricks[i].getY(), BRICK_WIDTH,BRICK_HEIGHT };
					SDL_RenderFillRect(renderer, &brickRect);
				}
				else if (bricks[i].getHealth() == 4) {
					SDL_SetRenderDrawColor(renderer, 0, 0, 255, 255);
					SDL_Rect brickRect = { bricks[i].getX(), bricks[i].getY(), BRICK_WIDTH,BRICK_HEIGHT };
					SDL_RenderFillRect(renderer, &brickRect);
				}
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
			SDL_Surface* surface = IMG_Load("C:/Users/Arnas/GIT/comp3016/GameOverScreen.png");

			SDL_DestroyWindow(window);
			init = true;
			SDL_Init(SDL_INIT_VIDEO);
			window = SDL_CreateWindow("Bricks & Breakers: Dice of Power - Game Over", SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, WINDOW_WIDTH, WINDOW_HEIGHT, SDL_WINDOW_SHOWN);
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
	else if (gameState == 5) {

	if (init == false) {
		SDL_Surface* surface = IMG_Load("C:/Users/Arnas/GIT/comp3016/RoundWinner.png");

		SDL_DestroyWindow(window);
		init = true;
		SDL_Init(SDL_INIT_VIDEO);
		window = SDL_CreateWindow("Bricks & Breakers: Dice of Power - Game Over", SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, WINDOW_WIDTH, WINDOW_HEIGHT, SDL_WINDOW_SHOWN);
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

};


