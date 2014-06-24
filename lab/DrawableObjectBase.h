#ifndef _DRAWABLE_OBJECT_H_
#define _DRAWABLE_OBJECT_H_

#include "Vertex3D.h"
#include "Color.h"
#include "TexCoords.h"

// base class for any drawable object
class DrawableObjectBase
{
private:
	
protected:
	int vertexCount;
	GLenum type;					// defines the type of geometry object the vertices should build, will be passed directly to glBegin()
	Vertex3D * position;
	Vertex3D ** vertices;

	TexCoords ** texCoords;
	GLuint texture;

public:
	virtual ~DrawableObjectBase() {}

	virtual void generate() = 0;	// create the internal array returned at getVertices()

	Vertex3D ** getVertices();		// returns the array of vertices

	GLuint getTexture();
	TexCoords ** getTexCoords();

	GLenum getObjectType();			// returns the GLenum of the object
	Vertex3D * getPosition();		// returns the translation vector
	int getVertexCount();			// returns the number of vertices returned
};

#endif