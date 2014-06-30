#include "Window.h"
#include <GL\glut.h>

Window::Window(std::string title)
{
	this->width = 640;
	this->height = 480;
	this->title = title;
}

Window::Window(int width, int height, std::string title)
{
	this->width = width;
	this->height = height;
	this->title = title;
}

Window::~Window()
{
}

void Window::create()
{
	glutInitDisplayMode(GLUT_DOUBLE | GLUT_DEPTH);
	glutInitWindowSize(this->width, this->height);
	this->windowNr = glutCreateWindow(this->title.c_str());
}

void Window::resize(int newWidth, int newHeight)
{
	this->width = newWidth;
	this->height = newHeight;

	glViewport(0, 0, (GLsizei)this->width, (GLsizei)this->height); //set the viewport to the current window specifications
	glMatrixMode(GL_PROJECTION); //set the matrix to projection

	glLoadIdentity();
	gluPerspective(60, (GLfloat)this->width / (GLfloat)this->height, 0.1, 100.0); //set the perspective (angle of sight, width, height, depth)
	glMatrixMode(GL_MODELVIEW); //set the matrix back to model
}

int Window::getHeight()
{
	return this->height;
}

int Window::getWidth()
{
	return this->width;
}

int Window::getWindowNr()
{
	return this->windowNr;
}