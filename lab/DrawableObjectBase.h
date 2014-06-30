#ifndef _DRAWABLE_OBJECT_H_
#define _DRAWABLE_OBJECT_H_

#include <vector>
#include "Coord2D.h"
#include "Coord3D.h"
#include "TgaTexture.h"

// base class for any drawable object
class DrawableObjectBase
{
protected:
	int vertexCount;
	int iterations;
	GLenum type;					// defines the type of geometry object the vertices should build, will be passed directly to glBegin()

	std::vector<Coord3D*> * vertices;
	std::vector<Coord3D*> * normals;
	std::vector<Coord2D*> * texCoords;

	Coord3D * position;
	TgaTexture * texture;

public:

	DrawableObjectBase(Coord3D* position, TgaTexture* texture);
	virtual ~DrawableObjectBase();

	virtual void generate() = 0;	// create the internal array returned at getVertices()


	std::vector<Coord3D*> * getVertices();		// returns the array of vertices
	std::vector<Coord3D*> * getNormals();

	TgaTexture * getTexture();
	std::vector<Coord2D*> * getTexCoords();

	int getIterations();

	GLenum getObjectType();			// returns the GLenum of the object
	Coord3D * getPosition();		// returns the translation vector
};

#endif