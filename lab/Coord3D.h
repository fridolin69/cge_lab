#ifndef _3D_VERTEX_H_
#define _3D_VERTEX_H_

#include <GL\glut.h>

class Coord3D
{
public:
	const GLfloat x, y, z;

public:
	Coord3D();
	Coord3D(GLfloat x, GLfloat y, GLfloat z);
	~Coord3D();

	Coord3D * cross(const Coord3D * other);
	Coord3D * operator+(const Coord3D * other);
	Coord3D * operator-(const Coord3D * other);

	Coord3D * operator/(const float factor);
	Coord3D * operator*(const float factor);

	GLfloat * toArray();
};

#endif