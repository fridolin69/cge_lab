#include "DrawableObjectBase.h"

int DrawableObjectBase::getVertexCount()
{
	return this->vertexCount;
}

Vertex3D ** DrawableObjectBase::getVertices()
{
	return this->vertices;
}

GLuint DrawableObjectBase::getTexture()
{
	return this->texture;
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