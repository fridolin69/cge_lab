#pragma once
#include <GL\glut.h>

typedef struct
{
	short int width;
	short int height;
} ImageSize;

class TgaTexture
{
private:
	char * path;
	GLuint textureId;
	GLint rgbMode;
	GLint textureWrapMode;
	int status;
	ImageSize size;

public:
	TgaTexture(char * path, GLint glTextureWrapMode);
	~TgaTexture();

	void loadImage();
	GLint getRGBMode();
	GLint getWrapMode();
	GLuint getTextureId();
	ImageSize getSize();
};