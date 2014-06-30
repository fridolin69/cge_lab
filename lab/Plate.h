#pragma once
#include "DrawableObjectBase.h"
#include "Vertex3D.h"

class Plate : public DrawableObjectBase
{
private:
	Vertex3D * cornerA;
	Vertex3D * cornerB;
	Vertex3D * cornerC;
	Vertex3D * cornerD;

	GLfloat size;
	GLfloat zWidth;
public:
	Plate(Vertex3D* position, GLfloat zWidth, GLfloat size, TgaTexture* texture);

	virtual ~Plate();

	void generate() override;
};

