#ifndef _BOX_H_
#define _BOX_H_

#include "Vertex3D.h"
#include "DrawableObjectBase.h"

class Box : public DrawableObjectBase
{
private:
	Vertex3D * cornerA;
	Vertex3D * cornerB;
	Vertex3D * cornerC;
	Vertex3D * cornerD;

	Vertex3D * cornerE;
	Vertex3D * cornerF;
	Vertex3D * cornerG;
	Vertex3D * cornerH;

	GLfloat size;

public:
	// TODO set color here too
	Box(Vertex3D * pos, GLfloat size);
	virtual ~Box();

	void generate();

	int getVertexCount();
	Color * getColor();
	GLenum getObjectType();
	Vertex3D ** getVertices(); // will return an array of 24 vertices, because this is a box
	Vertex3D * getPosition(); // return the translation vector
};

#endif