#pragma once
#include <string>
#include <GL/glew.h>
#include "GLTexture.h"

using namespace std;

class Sprite
{
private:
	float x, y;
	int width, height;
	float vertexData;
	GLTexture texture;
	GLuint vboID; //Vertex Buffer Object ID

public:
	Sprite();
	~Sprite();
	void init(float _x, float _y, int _width, int _height, string texturePath);
	void draw();
};

