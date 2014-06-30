#include "Util.h"
#include "Plate.h"

Plate::Plate(Vertex3D* position, GLfloat zWidth, GLfloat size, TgaTexture* texture)
	: DrawableObjectBase(position, texture), size(size)
{
	this->vertexCount = 4;
	this->type = GL_QUADS;
	this->zWidth = zWidth;
}

Plate::~Plate()
{
	delete this->cornerA;
	delete this->cornerB;
	delete this->cornerC;
	delete this->cornerD;

	delete this->position;
	delete this->vertices;
}

void Plate::generate()
{
	this->cornerA = new Vertex3D( 0,    0,   zWidth);
	this->cornerB = new Vertex3D( size, 0,   zWidth);
	this->cornerC = new Vertex3D( size, 0,   0);
	this->cornerD = new Vertex3D( 0,    0,   0);

	texCoords = new TexCoords *[this->vertexCount];
	vertices =  new Vertex3D  *[this->vertexCount];
	normals =   new Vertex3D  *[this->vertexCount];

	texCoords[0] = new TexCoords(  0.0f,   0.0f  );
	texCoords[1] = new TexCoords(  size,   0.0f  );
	texCoords[2] = new TexCoords(  size,   zWidth);
	texCoords[3] = new TexCoords(  0.0f,   zWidth);

	Vertex3D * normalBottom = Util::normal(cornerA, cornerB, cornerC, cornerD);

	// bottom plate
	vertices[0] = cornerA;
	vertices[1] = cornerB;
	vertices[2] = cornerC;
	vertices[3] = cornerD;

	normals[0] = normals[1] = normals[2] = normals[3] = normalBottom;
}