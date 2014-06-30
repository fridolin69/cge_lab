#include <iostream>
#include "Plate.h"

Plate::Plate(Coord3D* position, GLfloat zWidth, GLfloat size, TgaTexture* texture)
	: DrawableObjectBase(position, texture), size(size)
{
	this->vertexCount = 6;
	this->iterations = 1;
	this->type = GL_TRIANGLE_FAN;
	this->zWidth = zWidth;
}

Plate::~Plate()
{
	delete this->A;
	delete this->B;
	delete this->C;
	delete this->D;

	delete this->position;
	delete this->texCoords;
	delete this->vertices;
	delete this->normals;
}

void Plate::generate()
{
	this->A = new Coord3D( 0,    0,   zWidth);
	this->B = new Coord3D( size, 0,   zWidth);
	this->C = new Coord3D( size, 0,   0);
	this->D = new Coord3D( 0,    0,   0);

	Coord3D * middleABCD = new Coord3D(size / 2, 0 , zWidth / 2);

	texCoords = new std::vector<Coord2D*>(vertexCount);
	vertices = new std::vector<Coord3D*>(vertexCount);
	normals = new std::vector<Coord3D*>(vertexCount);

	vertices->at(0) = middleABCD;
	vertices->at(1) = A;
	vertices->at(2) = B;
	vertices->at(3) = C;
	vertices->at(4) = D;
	vertices->at(5) = A;

	texCoords->at(0) = new Coord2D(middleABCD->x, middleABCD->z);
	texCoords->at(1) = new Coord2D(A->x, A->z);
	texCoords->at(2) = new Coord2D(B->x, B->z);
	texCoords->at(3) = new Coord2D(C->x, C->z);
	texCoords->at(4) = new Coord2D(D->x, D->z);
	texCoords->at(5) = new Coord2D(A->x, A->z);

	Coord3D * vecAC = *C - A;
	Coord3D * vecBD = *D - B;
	Coord3D * normal = vecAC->cross(vecBD);

	for (int j = 0; j < 6; j++)
	{
		normals->at(j) = normal;
	}
	
	delete vecAC, vecBD;
}