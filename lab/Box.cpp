#include "Box.h"

Box::Box(Vertex3D * pos, GLfloat size, Color * color)
{
	this->position = pos;
	this->size = size;
	this->vertexCount = 24;
	this->type = GL_QUADS;
	this->color = color;
}

void Box::generate()
{
	this->cornerA = new Vertex3D(0, 0, 0);
	this->cornerB = new Vertex3D(size, 0, 0);
	this->cornerC = new Vertex3D(size, 0, size);
	this->cornerD = new Vertex3D(0, 0, size);

	this->cornerE = new Vertex3D(0, size, 0);
	this->cornerF = new Vertex3D(size, size, 0);
	this->cornerG = new Vertex3D(size, size, size);
	this->cornerH = new Vertex3D(0, size, size);

	vertices = new Vertex3D *[this->vertexCount];

	// bottom plate
	vertices[0] = cornerA;
	vertices[1] = cornerB;
	vertices[2] = cornerC;
	vertices[3] = cornerD;

	// front plate
	vertices[4] = cornerA;
	vertices[5] = cornerB;
	vertices[6] = cornerE;
	vertices[7] = cornerF;

	// top plate
	vertices[8] = cornerE;
	vertices[9] = cornerF;
	vertices[10] = cornerG;
	vertices[11] = cornerH;

	// back plate
	vertices[12] = cornerC;
	vertices[13] = cornerD;
	vertices[14] = cornerG;
	vertices[15] = cornerH;

	// left plate
	vertices[16] = cornerA;
	vertices[17] = cornerD;
	vertices[18] = cornerF;
	vertices[19] = cornerE;

	// right plate
	vertices[20] = cornerB;
	vertices[21] = cornerC;
	vertices[22] = cornerG;
	vertices[23] = cornerF;
}

Box::~Box()
{
	delete this->cornerA;
	delete this->cornerB;
	delete this->cornerC;
	delete this->cornerD;

	delete this->cornerE;
	delete this->cornerF;
	delete this->cornerG;
	delete this->cornerH;

	delete this->position;
}