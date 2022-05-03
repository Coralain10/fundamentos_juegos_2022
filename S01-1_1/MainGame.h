#pragma once
#include <SDL/SDL.h>
#include "Sprite.h"
#include "GLS_Program.h"

enum class GameState {
	PLAY, EXIT
};
class MainGame
{
private:
	float time;
	GLS_Program program;
	int width;
	int height;
	GameState gameState;
	SDL_Window* window;
	void init();
	void update();
	void draw();
	void processInput();
	void initShaders();
	Sprite sprite;
	Sprite spriteTR;
public:
	MainGame();
	~MainGame();
	void run();
};

