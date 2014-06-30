#pragma once
#include "DrawableObjectBase.h"
#include "Coord3D.h"

class Plate : public DrawableObjectBase
{
private:
	Coord3D * A;
	Coord3D * B;
	Coord3D * C;
	Coord3D * D;

	GLfloat size;
	GLfloat zWidth;

public:
	Plate(Coord3D* position, GLfloat zWidth, GLfloat size, TgaTexture* texture);
	virtual ~Plate();

	void generate() override;
};