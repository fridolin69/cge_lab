#include "DrawableObjectBase.h"
#include "TgaTexture.h"
#include "Coord2D.h"

TgaTexture * DrawableObjectBase::getTexture()
{
	return this->texture;
}

DrawableObjectBase::DrawableObjectBase(Coord3D* position, TgaTexture* texture)
	: position(position), texture(texture)
{
	vertices = nullptr;
	normals = nullptr;
	texCoords = nullptr;
	vertexCount = 0;
	type = 0;
}

std::vector<Coord3D*> * DrawableObjectBase::getVertices()
{
	return this->vertices;
}

std::vector<Coord3D*> * DrawableObjectBase::getNormals()
{
	return this->normals;
}

std::vector<Coord2D*> * DrawableObjectBase::getTexCoords()
{
	return this->texCoords;
}

int DrawableObjectBase::getIterations()
{
	return this->iterations;
}

Coord3D * DrawableObjectBase::getPosition()
{
	return this->position;
}

GLenum DrawableObjectBase::getObjectType()
{
	return this->type;
}