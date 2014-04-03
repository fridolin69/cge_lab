#ifndef _HORIZONTAL_SQUARE_PLATE_H
#define _HORIZONTAL_SQUARE_PLATE_H

#include "Vertex3D.h"
#include "DrawableObjectBase.h"

class HorizontalSquarePlate : public DrawableObjectBase
{
private:
	Vertex3D * cornerA;
	Vertex3D * cornerB;
	Vertex3D * cornerC;
	Vertex3D * cornerD;

	GLfloat size;

public:
	HorizontalSquarePlate(Vertex3D * pos, GLfloat size, Color * color);
	virtual ~HorizontalSquarePlate();

	void generate();
};

#endif