#include "MainGame.h"
#include <GL/glew.h>

MainGame::MainGame() :window(nullptr), width(800), height(600), gameState(GameState::PLAY)
{
}

MainGame::~MainGame()
{
}

void MainGame::run()
{
	init();
	update();
}


void MainGame::init()
{
	SDL_Init(SDL_INIT_EVERYTHING);
	window = SDL_CreateWindow("Hey!",
		SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED,
		width, height, SDL_WINDOW_OPENGL);
	if (window == nullptr) {
		//paso algo mostrar mensaje
	}
	SDL_GLContext glContext = SDL_GL_CreateContext(window);
	GLenum error = glewInit();
	if (error != GLEW_OK) {
		//paso algo mostrar mensaje 2
	}
	SDL_GL_SetAttribute(SDL_GL_DOUBLEBUFFER, 1);
	glClearColor(0.0f,0.5f,0.75f,0.0f);
}

void MainGame::update()
{
	while (gameState == GameState::PLAY)
	{
		//dibujar pantalla y otros
		processInput();
		draw();
	}
}


void MainGame::draw()
{
	glClearDepth(1.0);
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	//Si hubiera un elemento en escena, lo dibuja
	SDL_GL_SwapWindow(window);
}

void MainGame::processInput()
{
	SDL_Event event;
	while (SDL_PollEvent(&event)) {
		//captura los eventos en la pantalla
		switch (event.type)
		{
		case SDL_QUIT:
			gameState = GameState::EXIT;
			break;
		case SDL_MOUSEMOTION:
			break;
		}
	}
}
