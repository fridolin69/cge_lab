#ifndef _COLOR_H_
#define _COLOR_H_

#include <GL\glut.h>

// TODO: create default cstr with default color

// represents the color of a DrawableObject
class Color
{
private:
	GLfloat red;
	GLfloat green;
	GLfloat blue;
	GLfloat alpha;

public:
	Color(GLfloat red, GLfloat green, GLfloat blue); // cstr without alpha channel
	Color(GLfloat red, GLfloat green, GLfloat blue, GLfloat alpha); // cstr with alpha channel

	GLfloat getRed();
	GLfloat getGreen();
	GLfloat getBlue();
	GLfloat getAlpha();
};

#endif