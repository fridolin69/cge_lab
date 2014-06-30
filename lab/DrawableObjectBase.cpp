#include "DrawableObjectBase.h"
#include "TgaTexture.h"
#include "Coord2D.h"
#include <algorithm>

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

DrawableObjectBase::~DrawableObjectBase()
{
	for_each(normals->begin(), normals->end(), [](Coord3D * coord) -> void {
		if (coord != nullptr)
		{
			//delete coord;
			coord = nullptr;
		}
	});

	for_each(texCoords->begin(), texCoords->end(), [](Coord2D * coord) -> void {
		if (coord != nullptr)
		{
			//delete coord;
			coord = nullptr;
		}
	});

	for_each(vertices->begin(), vertices->end(), [](Coord3D * coord) -> void {
		if (coord != nullptr)
		{
			//delete coord;
			coord = nullptr;
		}
	});

	delete this->position;
	delete this->vertices;
	delete this->normals;
	delete this->texCoords;

	if (texture != nullptr)
	{
		delete texture;
		texture = nullptr;
	}
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