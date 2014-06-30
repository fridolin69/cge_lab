#include <cwchar>
#include <fstream>
#include "TgaTexture.h"

#pragma warning(disable: 4996)
#include <iostream>

using namespace std;

TgaTexture::TgaTexture(char* path, GLint glTextureWrapMode)
{
	this->path = path;
	this->textureId = -1;
	this->textureWrapMode = glTextureWrapMode;
}

TgaTexture::~TgaTexture()
{

}

void TgaTexture::loadImage()
{
	// open the file for reading (binary mode)
	FILE * file = fopen(path, "rb");
	if (file == NULL) 
	{
		cout << "Cannot open image file" << endl;
		throw new exception("Cannot open image file");
	}

	clearerr(file);

	unsigned char cGarbage;
	short int iGarbage;

	fread(&cGarbage, sizeof(unsigned char), 1, file);
	fread(&cGarbage, sizeof(unsigned char), 1, file);

	unsigned char type;

	// type must be 2 or 3
	fread(&type, sizeof(unsigned char), 1, file);

	if (type == 1)
	{
		throw new exception("Image must not be of type 1 (indexed color)");
	}

	fread(&iGarbage, sizeof(short int), 1, file);
	fread(&iGarbage, sizeof(short int), 1, file);
	fread(&cGarbage, sizeof(unsigned char), 1, file);
	fread(&iGarbage, sizeof(short int), 1, file);
	fread(&iGarbage, sizeof(short int), 1, file);

	fread(&size.width, sizeof(short int), 1, file);
	fread(&size.height, sizeof(short int), 1, file);

	unsigned char pixelDepth;
	fread(&pixelDepth, sizeof(unsigned char), 1, file);

	int pixelSize = pixelDepth / 8;
	rgbMode = (pixelSize == 4) ? GL_RGBA : GL_RGB;

	fread(&cGarbage, sizeof(unsigned char), 1, file);

	// check for errors when loading the header
	if (ferror(file)) 
	{
		throw new exception("An error occured while reading the file header");
	}

	int totalBytes = size.width * size.height * pixelSize;
	unsigned char * imageData = new unsigned char[totalBytes];

	fread(imageData, sizeof(unsigned char), totalBytes, file);

	unsigned char tmp;

	// mode=3 or 4 implies that the image is RGB(A). However TGA
	// stores it as BGR(A) so we'll have to swap R and B.
	for (int i = 0; i < totalBytes; i += pixelSize)
	{
		tmp = imageData[i];
		imageData[i] = imageData[i + 2];
		imageData[i + 2] = tmp;
	}

	// check for errors when reading the pixels
	if (ferror(file)) 
	{
		throw new exception("An error occured while reading file data");
	}

	fclose(file);

	glGenTextures(1, &textureId);
	glBindTexture(GL_TEXTURE_2D, textureId);

	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);

	glTexImage2D(GL_TEXTURE_2D, 0, rgbMode, size.width, size.height, 0, rgbMode, GL_UNSIGNED_BYTE, imageData);

	delete imageData;
}

GLint TgaTexture::getRGBMode()
{
	if (textureId == -1)
	{
		this->loadImage();
	}
	return this->rgbMode;
}

GLint TgaTexture::getWrapMode()
{
	return this->textureWrapMode;
}

ImageSize TgaTexture::getSize()
{
	if (textureId == -1)
	{
		this->loadImage();
	}
	return this->size;
}

GLuint TgaTexture::getTextureId()
{
	if (textureId == -1)
	{
		this->loadImage();
	}
	return this->textureId;
}