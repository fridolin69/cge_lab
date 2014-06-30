#include "Util.h"
#include "Box.h"

Box::Box(Vertex3D* position, GLfloat size, TgaTexture* texture)
	: DrawableObjectBase(position, texture), size(size)
{
	this->vertexCount = 24;
	this->type = GL_QUADS;
	this->height = size;
}

Box::Box(Vertex3D* position, GLfloat height, GLfloat size, TgaTexture* texture)
	: DrawableObjectBase(position, texture), size(size)
{
	this->vertexCount = 24;
	this->type = GL_QUADS;
	this->height = height;
}

void Box::generate()
{
	this->cornerA = new Vertex3D(0,    0,    size);
	this->cornerB = new Vertex3D(size, 0,    size);
	this->cornerC = new Vertex3D(size, 0,    0);
	this->cornerD = new Vertex3D(0,    0,    0);

	this->cornerE = new Vertex3D(0,    height, size);
	this->cornerF = new Vertex3D(size, height, size);
	this->cornerG = new Vertex3D(size, height, 0);
	this->cornerH = new Vertex3D(0,    height, 0);

	texCoords = new TexCoords *[this->vertexCount];
	vertices =  new Vertex3D  *[this->vertexCount];
	normals =   new Vertex3D  *[this->vertexCount];

	auto texCor1 = new TexCoords(0, 0);
	auto texCor2 = new TexCoords(1, 0);
	auto texCor3 = new TexCoords(1, 1);
	auto texCor4 = new TexCoords(0, 1);

	for (int i = 0; i < this->vertexCount; i = i + 4)
	{
		texCoords[i] = texCor1;
		texCoords[i + 1] = texCor2;
		texCoords[i + 2] = texCor3;
		texCoords[i + 3] = texCor4;
	}

	Vertex3D * normalBottom = Util::normal(cornerA, cornerB, cornerC, cornerD);
	Vertex3D * normalFront = Util::normal(cornerA, cornerB, cornerF, cornerE);
	Vertex3D * normalTop = Util::normal(cornerE, cornerF, cornerG, cornerH);
	Vertex3D * normalBack = Util::normal(cornerC, cornerD, cornerH, cornerG);
	Vertex3D * normalLeft = Util::normal(cornerD, cornerA, cornerE, cornerH);
	Vertex3D * normalRight = Util::normal(cornerB, cornerC, cornerG, cornerF);

	normals[0] = normals[1] = normals[2] = normals[3] = normalBottom;
	normals[4] = normals[5] = normals[6] = normals[7] = normalFront;
	normals[8] = normals[9] = normals[10] = normals[11] = normalTop;
	normals[12] = normals[13] = normals[14] = normals[15] = normalBack;
	normals[16] = normals[17] = normals[18] = normals[19] = normalLeft;
	normals[20] = normals[21] = normals[22] = normals[23] = normalRight;

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
	vertices[12] = cornerC;
	vertices[13] = cornerD;
	vertices[14] = cornerH;
	vertices[15] = cornerG;

	// left plate
	vertices[16] = cornerD;
	vertices[17] = cornerA;
	vertices[18] = cornerE;
	vertices[19] = cornerH;

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
	delete this->vertices;
	delete this->normals;
}