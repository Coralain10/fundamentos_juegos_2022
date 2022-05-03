#include "ImageLoader.h"
#include "IOManager.h"
#include "Error.h"
#include "picoPNG.h"

GLTexture ImageLoader::loadPNG(std::string filePath)
{
    GLTexture texture = {};
    std::vector<unsigned char> out;
    std::vector<unsigned char> in;
    unsigned long width, height;

    if (!IOManager::readFileToBuffer(filePath, in)) {
        fatalError("No se puede leer el archivo " + filePath);
    }
    int errorCode = decodePNG(out, width, height, &(in[0]), in.size());
    if (errorCode != 0) {
        fatalError("No se puede decodear la imagen " + std::to_string(errorCode));
    }

    glGenTextures(1, &(texture.id));
    glBindTexture(GL_TEXTURE_2D, texture.id);
    glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, width, height, 0, GL_RGBA, GL_UNSIGNED_BYTE, &(out[0]));
    //GG http://www.opengl-tutorial.org/intermediate-tutorials/tutorial-10-transparency/
    glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA); // GG
    glEnable(GL_BLEND);// GG
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR_MIPMAP_LINEAR);

    glGenerateMipmap(GL_TEXTURE_2D); //Decirle a los archivos que no se distorcionen
    glBindTexture(GL_TEXTURE_2D, 0); //limpiar memoria
    texture.width = width;
    texture.height = height;
    return texture;
}
