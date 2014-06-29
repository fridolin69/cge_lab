#include "Camera.h"
#include <stdio.h>
#include <math.h>
#include <GL/glut.h>

Camera::Camera()
{
	this->fpsMode = false;
	this->yawAngle = 0.0;
	this->pitchAngle = 0.0;

	this->setPos(0, 0, 0);
}

Camera::~Camera()
{
	
}
void Camera::refresh()
{
	// Camera parameter according to Riegl's co-ordinate system
	// x/y for flat, z for height
	this->xDirectionVec = cos(yawAngle) * cos(pitchAngle);
	this->yDirectionVec = sin(pitchAngle);
	this->zDirectionVec = sin(yawAngle) * cos(pitchAngle);

	// calculate 90 degree vector
	this->xDirectionVecStrafe = cos(yawAngle - M_PI / 2);
	this->zDirectionVecStrafe = sin(yawAngle - M_PI / 2);

	glMatrixMode(GL_MODELVIEW);

	glLoadIdentity();

	GLfloat lightPosition[] = { xPos , yPos, zPos };
	glLightfv(GL_LIGHT0, GL_POSITION, lightPosition);


	gluLookAt(  this->xPos, 
				this->yPos, 
				this->zPos, 
				this->xPos + this->xDirectionVec,
				this->yPos + this->yDirectionVec,
				this->zPos + this->zDirectionVec,
				0.0, 1.0, 0.0);

	//printf("Camera: %f %f %f Direction vector: %f %f %f\n", xPos, yPos, zPos, xDirectionVec, yDirectionVec, zDirectionVec);
}

void Camera::setPos(float x, float y, float z)
{
	this->xPos = x;
	this->yPos = y;
	this->zPos = z;

	this->refresh();
}

void Camera::getPos(float &x, float &y, float &z)
{
	x = xPos;
	y = yPos;
	z = zPos;
}

void Camera::getDirectionVector(float &x, float &y, float &z)
{
	x = xDirectionVec;
	y = yDirectionVec;
	z = zDirectionVec;
}

void Camera::move(float incr, std::function<bool(float, float)> predicate)
{
	float xIncr = incr *  cos(this->yawAngle) * cos(this->pitchAngle);
	float zIncr = incr * sin(this->yawAngle) * cos(this->pitchAngle);

	float oldX = xPos;
	float oldZ = zPos;

	if (predicate(xPos + 5 * xIncr, oldZ))
	{
		xPos += xIncr;
	}
	if (predicate(oldX, zPos + 5 * zIncr))
	{
		zPos += zIncr;
	}
}

void Camera::strafe(float incr, std::function<bool(float, float)> predicate)
{
	float xIncr = incr * this->xDirectionVecStrafe;
	float zIncr = incr * this->zDirectionVecStrafe;

	float oldX = xPos;
	float oldZ = zPos;

	if (predicate(xPos + 5 * xIncr, oldZ))
	{
		xPos += xIncr;
	}
	if (predicate(oldX, zPos + 5 * zIncr))
	{
		zPos += zIncr;
	}
}

void Camera::rotateYaw(float angle)
{
	this->yawAngle += angle;
	this->refresh();
}

void Camera::rotatePitch(float angle)
{
	const float limit = 89.0 * M_PI / 180.0;

	this->pitchAngle -= angle;

	if (this->pitchAngle < -limit)
	{
		this->pitchAngle = -limit;
	}

	if (this->pitchAngle > limit)
	{
		this->pitchAngle = limit;
	}

	this->refresh();
}

void Camera::setYaw(float angle)
{
	this->yawAngle = angle;
	this->refresh();
}

void Camera::setPitch(float angle)
{
	this->pitchAngle = angle;
	this->refresh();
}

float Camera::getRotationSpeed()
{
	return this->rotationSpeed;
}

float Camera::getTranslationSpeed()
{
	return this->translationSpeed;
}

void Camera::setRotationSpeed(float rotationSpeed)
{
	this->rotationSpeed = rotationSpeed;
}

void Camera::setTranslationSpeed(float translationSpeed)
{
	this->translationSpeed = translationSpeed;
}

void Camera::enableFPSMode()
{
	this->fpsMode = true;
}

void Camera::disableFPSMode()
{
	this->fpsMode = false;
}

bool Camera::isFPSMode()
{
	return this->fpsMode;
}