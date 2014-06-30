#include "Box.h"
#include <algorithm>

Box::Box(Coord3D* position, GLfloat size, TgaTexture* texture)
	: DrawableObjectBase(position, texture), size(size)
{
	this->vertexCount = 6*6;
	this->iterations = 6;
	this->type = GL_TRIANGLE_FAN;
	this->height = size;
}

Box::Box(Coord3D* position, GLfloat height, GLfloat size, TgaTexture* texture)
	: DrawableObjectBase(position, texture), size(size)
{
	this->vertexCount = 6*6;
	this->iterations = 6;
	this->type = GL_TRIANGLE_FAN;
	this->height = height;
}

void Box::generate()
{
	this->A = new Coord3D(0,    0,    size);
	this->B = new Coord3D(size, 0,    size);
	this->C = new Coord3D(size, 0,    0);
	this->D = new Coord3D(0,    0,    0);

	this->E = new Coord3D(0,    height, size);
	this->F = new Coord3D(size, height, size);
	this->G = new Coord3D(size, height, 0);
	this->H = new Coord3D(0,    height, 0);

	Coord3D * middleABCD = new Coord3D(size / 2, 0, size / 2);
	Coord3D * middleABFE = new Coord3D(size / 2, height / 2, size);
	Coord3D * middleEFGH = new Coord3D(size / 2, height, size / 2);
	Coord3D * middleCDHG = new Coord3D(size / 2, height / 2, 0);
	Coord3D * middleDAEH = new Coord3D(0, height / 2, size / 2);
	Coord3D * middleBCGF = new Coord3D(size, height / 2, size / 2);

	texCoords = new std::vector<Coord2D*>(vertexCount);
	vertices = new std::vector<Coord3D*>(vertexCount);
	normals = new std::vector<Coord3D*>(vertexCount);

	// bottom
	vertices->at(0) = middleABCD;
	vertices->at(1) = A;
	vertices->at(2) = B;
	vertices->at(3) = C;
	vertices->at(4) = D;
	vertices->at(5) = A;

	// texcoords
	texCoords->at(0) = new Coord2D(middleABCD->x, middleABCD->z);
	texCoords->at(1) = new Coord2D(A->x, A->z);
	texCoords->at(2) = new Coord2D(B->x, B->z);
	texCoords->at(3) = new Coord2D(C->x, C->z);
	texCoords->at(4) = new Coord2D(D->x, D->z);
	texCoords->at(5) = new Coord2D(A->x, A->z);

	// front
	vertices->at(6) = middleABFE;
	vertices->at(7) = A;
	vertices->at(8) = B;
	vertices->at(9) = F;
	vertices->at(10) = E;
	vertices->at(11) = A;

	// texcoords
	texCoords->at(6) = new Coord2D(middleABFE->x, middleABFE->y);
	texCoords->at(7) = new Coord2D(A->x, A->y);
	texCoords->at(8) = new Coord2D(B->x, B->y);
	texCoords->at(9) = new Coord2D(F->x, F->y);
	texCoords->at(10) = new Coord2D(E->x, E->y);
	texCoords->at(11) = new Coord2D(A->x, A->y);


	// top
	vertices->at(12) = middleEFGH;
	vertices->at(13) = E;
	vertices->at(14) = F;
	vertices->at(15) = G;
	vertices->at(16) = H;
	vertices->at(17) = E;

	// texcoords
	texCoords->at(12) = new Coord2D(middleEFGH->x, middleEFGH->z);
	texCoords->at(13) = new Coord2D(E->x, E->z);
	texCoords->at(14) = new Coord2D(F->x, F->z);
	texCoords->at(15) = new Coord2D(G->x, G->z);
	texCoords->at(16) = new Coord2D(H->x, H->z);
	texCoords->at(17) = new Coord2D(E->x, E->z);


	// back
	vertices->at(18) = middleCDHG;
	vertices->at(19) = C;
	vertices->at(20) = D;
	vertices->at(21) = H;
	vertices->at(22) = G;
	vertices->at(23) = C;

	// texcoords
	texCoords->at(18) = new Coord2D(middleCDHG->x, middleCDHG->y);
	texCoords->at(19) = new Coord2D(C->x, C->y);
	texCoords->at(20) = new Coord2D(D->x, D->y);
	texCoords->at(21) = new Coord2D(H->x, H->y);
	texCoords->at(22) = new Coord2D(G->x, G->y);
	texCoords->at(23) = new Coord2D(C->x, C->y);


	// left
	vertices->at(24) = middleDAEH;
	vertices->at(25) = D;
	vertices->at(26) = A;
	vertices->at(27) = E;
	vertices->at(28) = H;
	vertices->at(29) = D;

	// texcoords
	texCoords->at(24) = new Coord2D(middleDAEH->z, middleDAEH->y);
	texCoords->at(25) = new Coord2D(D->z, D->y);
	texCoords->at(26) = new Coord2D(A->z, A->y);
	texCoords->at(27) = new Coord2D(E->z, E->y);
	texCoords->at(28) = new Coord2D(H->z, H->y);
	texCoords->at(29) = new Coord2D(D->z, D->y);


	// right
	vertices->at(30) = middleBCGF;
	vertices->at(31) = B;
	vertices->at(32) = C;
	vertices->at(33) = G;
	vertices->at(34) = F;
	vertices->at(35) = B;

	// texcoords
	texCoords->at(30) = new Coord2D(middleBCGF->z, middleBCGF->y);
	texCoords->at(31) = new Coord2D(B->z, B->y);
	texCoords->at(32) = new Coord2D(C->z, C->y);
	texCoords->at(33) = new Coord2D(G->z, G->y);
	texCoords->at(34) = new Coord2D(F->z, F->y);
	texCoords->at(35) = new Coord2D(B->z, B->y);


	for (unsigned int i = 0; i < vertices->size(); i = i + 6)
	{
		Coord3D * cor1 = vertices->at(i + 1);
		Coord3D * cor2 = vertices->at(i + 2);
		Coord3D * cor3 = vertices->at(i + 3);
		Coord3D * cor4 = vertices->at(i + 4);

		// normals
		Coord3D * vec1 = *cor3 - cor1;
		Coord3D * vec2 = *cor4 - cor2;
		Coord3D * normal = vec1->cross(vec2);

		for (unsigned int j = i; j < i + 6; j++)
		{
			normals->at(j) = normal;
		}

		delete vec1, vec2;
	}
}

Box::~Box()
{

}