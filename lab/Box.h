#ifndef _BOX_H_
#define _BOX_H_

#include "DrawableObjectBase.h"

class Box : public DrawableObjectBase
{
private:
	Coord3D * A;
	Coord3D * B;
	Coord3D * C;
	Coord3D * D;

	Coord3D * E;
	Coord3D * F;
	Coord3D * G;
	Coord3D * H;

	GLfloat size;
	GLfloat height;

public:
	Box(Coord3D* position, GLfloat size, TgaTexture* texture);
	Box(Coord3D* position, GLfloat height, GLfloat width, TgaTexture* texture);
	
	virtual ~Box();

	void generate() override;
};

#endif