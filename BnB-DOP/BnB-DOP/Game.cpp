#include "Game.h"
#include "SDL.h"


Game::Game() {
	SDL_Init(SDL_INIT_VIDEO);
	window = SDL_CreateWindow("Pong", SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, WINDOW_WIDTH, WINDOW_HEIGHT, SDL_WINDOW_SHOWN);
	renderer = SDL_CreateRenderer(window, -1, SDL_RENDERER_ACCELERATED);
	paddle = new Paddle(WINDOW_WIDTH / 2 - PADDLE_WIDTH / 2, WINDOW_HEIGHT - 20);
	ball = new Ball(WINDOW_WIDTH / 2 - BALL_SIZE / 2, WINDOW_HEIGHT / 2 - BALL_SIZE / 2, BALL_SPEED, BALL_SPEED);
	brick = new Brick(WINDOW_WIDTH / 2 - BRICK_WIDTH / 2, 200, 1, false);
};

Game::~Game() {

	SDL_DestroyRenderer(renderer);
	SDL_DestroyWindow(window);
	SDL_Quit();
};

void Game::Run() {

	while (true) {
		Input();
		ball->update(paddle->getX(), paddle->getY(), brick->getX(), brick->getY());
		Render();

	}

};

void Game::Input() {
	SDL_Event event;
	const Uint8* state = SDL_GetKeyboardState(NULL);
	while (SDL_PollEvent(&event)) {
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
};
void Game::Render() {
	SDL_SetRenderDrawColor(renderer, 0, 0, 0, 255);
	SDL_RenderClear(renderer);

	SDL_SetRenderDrawColor(renderer, 255, 255, 255, 255);

	SDL_Rect paddleRect = { paddle->getX(), paddle->getY(), PADDLE_WIDTH,PADDLE_HEIGHT };
	SDL_RenderFillRect(renderer, &paddleRect);

	SDL_Rect brickRect = { brick->getX(), brick->getY(), BRICK_WIDTH,BRICK_HEIGHT };
	SDL_RenderFillRect(renderer, &brickRect);

	SDL_SetRenderDrawColor(renderer, 0, 255, 0, 255);
	SDL_Rect ballRect = { ball->getX(), ball->getY(), BALL_SIZE, BALL_SIZE };
	SDL_RenderFillRect(renderer, &ballRect);



	SDL_RenderPresent(renderer);
	SDL_Delay(25);
};

