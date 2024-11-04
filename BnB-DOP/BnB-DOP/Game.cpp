#include "Game.h"
#include "SDL.h"
#include <array>
#include <iostream>
#include <random>
#include <SDL_image.h>
#include <fstream>
#include <string>

Game::Game() {
	//Default game states
	gameState = 0;
	characterClass = 0;
	init = false;
	ballsInit = false;
	paddleWidth = PADDLE_WIDTH * 1;
	brickCount = 0;
	fileInit = false;
	paddleSpeed = PADDLE_SPEED * 1;
	level = 1;
	rollingDie = false;
};

Game::~Game() {

	SDL_DestroyRenderer(renderer);
	SDL_DestroyWindow(window);
	SDL_Quit();
};

//Return how many balls are active
int GetActiveBalls(Ball allBalls[], int ballCount) {
	int balls = 0;
	for (int i = 0; i < 12; i++) {
		if (allBalls[i].getDestroyed() == false) {
			balls++;
		}
	}
	return balls;
}

//Return how many bricks are active
int GetActiveBricks(Brick allBricks[], int brickCount) {
	int bricks = brickCount;
	for (int i = 0; i < 64; i++) {
		if (allBricks[i].getDestroyed()) {
			bricks--;
		}
	}
	return bricks;
}

//Game loop
void Game::Run() {

	while (true) {
		Input();

		
		if (gameState == 3) {

			//Load level files
			if (fileInit == false) {
				std::string line;

				if (level == 1) {
					std::ifstream file("assets/level1.txt");
					while (std::getline(file, line)) { 
					}
					file.close(); 
				}
				else if (level == 2) {
					std::ifstream file("assets/level2.txt");
					while (std::getline(file, line)) { 
					}
					file.close();
				}
				else if (level == 3) {
					std::ifstream file("assets/level3.txt");
					while (std::getline(file, line)) { 
					}
					file.close();
				}
				else if (level == 4) {
					std::ifstream file("assets/level4.txt");
					while (std::getline(file, line)) {
					}
					file.close();
				}
				else if (level == 5) {
					std::ifstream file("assets/level5.txt");
					while (std::getline(file, line)) {
					}
					file.close();
				}
				else if (level == 6) {
					std::ifstream file("assets/level6.txt");
					while (std::getline(file, line)) {
					}
					file.close();
				}
				else if (level == 7) {
					std::ifstream file("assets/level7.txt");
					while (std::getline(file, line)) {
					}
					file.close();
				}
				
				fileInit = true;
				int stringCounter = 0;

				//Spawn bricks and their health based on the file layouts
				if (line.size() <= 64) {

					for (int i = 1; i < 5; i++) {
						for (int j = 0; j < 16; j++) {
							if (line[stringCounter] == 'X') {

								bricks[stringCounter] = Brick((j * BRICK_WIDTH), i * 60, 1, false);
								brickCount++;
							}
							else if (line[stringCounter] == 'C') {

								bricks[stringCounter] = Brick((j * BRICK_WIDTH), i * 60, 2, false);
								brickCount++;
							}
							else if (line[stringCounter] == 'V') {

								bricks[stringCounter] = Brick((j * BRICK_WIDTH), i * 60, 3, false);
								brickCount++;
							}
							else if (line[stringCounter] == 'B') {

								bricks[stringCounter] = Brick((j * BRICK_WIDTH), i * 60, 4, false);
								brickCount++;
							}
							stringCounter++;
						}
					}
				}
			}

		}

		//Spawn balls based on classes
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

			//Check for active balls and bricks, if 0 balls then you lose and if 0 bricks then you win
			if (GetActiveBalls(balls, ballCount) == 0) {
				gameState = 4;
				init = false;
				SDL_Quit();
			};

			//check if level has been completed based on brick count, if level count is 8 then there are no more levels and you go to the king screen
			if (GetActiveBricks(bricks, 64) == 0) {
				level++;
				if (level >= 8) {
					gameState = 6;
				}
				else {
					gameState = 5;
				}
				init = false;
				SDL_Quit();
			};
		}

		//Adjust paddle width based on class
		if (gameState == 2) {
			if (characterClass == 2) {
				paddles[0] = Paddle(WINDOW_WIDTH / 2 - paddleWidth / 2, WINDOW_HEIGHT - 240);
				paddles[1] = Paddle(WINDOW_WIDTH / 2 - paddleWidth / 2, WINDOW_HEIGHT - 320);
			}
			else {
				paddles[0] = Paddle(WINDOW_WIDTH / 2 - paddleWidth / 2, WINDOW_HEIGHT - 240);
			}
		}

		Render();
	}
};

void Game::GenerateBalls() {

	//Random number generation for dice values which decides how many balls should be spawned
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

		//Random generation of spawned ball trajectories and positions, not all balls have a force of up and right at spawning
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
	//Check if there are inputs
	while (SDL_PollEvent(&event)) {

		if (gameState == 0) {
			//If main menu S, send the player to character select screen, otherwise if X then close the game
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
		//If they are in the character select screen, then based on inputs 1,2, or 3, they select a class and are sent to the dice screen or quit if X pressed
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
		//If in the game state they press X the game enters game over screen or if they press A or D the paddle moves left or right.
		else if (gameState == 3) {
			if (state[SDL_SCANCODE_X]) {
				gameState = 4;
				init = false;
				SDL_Quit();
				exit(0);
			}
			else {
			
				//Different paddle quantities based on player class
				if (characterClass == 2) {
					if (state[SDL_SCANCODE_A]) {
						paddles[0].MoveLeft(paddleSpeed);
						paddles[1].MoveLeft(paddleSpeed);
					}
					if (state[SDL_SCANCODE_D]) {
						paddles[0].MoveRight(paddleSpeed, paddleWidth);
						paddles[1].MoveRight(paddleSpeed, paddleWidth);
					}
				}
				else {
					if (state[SDL_SCANCODE_A]) {
						paddles[0].MoveLeft(paddleSpeed);
					}
					if (state[SDL_SCANCODE_D]) {
						paddles[0].MoveRight(paddleSpeed, paddleWidth);
					}
				}

			}
		}
		//If after losing the player presses R the game restarts, if X then the game closes
		else if (gameState == 4) {
			if (state[SDL_SCANCODE_R]) {
				//Reset to default game state
				gameState = 1;
				characterClass = 0;
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
		//If the player has won the level, pressing N results in the next level being loaded, X closes the game
		else if (gameState == 5) {
			if (state[SDL_SCANCODE_N]) {
				gameState = 2;
				init = false;
				ballsInit = false;
				if (characterClass == 3) {
					paddleWidth = PADDLE_WIDTH * 2;
				}
				else{
					paddleWidth = PADDLE_WIDTH * 1;
				}
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
		//King screen, x closes the game
		else if (gameState == 6) {
			if (state[SDL_SCANCODE_X]) {
				gameState = -1;
				SDL_Quit();
				exit;
			}
		}
	}
};

//Generate 2 die values
void Game::GenerateDice() {
	std::random_device myRandomDevice;
	std::mt19937 eng(myRandomDevice());
	std::uniform_int_distribution<> distr(1, 6);

	die1 = distr(eng);
	die2 = distr(eng);

	rollingDie = true;

}

void Game::Render() {
	
	//Draw the start screen
	if (gameState == 0) {

		//Check if it has been drawn already, if init false then it has not been drawn and should be drawn, otherwise there is no need to draw again
		if (init == false) {
			//Get the start screen from assets folder
			SDL_Surface* surface = IMG_Load("assets/StartScreen.png");

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
		}

	}
	//Draw the character select screen
	else if (gameState == 1) {

		if (init == false) {
			SDL_Surface* surface = IMG_Load("assets/ChooseCharacterScreen.png");

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
		}

	}
	//Draw the dice roll screen
	else if (gameState == 2) {

		if (init == false) {
			SDL_Surface* surface1 = nullptr;
			SDL_Texture* texture1 = nullptr;
			surface1 = IMG_Load("assets/RollDiceScreen.png");

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

			if (!surface1) {
				std::cerr << "No image";
				SDL_DestroyRenderer(renderer);
				SDL_DestroyWindow(window);
				IMG_Quit();
				SDL_Quit();
				exit;
			}

			texture1 = SDL_CreateTextureFromSurface(renderer, surface1);
			SDL_FreeSurface(surface1);

			if (!texture1) {
				std::cerr << "No texture";
				SDL_DestroyRenderer(renderer);
				SDL_DestroyWindow(window);
				IMG_Quit();
				SDL_Quit();
				exit;
			}

			SDL_RenderCopy(renderer, texture1, NULL, NULL);

			//Randomise the dice displays as to show that they are being rolled
			std::random_device myRandomDevice;
			std::mt19937 eng(myRandomDevice());
			std::uniform_int_distribution<> distr(1, 6);

			int temp1 = distr(eng);
			int temp2 = distr(eng);
			DrawDice(true, temp1);
			DrawDice(false, temp2);
			SDL_Delay(500);

			temp1 = distr(eng);
			temp2 = distr(eng);
			DrawDice(true, temp1);
			DrawDice(false, temp2);
			SDL_Delay(500);

			temp1 = distr(eng);
			temp2 = distr(eng);
			DrawDice(true, temp1);
			DrawDice(false, temp2);
			SDL_Delay(500);

			temp1 = distr(eng);
			temp2 = distr(eng);
			DrawDice(true, temp1);
			DrawDice(false, temp2);
			SDL_Delay(500);
			

			//Finally display the final dice values
			GenerateDice();
			DrawDice(true, die1);
			DrawDice(false, die2);

			//Allow the player time to understand that these are the final values and update the game state to playing
			SDL_Delay(2000);
			init = false;
			gameState = 3;
			SDL_Quit();
		}

	}
	//Draw the game screen
	else if (gameState == 3) {
		static SDL_Texture* texture = nullptr; // Static texture to retain its value
		SDL_Surface* surface = nullptr;

		if (!init) {
			SDL_DestroyWindow(window);
			init = true;

			SDL_Init(SDL_INIT_VIDEO);
			window = SDL_CreateWindow("Bricks & Breakers: Dice of Power", SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, WINDOW_WIDTH, 600, SDL_WINDOW_SHOWN);
			renderer = SDL_CreateRenderer(window, -1, SDL_RENDERER_ACCELERATED);

			surface = IMG_Load("assets/GameScreen.png");
			if (!surface) {
				printf("IMG_Load Error: %s\n", IMG_GetError());
				return;
			}

			texture = SDL_CreateTextureFromSurface(renderer, surface);
			SDL_FreeSurface(surface);  

			if (!texture) {
				printf("SDL_CreateTextureFromSurface Error: %s\n", SDL_GetError());
				return;
			}
		}

		SDL_SetRenderDrawColor(renderer, 0, 0, 0, 255);
		SDL_RenderClear(renderer);

		SDL_Rect destRect1 = { 0, 0, 800, 800 };
		SDL_RenderCopy(renderer, texture, nullptr, &destRect1);

		SDL_SetRenderDrawColor(renderer, 255, 255, 255, 255);

		//Draw the first paddle
		SDL_Rect paddleRect = { paddles[0].getX(), paddles[0].getY(), paddleWidth, PADDLE_HEIGHT };
		SDL_RenderFillRect(renderer, &paddleRect);

		//Draw the second paddle based on the class
		if (characterClass == 2) {
			SDL_Rect paddleRect2 = { paddles[1].getX(), paddles[1].getY(), paddleWidth, PADDLE_HEIGHT };
			SDL_RenderFillRect(renderer, &paddleRect2);
		}
		
		//Draw each brick in a different colour based on how much health the brick has e.g 2 health = red and 1 health = white then green and blue
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

		//Draw the balls
		for (int i = 0; i < ballCount; i++) {
			if (!balls[i].getDestroyed()) {
				SDL_Rect ballRect = { balls[i].getX(), balls[i].getY(), BALL_SIZE, BALL_SIZE };
				SDL_RenderFillRect(renderer, &ballRect);
			}
		}

		SDL_RenderPresent(renderer);
		SDL_Delay(5);

	}
	//Draw the game over screen
	else if (gameState == 4) {

		if (init == false) {
			SDL_Surface* surface = IMG_Load("assets/GameOverScreen.png");

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
		}

	}
	//Draw the level win screen
	else if (gameState == 5) {

		if (init == false) {
			SDL_Surface* surface = IMG_Load("assets/RoundWinner.png");

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
		}
	}

	else if (gameState == 6) {

		if (init == false) {
			SDL_Surface* surface = IMG_Load("assets/KingScreen.png");

			SDL_DestroyWindow(window);
			init = true;
			SDL_Init(SDL_INIT_VIDEO);
			window = SDL_CreateWindow("Bricks & Breakers: Dice of Power - KING", SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, WINDOW_WIDTH, WINDOW_HEIGHT, SDL_WINDOW_SHOWN);
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

}

//Draw the appropriate dice based on passed in parameters (for the dice roll screen)
void Game::DrawDice(bool isLeft, int diceNumber) {

	SDL_Rect destRect1 = { 150, 250, 218, 252 }; //left rect
	SDL_Rect destRect2 = { 200 + 218, 250, 218, 252 }; //right rect

	if (isLeft) {
		if (diceNumber == 1) {
			SDL_Surface* surface1 = IMG_Load("assets/Dice1.png");

			SDL_Texture* texture1 = SDL_CreateTextureFromSurface(renderer, surface1);
			SDL_FreeSurface(surface1);  
			SDL_RenderCopy(renderer, texture1, nullptr, &destRect1);
		}
		else if (diceNumber == 2) {
			SDL_Surface* surface2 = IMG_Load("assets/Dice2.png");

			SDL_Texture* texture2 = SDL_CreateTextureFromSurface(renderer, surface2);
			SDL_FreeSurface(surface2);
			SDL_RenderCopy(renderer, texture2, nullptr, &destRect1);
		}
		else if (diceNumber == 3) {

			SDL_Surface* surface3 = IMG_Load("assets/Dice3.png");

			SDL_Texture* texture3 = SDL_CreateTextureFromSurface(renderer, surface3);
			SDL_FreeSurface(surface3);  
			SDL_RenderCopy(renderer, texture3, nullptr, &destRect1);
		}
		else if (diceNumber == 4) {

			SDL_Surface* surface4 = IMG_Load("assets/Dice4.png");

			SDL_Texture* texture4 = SDL_CreateTextureFromSurface(renderer, surface4);
			SDL_FreeSurface(surface4);  
			SDL_RenderCopy(renderer, texture4, nullptr, &destRect1);
		}
		else if (diceNumber == 5) {

			SDL_Surface* surface5 = IMG_Load("assets/Dice5.png");

			SDL_Texture* texture5 = SDL_CreateTextureFromSurface(renderer, surface5);
			SDL_FreeSurface(surface5);  
			SDL_RenderCopy(renderer, texture5, nullptr, &destRect1);
		}
		else if (diceNumber == 6) {
			SDL_Surface* surface6 = IMG_Load("assets/Dice6.png");

			SDL_Texture* texture6 = SDL_CreateTextureFromSurface(renderer, surface6);
			SDL_FreeSurface(surface6);  
			SDL_RenderCopy(renderer, texture6, nullptr, &destRect1);
		}
	}
	else {
		if (diceNumber == 1) {
			SDL_Surface* surface1 = IMG_Load("assets/Dice1.png");

			SDL_Texture* texture1 = SDL_CreateTextureFromSurface(renderer, surface1);
			SDL_FreeSurface(surface1);  
			SDL_RenderCopy(renderer, texture1, nullptr, &destRect2);
		}
		else if (diceNumber == 2) {
			SDL_Surface* surface2 = IMG_Load("assets/Dice2.png");

			SDL_Texture* texture2 = SDL_CreateTextureFromSurface(renderer, surface2);
			SDL_FreeSurface(surface2);  
			SDL_RenderCopy(renderer, texture2, nullptr, &destRect2);
		}
		else if (diceNumber == 3) {

			SDL_Surface* surface3 = IMG_Load("assets/Dice3.png");

			SDL_Texture* texture3 = SDL_CreateTextureFromSurface(renderer, surface3);
			SDL_FreeSurface(surface3);  
			SDL_RenderCopy(renderer, texture3, nullptr, &destRect2);
		}
		else if (diceNumber == 4) {

			SDL_Surface* surface4 = IMG_Load("assets/Dice4.png");

			SDL_Texture* texture4 = SDL_CreateTextureFromSurface(renderer, surface4);
			SDL_FreeSurface(surface4);  
			SDL_RenderCopy(renderer, texture4, nullptr, &destRect2);
		}
		else if (diceNumber == 5) {

			SDL_Surface* surface5 = IMG_Load("assets/Dice5.png");

			SDL_Texture* texture5 = SDL_CreateTextureFromSurface(renderer, surface5);
			SDL_FreeSurface(surface5);  
			SDL_RenderCopy(renderer, texture5, nullptr, &destRect2);
		}
		else if (diceNumber == 6) {
			SDL_Surface* surface6 = IMG_Load("assets/Dice6.png");

			SDL_Texture* texture6 = SDL_CreateTextureFromSurface(renderer, surface6);
			SDL_FreeSurface(surface6);  
			SDL_RenderCopy(renderer, texture6, nullptr, &destRect2);
		}
	}

	SDL_RenderPresent(renderer);

}




