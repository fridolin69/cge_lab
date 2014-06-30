#include "Coord2D.h"


Coord2D::Coord2D(GLfloat x, GLfloat y): x(x),y(y)
{

}


Coord2D::~Coord2D()
{

}

GLfloat* Coord2D::toArray()
{
	return new GLfloat[] {x, y};
}