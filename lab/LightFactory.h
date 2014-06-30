#pragma once

#include "Coord3D.h"
#include <GL/glut.h>

class LightFactory
{
private:
	LightFactory();
	~LightFactory();
	LightFactory(LightFactory const&);

private:
	void operator=(LightFactory const&);

public:
	static LightFactory & getInstance()
	{
		static LightFactory instance;
		return instance;
	}

	void enable(GLuint lightIndex);
	void disable(GLuint lightIndex);
	void initSpotlight(GLuint lightIndex);
	void setPosition(GLuint lightIndex, Coord3D * position);
	void setDirection(GLuint lightIndex, Coord3D * direction);
	void setAttenuation(GLuint lightIndex, GLfloat constant, GLfloat linear, GLfloat quadratic);
};

