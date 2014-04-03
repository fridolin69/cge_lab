#include "DrawableObjectBase.h"

int DrawableObjectBase::getVertexCount()
{
	return this->vertexCount;
}

Vertex3D ** DrawableObjectBase::getVertices()
{
	return this->vertices;
}

Vertex3D * DrawableObjectBase::getPosition()
{
	return this->position;
}

GLenum DrawableObjectBase::getObjectType()
{
	return this->type;
}

Color * DrawableObjectBase::getColor()
{
	return this->color;
}