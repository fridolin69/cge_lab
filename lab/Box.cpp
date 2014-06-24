#include "Box.h"

Box::Box(Vertex3D * pos, GLfloat size, GLuint texture)
{
	this->position = pos;
	this->size = size;
	this->vertexCount = 24;
	this->type = GL_QUADS;
	this->texture = texture;
}

void Box::generate()
{
	this->cornerA = new Vertex3D(0, 0, size);
	this->cornerB = new Vertex3D(size, 0, size);
	this->cornerC = new Vertex3D(size, 0, 0);
	this->cornerD = new Vertex3D(0, 0, 0);

	this->cornerE = new Vertex3D(0, size, size);
	this->cornerF = new Vertex3D(size, size, size);
	this->cornerG = new Vertex3D(size, size, 0);
	this->cornerH = new Vertex3D(0, size, 0);

	texCoords = new TexCoords *[this->vertexCount];
	vertices = new Vertex3D *[this->vertexCount];

	auto texCor1 = new TexCoords(0.0f, 0.0f);
	auto texCor2 = new TexCoords(1.0f, 0.0f);
	auto texCor3 = new TexCoords(1.0f, 1.0f);
	auto texCor4 = new TexCoords(0.0f, 1.0f);

	for (int i = 0; i < this->vertexCount; i = i + 4)
	{
		texCoords[i] = texCor1;
		texCoords[i + 1] = texCor2;
		texCoords[i + 2] = texCor3;
		texCoords[i + 3] = texCor4;
	}

	// bottom plate
	vertices[0] = cornerA;
	vertices[1] = cornerB;
	vertices[2] = cornerC;
	vertices[3] = cornerD;

	// front plate
	vertices[4] = cornerA;
	vertices[5] = cornerB;
	vertices[6] = cornerF;
	vertices[7] = cornerE;

	// top plate
	vertices[8] = cornerE;
	vertices[9] = cornerF;
	vertices[10] = cornerG;
	vertices[11] = cornerH;

	// back plate
	vertices[12] = cornerD;
	vertices[13] = cornerC;
	vertices[14] = cornerG;
	vertices[15] = cornerH;

	// left plate
	vertices[16] = cornerA;
	vertices[17] = cornerD;
	vertices[18] = cornerH;
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