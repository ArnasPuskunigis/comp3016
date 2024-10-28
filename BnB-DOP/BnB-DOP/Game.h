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
	Brick bricks[10];
	Ball balls[11];
	Paddle* paddles[1];
	int diceValue;
	int ballCount;
	// Game states: 1 = Main | 2 = Class select | 3 = Dice roll | 4 = Level 1 | 5 = Level complete | 6 = Level 2 |
	int gameState;
	
};

