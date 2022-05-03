#include "IOManager.h"
#include <fstream>
using namespace std;

bool IOManager::readFileToBuffer(string filePath, vector<unsigned char>& buffer) {
	ifstream file(filePath, ios::binary);
	if (file.fail()) {
		perror(filePath.c_str());
		return false;
	}
	file.seekg(0, ios::end);
	int fileSize = file.tellg();

	//los archivos de imagen tienen una cabecera
	//que es necesario quitarla para leer con otra cosa
	file.seekg(0, ios::beg);
	fileSize -= file.tellg();

	//rezizeando el vector acorde a la imagen
	buffer.resize(fileSize);
	file.read((char*)&(buffer[0]), fileSize);
	file.close();

	return true;
}