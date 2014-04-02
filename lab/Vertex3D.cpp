#include "Vertex3D.h"

Vertex3D::Vertex3D()
{
	this->x = 0;
	this->y = 0;
	this->z = 0;
}

Vertex3D::Vertex3D(GLfloat x, GLfloat y, GLfloat z)
{
	this->x = x;
	this->y = y;
	this->z = z;
}

Vertex3D::~Vertex3D()
{

}

GLfloat Vertex3D::getX()
{
	return this->x;
}

GLfloat Vertex3D::getY()
{
	return this->y;
}

GLfloat Vertex3D::getZ()
{
	return this->z;
}