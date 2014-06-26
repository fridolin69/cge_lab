#include "DrawableObjectBase.h"
#include "TgaTexture.h"

int DrawableObjectBase::getVertexCount()
{
	return this->vertexCount;
}

Vertex3D ** DrawableObjectBase::getVertices()
{
	return this->vertices;
}

TgaTexture * DrawableObjectBase::getTexture()
{
	return this->texture;
}

DrawableObjectBase::DrawableObjectBase(Vertex3D* position, TgaTexture* texture)
	: position(position), texture(texture)
{
	vertices = nullptr;
	texCoords = nullptr;
	normals = nullptr;
	vertexCount = 0;
	type = 0;
}

Vertex3D** DrawableObjectBase::getNormals()
{
	return this->normals;
}

TexCoords** DrawableObjectBase::getTexCoords()
{
	return this->texCoords;
}

Vertex3D * DrawableObjectBase::getPosition()
{
	return this->position;
}

GLenum DrawableObjectBase::getObjectType()
{
	return this->type;
}