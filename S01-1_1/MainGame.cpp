#include "MainGame.h"
//#import <iostream>
#include "Error.h"
#include <GL/glew.h>

//antes era width(800), height(600)
MainGame::MainGame() :window(nullptr), width(640), height(640), gameState(GameState::PLAY)
{
}

MainGame::~MainGame()
{
}

void MainGame::init()
{
	time = 0.0f;
	SDL_Init(SDL_INIT_EVERYTHING);
	window = SDL_CreateWindow("Hey!",
		SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED,
		width, height, SDL_WINDOW_OPENGL);
	if (window == nullptr) {
		fatalError("No se pudo inicalizar el SDL");
	}
	SDL_GLContext glContext = SDL_GL_CreateContext(window);
	GLenum error = glewInit();
	if (error != GLEW_OK) {
		fatalError("No se pudo inicializar el GLEW");
	}
	SDL_GL_SetAttribute(SDL_GL_DOUBLEBUFFER, 1);
	//glClearColor(0.0f, 0.5f, 0.75f, 0.0f);
	glClearColor(0.0f, 0.0f, 0.0f, 0.0f);
	initShaders();
}

void MainGame::run()
{
	init();
	sprite.init(-1, -1, 1, 1, "Textures/texture1.png");
	spriteTR.init(0, 0, 1, 1, "Textures/texture2.png");
	update();
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

void MainGame::initShaders()
{
	program.compileShaders("Shaders/colorShaderVert.vert", "Shaders/colorShaderFrag.frag");
	program.addAtribute("vertexPosition");
	program.addAtribute("vertexColor");
	program.addAtribute("vertexUV");
	program.linkShader();
}


void MainGame::update()
{
	while (gameState == GameState::PLAY)
	{
		//dibujar pantalla y otros
		processInput();
		time += 0.002f;
		draw();
	}
}


void MainGame::draw()
{
	glClearDepth(1.0);
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	program.use();
	glActiveTexture(GL_TEXTURE0);
	GLuint imageLocation = program.getUniformLocation("myImage");
	glUniform1i(imageLocation, 0);
	// variable delta lo saca del shader
	GLuint timeLocation = program.getUniformLocation("delta");
	glUniform1f(timeLocation, time);
	sprite.draw();
	spriteTR.draw();
	program.unuse();
	SDL_GL_SwapWindow(window);
}
