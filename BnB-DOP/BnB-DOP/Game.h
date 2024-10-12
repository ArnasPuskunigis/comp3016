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

private:
	void Input();
	void Render();
	SDL_Window* window;
	SDL_Renderer* renderer;
	Paddle* paddle;
	Ball* ball;
	Brick* brick;
};

