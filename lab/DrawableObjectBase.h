#ifndef _DRAWABLE_OBJECT_H_
#define _DRAWABLE_OBJECT_H_

#include "Vertex3D.h"
#include "Color.h"

// TODO: add texture

// base class for any drawable object
class DrawableObjectBase
{
private:
	
protected:
	int vertexCount;
	GLenum type;					// defines the type of geometry object the vertices should build, will be passed directly to glBegin()
	Color * color;					
	Vertex3D * position;
	Vertex3D ** vertices;

public:
	virtual void generate() = 0;	// create the internal array returned at getVertices()

	Vertex3D ** getVertices();		// returns the array of vertices
	Color * getColor();				// return the color of the object
	GLenum getObjectType();			// returns the GLenum of the object
	Vertex3D * getPosition();		// returns the translation vector
	int getVertexCount();			// returns the number of vertices returned
};

#endif