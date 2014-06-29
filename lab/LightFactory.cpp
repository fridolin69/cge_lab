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

	glLightf(lightIndex, GL_SPECULAR, 0.8f);
	glLightf(lightIndex, GL_DIFFUSE, 0.1f);
	glLightf(lightIndex, GL_AMBIENT, 0.0f);

	//glLightf(lightIndex, GL_SPOT_CUTOFF, 20); // angle is 0 to 180
	glLightf(lightIndex, GL_SPOT_EXPONENT, 80); // exponent is 0 to 128

	this->setAttenuation(lightIndex, 1, 0, 3);
}

void LightFactory::setPosition(GLuint lightIndex, Vertex3D* position)
{
	GLfloat lightPosition[] = { position->getX(), position->getY(), position->getZ(), 1.0f };
	glLightfv(lightIndex, GL_POSITION, lightPosition);
}

void LightFactory::setDirection(GLuint lightIndex, Vertex3D* direction)
{
	GLfloat lightDirection[] = { direction->getX(), direction->getY(), direction->getZ() };
	glLightfv(lightIndex, GL_SPOT_DIRECTION, lightDirection);
}

void LightFactory::setAttenuation(GLuint lightIndex, GLfloat constant, GLfloat linear, GLfloat quadratic)
{
	glLightf(lightIndex, GL_CONSTANT_ATTENUATION, constant);
	glLightf(lightIndex, GL_LINEAR_ATTENUATION, linear);
	glLightf(lightIndex, GL_QUADRATIC_ATTENUATION, quadratic);
}