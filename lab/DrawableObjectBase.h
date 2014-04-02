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
	GLenum type; // defines the type of geometry object the vertices should build, will be passed directly to glBegin()
	Color * color;
	Vertex3D * position;
	Vertex3D ** vertices;

public:
	void generate(); // create the internal array returned at getObject()

	virtual Color * getColor() = 0; // return the color of the object
	virtual GLenum getObjectType() = 0; // returns the GLenum of the object
	virtual int getVertexCount() = 0; // returns the number of vertices returned
	virtual Vertex3D ** getVertices() = 0; // returns the array of vertices
	virtual Vertex3D * getPosition() = 0; // returns the translation vector
};

#endif