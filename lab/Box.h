#ifndef _BOX_H_
#define _BOX_H_

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
	Box(Vertex3D* position, GLfloat size, TgaTexture* texture);
	virtual ~Box();

	void generate() override;
};

#endif