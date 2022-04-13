#pragma once
#include <GL/glew.h>
#include <string>
using namespace std;

class GLS_Program
{
private:
	GLuint programID; //va a leer el gls en archivo de texto para que luego lo interprete
	GLuint fragmentShaderID;
	GLuint vertexShaderID;
	void compileShader(const string& shaderPath, GLuint id);
public:
	GLS_Program();
	~GLS_Program();
	int numAtribute;
	void addAtribute(const string& atributeName);
	void use();
	void unuse();
	void compileShaders(const string& vertexShaderFilePath,
		const string& fragmentShaderFilePath);
	void linkShader();
};

