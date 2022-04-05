#pragma once
#include <SDL/SDL.h>
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
public:
	MainGame();
	~MainGame();
	void run();
};

