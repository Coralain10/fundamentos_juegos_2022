#include "GLS_Program.h"
#include "Error.h"
#include <iostream>
#include <fstream>
#include <vector>
//using namespace std;

GLS_Program::GLS_Program():programID(0),
	vertexShaderID(0),fragmentShaderID(0), numAtribute(0)
{
}

GLS_Program::~GLS_Program()
{
}

void GLS_Program::compileShader(const string& shaderPath, GLuint id)
{
	string fileContent = "";
	string line = "";
	ifstream shaderFile(shaderPath);
	if (shaderFile.fail()) {
		fatalError("No se puede abrir el archivo" + shaderPath);
	}
	while (getline(shaderFile,line)) {
		fileContent += line + "\n";
	}
	shaderFile.close();
	const char* contents = fileContent.c_str();
	//todo lo que ha leido lo tenga ahi para que se lo pase al shader, aun no lo pasa a la variable id 
	glShaderSource(id, 1, &contents, nullptr); // 1 de 1 shader
	glCompileShader(id); //shader en codigo de c++

	GLint isCompiled = 0;
	glGetShaderiv(id, GL_COMPILE_STATUS, &isCompiled); //Verifica si todo funciono bien
	if (isCompiled == GL_FALSE) {
		GLint maxLength = 0;
		glGetShaderiv(id, GL_INFO_LOG_LENGTH, &maxLength);
		std::vector<GLchar> infoLog(maxLength);
		glGetShaderInfoLog(id, maxLength, &maxLength, &infoLog[0]);

		std::cout << shaderPath << endl;
		fatalError("Shader no compila " + printf("%s", &(infoLog[0])));
		glDeleteShader(id);
		return;
	}
}

void GLS_Program::addAtribute(const string& atributeName)
{
}

void GLS_Program::use()
{
}

void GLS_Program::unuse()
{
}

void GLS_Program::compileShaders(const string& vertexShaderFilePath, const string& fragmentShaderFilePath)
{
	//lee, interpreta, compilar shader
	programID = glCreateProgram(); //crea el compilador
	//xy de los puntos
	vertexShaderID = glCreateShader(GL_VERTEX_SHADER);
	if (vertexShaderID == 0) {
		fatalError("No se puede compilar el shader Vertex");
	}
	//colorear los pixeles
	fragmentShaderID = glCreateShader(GL_FRAGMENT_SHADER);
	if (fragmentShaderID == 0) {
		fatalError("No se puede compilar el shader Fragment");
	}

	compileShader(vertexShaderFilePath, vertexShaderID);
	compileShader(fragmentShaderFilePath, fragmentShaderID);
}

void GLS_Program::linkShader()
{
	//programID traduce de gls a c++
	glAttachShader(programID, vertexShaderID);
	glAttachShader(programID, fragmentShaderID);

	glLinkProgram(programID);
	GLint isLinked = 0;
	glGetProgramiv(programID, GL_LINK_STATUS, (int*)isLinked);
	if (isLinked == GL_FALSE) {
		GLint maxLenght = 0;
		glGetProgramiv(programID, GL_INFO_LOG_LENGTH, &maxLenght);
		std::vector<GLchar> infoLoght(maxLenght);
		glGetProgramInfoLog(programID, maxLenght, &maxLenght, &infoLoght[0]);
		glDeleteProgram(programID);
		fatalError("Shaders no se linkearon" + printf("%s", &(infoLoght[0])));
		glDeleteShader(vertexShaderID);
		glDeleteShader(fragmentShaderID);
		return;
	}
	glDetachShader(programID, vertexShaderID);
	glDetachShader(programID, fragmentShaderID); //dejando las variables sin valor
	glDeleteShader(vertexShaderID);
	glDeleteShader(fragmentShaderID);
}
