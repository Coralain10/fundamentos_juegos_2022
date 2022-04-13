#include "Sprite.h"
#include "Vertex.h"
#include <cstddef> //permite calcular el espacio en memoria

Sprite::Sprite()
{
	vboID = 0;
}

Sprite::~Sprite()
{
	if (vboID != 0) {
		glDeleteBuffers(1, &vboID);
	}
}

void Sprite::init(float _x, float _y, int _width, int _height)
{
	x = _x;
	y = _y;
	width = _width;
	height = _height;

	if (vboID == 0) {
		//inicializa: reserva memoria y todo se volcará en esa variable
		glGenBuffers(1, &vboID);
	}

	/*float vertexData[12];
	vertexData[0] = x + width;
	vertexData[1] = y + height;
	vertexData[2] = x;
	vertexData[3] = y + height;
	vertexData[4] = x;
	vertexData[5] = y;
	vertexData[6] = x;
	vertexData[7] = y;
	vertexData[8] = x + width;
	vertexData[9] = y;
	vertexData[10] = x + width;
	vertexData[11] = y + height;*/

	Vertex vertexData[6];
	vertexData[0].setPostion(x + width, y + height);
	vertexData[1].setPostion(x, y + height);
	vertexData[2].setPostion(x, y);
	vertexData[3].setPostion(x, y);
	vertexData[4].setPostion(x + width, y);
	vertexData[5].setPostion(x + width, y + height);
	/*vertexData[0].setColor();
	vertexData[1].setColor();
	vertexData[2].setColor();
	vertexData[3].setColor();*/
	vertexData[4].setColor(200, 200, 200, 255);
	vertexData[5].setColor(200, 200, 200, 255);

	glBindBuffer(GL_ARRAY_BUFFER, vboID);
	glBufferData(GL_ARRAY_BUFFER, sizeof(vertexData),
		vertexData, GL_STATIC_DRAW);
	glBindBuffer(GL_ARRAY_BUFFER, 0);
}

void Sprite::draw()
{
	glBindBuffer(GL_ARRAY_BUFFER, vboID);
	glEnableVertexAttribArray(0); 
	
	//0 solo para coordenadas
	//glVertexAttribPointer(0,2,GL_FLOAT,GL_FALSE,0,0);
	glVertexAttribPointer(0, 2, GL_FLOAT, GL_FALSE, sizeof(Vertex),
		(void*)offsetof(Vertex,position));
	//1 color
	glVertexAttribPointer(1, 2, GL_UNSIGNED_BYTE, GL_TRUE, sizeof(Vertex),
		(void*)offsetof(Vertex,color));

	glDrawArrays(GL_TRIANGLES,0,6);
	glDisableVertexAttribArray(0);
	glBindBuffer(GL_ARRAY_BUFFER, 0);
}
