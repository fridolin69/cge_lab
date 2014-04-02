#ifndef _3D_VERTEX_H_
#define _3D_VERTEX_H_

#include <GL\glut.h>

class Vertex3D
{
private:
	GLfloat x;
	GLfloat y;
	GLfloat z;

public:
	Vertex3D();
	Vertex3D(GLfloat x, GLfloat y, GLfloat z);
	~Vertex3D();

	GLfloat getX();
	GLfloat getY();
	GLfloat getZ();
};

#endif