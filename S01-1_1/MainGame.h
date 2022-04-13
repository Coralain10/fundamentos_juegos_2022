#pragma once
#include <SDL/SDL.h>
#include "Sprite.h"

enum class GameState {
	PLAY, EXIT
};
class MainGame
{
private:
	int width;
	int height;
	GameState gameState;
	SDL_Window* window;
	void init();
	void update();
	void draw();
	void processInput();
	Sprite sprite;
public:
	MainGame();
	~MainGame();
	void run();
};

