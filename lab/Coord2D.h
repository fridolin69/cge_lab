#pragma once
#include <GL\glut.h>

class Coord2D
{
public:
	const GLfloat x, y;

public:
	Coord2D(GLfloat x, GLfloat y);
	~Coord2D();

	GLfloat * toArray();
};

