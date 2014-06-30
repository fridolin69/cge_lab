#include <stdio.h>
#include <cstdio>
#include <iostream>
#include <fstream>
#include <cmath>
#include <sstream>
#include <time.h>
#include <vector>
#include <algorithm>
#include <numeric>

#include "LightFactory.h"
#include "Plate.h"
#include "Maze.h"
#include "Box.h"
#include "Camera.h"
#include "Renderer.h"
#include "DrawableObjectBase.h"
#include "KeyboardInput.h"
#include "Window.h"
#include "TgaTexture.h"
#include "Color.h"

#include <GL\glut.h>

#define M_PI 3.1415
#define MAX_FPS 60.0f
#define MSEC_DISPLAY_TIMER (1000.0f / MAX_FPS)
#define MSEC_INPUT_TIMER 10

using namespace std;

void display();
void resize(int w, int h);
void keyDown(unsigned char key, int x, int y);
void keyUp(unsigned char key, int x, int y);
void mouseMotion(int x, int y);
void inputTimer(int value);
void displayTimer(int value);
void reportGLError(const char * msg);
bool canMoveTo(float x, float z);
void loadLevel(int index);

Window * window = nullptr;
Maze * maze = nullptr;
long lastRender = 0;
float translationUnit = 0.003;
vector<long> * lastRenderDurations = new vector<long>(5);

int main(int argc, char **argv) 
{
	glutInit(&argc, argv);

	// set up camera
	Camera &camera = Camera::getInstance();
	camera.setRotationSpeed(M_PI / 180 * 0.2);
	camera.setPos(-2, 0.5f, -2);

	// set up window
	window = new Window(1680, 1050, "Lab Display");
	window->create();

	// register glut functions
	glutDisplayFunc(display);
	glutReshapeFunc(resize);
	glutMotionFunc(mouseMotion);
	glutPassiveMotionFunc(mouseMotion);
	glutKeyboardFunc(keyDown);
	glutKeyboardUpFunc(keyUp);
	glutTimerFunc(MSEC_INPUT_TIMER, inputTimer, 0);
	glutTimerFunc(MSEC_DISPLAY_TIMER, displayTimer, 0);

	glutIgnoreKeyRepeat(1);

	loadLevel(2);

	glShadeModel(GL_SMOOTH);

	LightFactory::getInstance().initSpotlight(GL_LIGHT0);

	glTexEnvi(GL_TEXTURE_ENV, GL_TEXTURE_ENV_MODE, GL_MODULATE);

	Color * white = new Color(1, 1, 1);
	Color * superDarkGrey = new Color(0.02f, 0.02f, 0.02f);
	GLfloat * material = white->toArray();

	// TODO test if needed
	glMaterialfv(GL_FRONT, GL_AMBIENT, material);
	glMaterialfv(GL_FRONT, GL_DIFFUSE, material);
	glMaterialfv(GL_FRONT, GL_SPECULAR, material);
	glMaterialfv(GL_FRONT, GL_SHININESS, material);

	glLightModelfv(GL_LIGHT_MODEL_AMBIENT, superDarkGrey->toArray());

	glEnable(GL_TEXTURE_2D);
	glEnable(GL_DEPTH_TEST);
	glEnable(GL_LIGHTING);
	glEnable(GL_COLOR_MATERIAL);

	glutMainLoop();
	return 0;
}

void loadLevel(int index)
{
	Renderer::getInstance().clear();

	if (maze != nullptr)
		delete maze;

	if (index == 0)
	{
		maze = new Maze("data/maze.txt");
	}
	else if (index < 0)
	{
		throw new exception("Index must be greater than 0");
	} else
	{
		string pathPrefix = "data/maze";
		stringstream path;
		path << pathPrefix << index << ".txt";
		maze = new Maze(path.str());
	}

	// load textures
	TgaTexture * boxTga = new TgaTexture("data/box.tga", GL_CLAMP);
	TgaTexture * sandTga = new TgaTexture("data/sand.tga", GL_REPEAT);

	TgaTexture * launchTga = new TgaTexture("data/launch_DIFFUSE.tga", GL_CLAMP);
	TgaTexture * sandstoneTga = new TgaTexture("data/kt_stone_2.tga", GL_CLAMP);

	// generate maze
	maze->walk(

		[boxTga](int x, int y) -> void
	{
		Coord3D * position = new Coord3D(x, 0, y);
		Box * box = new Box(position, 1, boxTga);
		Renderer::getInstance().addDrawableObject(box);
	}
		,
		[sandTga](int x, int y) -> void
	{
		Coord3D * position = new Coord3D(x, 0, y);
		Plate * floor = new Plate(position, 1, 1, sandTga);
		Renderer::getInstance().addDrawableObject(floor);
	}
		,
		[launchTga, sandstoneTga](int x, int y, int level, char field) -> void
	{
		if (field == 'x')
		{
			Coord3D * position = new Coord3D(x, 0, y);
			Box * box = new Box(position, 0.3, 1, sandstoneTga);
			Renderer::getInstance().addDrawableObject(box);
		}
		else if (field == 's')
		{
			Coord3D * position = new Coord3D(x, 0, y);
			Box * box = new Box(position, 0.001, 1, launchTga);
			Renderer::getInstance().addDrawableObject(box);
		}
	}
	);

	// create display list out of all objects
	Renderer::getInstance().createDisplayList();
}

void display() 
{
	Renderer &renderer = Renderer::getInstance();
	Camera &camera = Camera::getInstance();

	camera.refresh();
	renderer.render();
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

	lastRenderDurations->at(index++ % 5) = clock() - lastRender;

	long avgRenderDuration = accumulate(lastRenderDurations->begin(), lastRenderDurations->end(), 0) / 5;

	Camera::getInstance().setTranslationSpeed(translationUnit * avgRenderDuration);

	//cout << "Avg time: " << avgRenderDuration << " ms" << endl;

	lastRender = clock();

	display();

	glutTimerFunc(MSEC_DISPLAY_TIMER, displayTimer, 0);
}

void inputTimer(int value)
{
	KeyboardInput &keyboard = KeyboardInput::getInstance();
	Camera &camera = Camera::getInstance();
	float speed = camera.getTranslationSpeed();

	if (camera.isFPSMode()) 
	{
		if ((keyboard.isDown('w') || keyboard.isDown('s')) && (keyboard.isDown('a') || (keyboard.isDown('d'))))
		{
			speed *= 0.707;
		}

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

	glutTimerFunc(MSEC_INPUT_TIMER, inputTimer, 0);
}

bool canMoveTo(float x, float z)
{
	x = floor(x);
	z = floor(z);
	cout << "Checking access to " << x << " | " << z << endl;
	//TODO
	/*if (maze->at(x, z) == ' ')
	{
		return true;
	}*/
	if (maze->at(x, z) == '#' || maze->at(x, z) == 'x')
	{
		return false;
	}
	return true;
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