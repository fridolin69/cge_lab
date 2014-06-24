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