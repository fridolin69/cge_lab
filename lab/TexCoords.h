#pragma once
#include <GL\glut.h>

class TexCoords
{
private:
	GLfloat x, y;

public:
	TexCoords(GLfloat x, GLfloat y);
	~TexCoords();

	GLfloat getX();
	GLfloat getY();
};

