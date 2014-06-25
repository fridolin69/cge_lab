#include "TexCoords.h"


TexCoords::TexCoords(GLfloat x, GLfloat y)
{
	this->x = x;
	this->y = y;
}


TexCoords::~TexCoords()
{
}

GLfloat TexCoords::getY()
{
	return this->y;
}

GLfloat TexCoords::getX()
{
	return this->x;
}
