#include "Color.h"

Color::Color(GLfloat red, GLfloat green, GLfloat blue)
{
	Color(red, green, blue, 1);
}

Color::Color(GLfloat red, GLfloat green, GLfloat blue, GLfloat alpha)
{
	this->red = red;
	this->green = green;
	this->blue = blue;
	this->alpha = alpha;
}

GLfloat Color::getRed()
{
	return this->red;
}

GLfloat Color::getGreen()
{
	return this->green;
}

GLfloat Color::getBlue()
{
	return this->blue;
}

GLfloat Color::getAlpha()
{
	return this->alpha;
}