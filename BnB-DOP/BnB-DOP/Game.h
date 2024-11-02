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
	void DrawDice(bool isLeft, int diceNumber);
	SDL_Window* window;
	SDL_Renderer* renderer;
	Brick bricks[64];
	Ball balls[12];
	Paddle paddles[2];
	int level;
	bool rollingDie;
	bool fileInit;
	int paddleWidth;
	int diceValue;
	int paddleSpeed;
	int ballCount;
	int brickCount;
	int gameState;
	
};

