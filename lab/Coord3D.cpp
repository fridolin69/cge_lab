#include "Coord3D.h"

Coord3D::Coord3D(GLfloat x, GLfloat y, GLfloat z): x(x),y(y),z(z)
{

}

Coord3D::~Coord3D()
{

}

Coord3D * Coord3D::cross(Coord3D const* other)
{
	return new Coord3D(
		this->y * other->z - this->z * other->y,
		other->x * this->z - other->z * this->x,
		this->x * other->y - this->y * other->x
		);
}

Coord3D * Coord3D::operator+(Coord3D const * other)
{
	return new Coord3D(this->x + other->x, this->y + other->y, this->z + other->z);
}

Coord3D * Coord3D::operator-(Coord3D const * other)
{
	return new Coord3D(this->x - other->x, this->y - other->y, this->z - other->z);
}

Coord3D* Coord3D::operator/(float const factor)
{
	return new Coord3D(this->x / factor, this->y / factor, this->z / factor);
}

Coord3D* Coord3D::operator*(float const factor)
{
	return new Coord3D(this->x * factor, this->y * factor, this->z * factor);
}

GLfloat* Coord3D::toArray()
{
	GLfloat * array = new GLfloat[4];
	array[0] = x;
	array[1] = y;
	array[2] = z;

	return array; // make room for 4 values (maybe someone wants to add w :) ?
}