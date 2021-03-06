#include "ImageLoader.h"
#include "IOManager.h"
#include "Error.h"
#include "picoPNG.h"

GLTexture ImageLoader::loadPNG(string filePath) {

	GLTexture texture = {};
	vector <unsigned char> in;
	vector <unsigned char> out;
	unsigned long width, height;
	if (!IOManager::readFileBuffer(filePath, in))
	{
		fatalError("Could not read" + filePath);


	}
	int errorCode = decodePNG(out,width,height,&(in[0]),in.size());

	if (errorCode != 0) {
		fatalError("Can't decode image with error" + std::to_string(errorCode));
	}
	//CUANTAS TEXTUREAS SE GENERAN
	glGenTextures(1, &(texture.id));

	//TIPO DE TEXTURA
	glBindTexture(GL_TEXTURE_2D, texture.id);

	//convierte a imagen
	glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, width, height, 0, GL_RGBA, GL_UNSIGNED_BYTE,&(out[0]));

	//repetir
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
	//angrandar achicar
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER,GL_LINEAR_MIPMAP_LINEAR);
	
	
	glGenerateMipmap(GL_TEXTURE_2D);

	glBindTexture(GL_TEXTURE, 0);

	
	texture.width = width;
	texture.height = height;
	return texture;

}
