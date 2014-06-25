#include <stdio.h>
#include <cstdio>
#include <iostream>
#include <fstream>
#include <cmath>
#include <time.h>
#include <vector>

#include "Plate.h"
#include "Maze.h"
#include "Box.h"
#include "Camera.h"
#include "Renderer.h"
#include "DrawableObjectBase.h"
#include "KeyboardInput.h"
#include "Window.h"
#include "TgaTexture.h"
#include <GL\glut.h>

#define M_PI 3.1415
#define MAX_FPS 60.0f
#define MSEC_DISPLAY_TIMER (1000.0f / MAX_FPS)
#include <algorithm>
#include "Util.h"

using namespace std;

void display();
void resize(int w, int h);
void keyDown(unsigned char key, int x, int y);
void keyUp(unsigned char key, int x, int y);
void mouseMotion(int x, int y);

void processInput(int value);
void displayTimer(int value);

void reportGLError(const char * msg);
bool canMoveTo(float x, float z);



int g_viewport_width = 0;
int g_viewport_height = 0;

Window * window;
Maze * maze;

vector<long> * lastRenderDurations = new vector<long>(5);

int main(int argc, char **argv) 
{
	glutInit(&argc, argv);

	Camera &camera = Camera::getInstance();

	window = new Window(1680, 1050, "Lab Display");
	window->create();

	glutIgnoreKeyRepeat(1);

	glutDisplayFunc(display);
	glutReshapeFunc(resize);

	glutMotionFunc(mouseMotion);
	glutPassiveMotionFunc(mouseMotion);

	glutKeyboardFunc(keyDown);
	glutKeyboardUpFunc(keyUp);

	camera.setRotationSpeed(M_PI / 180 * 0.2);
	camera.setTranslationSpeed(0.1);
	camera.setPos(-2, 0.5f, -2);

	glEnable(GL_TEXTURE_2D);
	glEnable(GL_DEPTH_TEST);

	maze = new Maze("C:\\maze1_small.txt");
	maze->parse();

	TgaTexture * boxTga = new TgaTexture("C:\\box.tga", GL_CLAMP);
	TgaTexture * sandTga = new TgaTexture("C:\\sand.tga", GL_REPEAT);

	maze->walk([boxTga](int x, int y) -> void { 
		Vertex3D * position = new Vertex3D(x, 0, y);
		Box * box = new Box(position, 1, boxTga);
		box->generate();
		Renderer::getInstance().addDrawableObject(box);
	},
		nullptr);

	Plate * floor = new Plate(new Vertex3D(-1, 0, -1), maze->getWidth() + 2, sandTga);
	floor->generate();
	Renderer::getInstance().addDrawableObject(floor);

	glutTimerFunc(10, processInput, 0);
	glutTimerFunc(MSEC_DISPLAY_TIMER, displayTimer, 0);

	glutMainLoop();

	return 0;
}

void display() 
{
	Renderer &renderer = Renderer::getInstance();
	Camera &camera = Camera::getInstance();

	renderer.preRender();
	camera.refresh();
	renderer.render();

	renderer.postRender();
}

void resize(int width, int height) {
	window->resize(width, height);
}

void keyDown(unsigned char key, int x, int y)
{
	KeyboardInput &keyboard = KeyboardInput::getInstance();
	Camera &camera = Camera::getInstance();

	if (key == ' ') 
	{
		switch (camera.isFPSMode())
		{
			case true:
				glutSetCursor(GLUT_CURSOR_LEFT_ARROW);
				camera.disableFPSMode();
				break;

			case false:
				glutSetCursor(GLUT_CURSOR_NONE);
				glutWarpPointer(window->getWidth() / 2, window->getHeight() / 2);
				camera.enableFPSMode();
				break;
		}
	}

	keyboard.keyDown(key);
}

void keyUp(unsigned char key, int x, int y)
{
	KeyboardInput::getInstance().keyUp(key);
}

void displayTimer(int value)
{
	static int index = 0;

	cout << "Avg time: " << Util::avg(lastRenderDurations) << " ms" << endl;

	long beforeDisplay = clock();

	display();

	lastRenderDurations->at(index++ % 5) = clock() - beforeDisplay;

	glutTimerFunc(MSEC_DISPLAY_TIMER, displayTimer, 0);
}

void processInput(int value)
{
	KeyboardInput &keyboard = KeyboardInput::getInstance();
	Camera &camera = Camera::getInstance();
	float speed = camera.getTranslationSpeed();

	if (camera.isFPSMode()) 
	{
		if (keyboard.isDown('w')) 
		{
			camera.move(speed, canMoveTo);
		}

		if (keyboard.isDown('s')) 
		{
			camera.move(-speed, canMoveTo);
		}

		if (keyboard.isDown('a')) 
		{
			camera.strafe(speed, canMoveTo);
		}

		if (keyboard.isDown('d')) 
		{
			camera.strafe(-speed, canMoveTo);
		}
	}

	glutTimerFunc(10, processInput, 0);
}

bool canMoveTo(float x, float z)
{
	return maze->at(x, z) == ' ';
}

void mouseMotion(int x, int y)
{
	Camera &camera = Camera::getInstance();
	float speed = camera.getRotationSpeed();

	// This variable is hack to stop glutWarpPointer from triggering an event callback to Mouse(...)
	// This avoids it being called recursively and hanging up the event loop
	static bool just_warped = false;

	if (just_warped)
	{
		just_warped = false;
		return;
	}

	if (camera.isFPSMode())
	{
		int deltaX = x - window->getWidth() / 2;
		int deltaY = y - window->getHeight() / 2;

		if (deltaX != 0) 
		{
			camera.rotateYaw(speed * deltaX);
		}

		if (deltaY != 0) 
		{
			camera.rotatePitch(speed * deltaY);
		}

		glutWarpPointer(window->getWidth() / 2, window->getHeight() / 2);

		just_warped = true;
	}
}

void reportGLError(const char * msg)
{
	GLenum errCode;
	const GLubyte *errString;
	while ((errCode = glGetError()) != GL_NO_ERROR) {
		errString = gluErrorString(errCode);
		fprintf(stdout, "OpenGL Error: %s %s\n", msg, errString);
	}
}