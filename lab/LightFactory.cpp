#include <iostream>
#include "LightFactory.h"
#include "Color.h"


LightFactory::LightFactory()
{
}


LightFactory::~LightFactory()
{
}

void LightFactory::enable(GLuint lightIndex)
{
	glEnable(lightIndex);
}

void LightFactory::disable(GLuint lightIndex)
{
	glDisable(lightIndex);
}

void LightFactory::initSpotlight(GLuint lightIndex)
{
	// basic setup of a spotlight

	this->enable(lightIndex);

	glLightf(lightIndex, GL_SPECULAR, 0.1f);
	glLightf(lightIndex, GL_DIFFUSE, 0.0f);
	glLightf(lightIndex, GL_AMBIENT, 0.0f);

	glLightf(lightIndex, GL_SPOT_CUTOFF, 15); // angle is 0 to 180
	glLightf(lightIndex, GL_SPOT_EXPONENT, 128); // exponent is 0 to 128

	this->setAttenuation(lightIndex, 0, 0, 0.1f);
}

void LightFactory::setPosition(GLuint lightIndex, Coord3D* position)
{
	GLfloat * lightPosition = position->toArray();
	lightPosition[3] = 1.0f;

	glLightfv(lightIndex, GL_POSITION, lightPosition);
}

void LightFactory::setDirection(GLuint lightIndex, Coord3D* direction)
{
	GLfloat * lightDirection = direction->toArray();
	glLightfv(lightIndex, GL_SPOT_DIRECTION, lightDirection);
}

void LightFactory::setAttenuation(GLuint lightIndex, GLfloat constant, GLfloat linear, GLfloat quadratic)
{
	glLightf(lightIndex, GL_CONSTANT_ATTENUATION, constant);
	glLightf(lightIndex, GL_LINEAR_ATTENUATION, linear);
	glLightf(lightIndex, GL_QUADRATIC_ATTENUATION, quadratic);
}