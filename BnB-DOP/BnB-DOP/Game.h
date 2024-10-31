#pragma once
#include "Paddle.h"
#include "Ball.h"
#include "Brick.h"
#include "SDL.h"

class Game
{
public:
	Game();
	~Game();
	void Run();
	bool init;
	bool ballsInit;
	int characterClass;
	bool characterInit;
	int die1;
	int die2;

private:
	void GenerateDice();
	void GenerateBalls();
	void Input();
	void Render();
	SDL_Window* window;
	SDL_Renderer* renderer;
	Paddle* paddle;
	Ball* ball;
	Ball* ball2;
	Brick* brick;
	Brick bricks[11];
	Ball balls[12];
	Paddle paddles[2];
	bool fileInit;
	int paddleWidth;
	int diceValue;
	int paddleSpeed;
	int ballCount;
	int brickCount;
	// Game states: 1 = Main | 2 = Class select | 3 = Dice roll | 4 = Level 1 | 5 = Level complete | 6 = Level 2 |
	int gameState;
	
};

