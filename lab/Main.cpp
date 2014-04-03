#include <stdio.h>
#include <iostream>
#include <fstream>
#include <cmath>
#include <vector>
#include <GL/glut.h>

#include "Box.h"
#include "HorizontalSquarePlate.h"
#include "Camera.h"
#include "Renderer.h"
#include "DrawableObjectBase.h"
#include "KeyboardInput.h"
#include "Window.h"

#define M_PI 3.1415

using namespace std;

void display();
void resize(int w, int h);
void keyDown(unsigned char key, int x, int y);
void keyUp(unsigned char key, int x, int y);
void mouseMotion(int x, int y);
void timer(int value);
void idle();

void readMazeFile();
void printMaze();

int g_viewport_width = 0;
int g_viewport_height = 0;

Window * window;

int main(int argc, char **argv) 
{
	glutInit(&argc, argv);

	Camera &camera = Camera::getInstance();

	window = new Window(1680, 1050, "Lab Display");
	window->create();

	glutIgnoreKeyRepeat(1);

	glutDisplayFunc(display);
	glutIdleFunc(display);

	glutReshapeFunc(resize);

	glutMotionFunc(mouseMotion);
	glutPassiveMotionFunc(mouseMotion);

	glutKeyboardFunc(keyDown);
	glutKeyboardUpFunc(keyUp);

	glutIdleFunc(idle);

	camera.setRotationSpeed(M_PI / 180 * 0.2);
	camera.setTranslationSpeed(0.2);
	camera.setPos(-25, 0.5, 25);

	readMazeFile();

	glutTimerFunc(1, timer, 0);
	glutMainLoop();

	return 0;
}

void readMazeFile()
{
	fstream mazeFile;

	mazeFile.open("D:\\maze2_unicursal.txt", fstream::in);

	if (!mazeFile.is_open())
	{
		cerr << "Failed to open labyrinth-file!" << endl;
		return;
	}

	int x = 0, y = 0, linelength = 0;
	Vertex3D * position;
	Box * box;
	HorizontalSquarePlate * plate;
	Color * boxColor = new Color(1, 1, 1);
	Color * floorColor = new Color(0.7, 0, 0);

	while (mazeFile.good())
	{
		switch (char(mazeFile.get()))
		{
			// EOL -> define linelength and increase linenumber (y)
			case '\n':
			case '\r':
				// do not increase linenumber for empty lines
				if (x != 0)
				{
					linelength = x;
					y++;
					x = 0;
				}
				break;

				// on # or ' ' fall through and add char to vector
			case '#':
				x++;
				position = new Vertex3D(x, 0, y);
				box = new Box(position, 1, boxColor);
				box->generate();
				Renderer::getInstance().addDrawableObject(box);
				break;

			case ' ':
				x++;
				break;

			case -1:
				continue;
		}
	}

	mazeFile.close();

	for (int i = -10; i < linelength + 10; i++)
	{
		for (int j = -10; j < y + 10; j++)
		{
			position = new Vertex3D(i, 0, j);
			plate = new HorizontalSquarePlate(position, 1, floorColor);
			plate->generate();
			Renderer::getInstance().addDrawableObject(plate);
		}
	}
}

void display() 
{
	Renderer &renderer = Renderer::getInstance();

	renderer.preRender();
	Camera::getInstance().refresh();
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

void timer(int value)
{
	KeyboardInput &keyboard = KeyboardInput::getInstance();
	Camera &camera = Camera::getInstance();
	float speed = camera.getTranslationSpeed();

	if (camera.isFPSMode()) 
	{
		if (keyboard.isDown('w')) 
		{
			camera.move(speed);
		}

		if (keyboard.isDown('s')) 
		{
			camera.move(-speed);
		}

		if (keyboard.isDown('a')) 
		{
			camera.strafe(speed);
		}

		if (keyboard.isDown('d')) 
		{
			camera.strafe(-speed);
		}
	}

	glutTimerFunc(10, timer, 0);
}

void idle()
{
	display();
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
