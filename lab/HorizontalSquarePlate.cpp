#include "HorizontalSquarePlate.h"


HorizontalSquarePlate::HorizontalSquarePlate(Vertex3D * pos, GLfloat size, Color * color)
{
	this->position = pos;
	this->size = size;
	this->vertexCount = 4;
	this->type = GL_QUADS;
	this->color = color;
}


HorizontalSquarePlate::~HorizontalSquarePlate()
{
	delete cornerA;
	delete cornerB;
	delete cornerC;
	delete cornerD;
}

void HorizontalSquarePlate::generate()
{
	this->cornerA = new Vertex3D(0, 0, 0);
	this->cornerB = new Vertex3D(size, 0, 0);
	this->cornerC = new Vertex3D(size, 0, size);
	this->cornerD = new Vertex3D(0, 0, size);

	vertices = new Vertex3D *[this->vertexCount];

	vertices[0] = cornerA;
	vertices[1] = cornerB;
	vertices[2] = cornerC;
	vertices[3] = cornerD;
}