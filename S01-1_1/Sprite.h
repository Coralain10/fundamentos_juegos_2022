#pragma once
#include <GL/glew.h>
using namespace std;

class Sprite
{
private:
	float x, y;
	int width, height;
	float vertexData;
	GLuint vboID; //Vertex Buffer Object ID

public:
	Sprite();
	~Sprite();
	void init(float _x, float _y, int _width, int _height);
	void draw();
};

