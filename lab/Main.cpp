#include <stdio.h>
#include <iostream>
#include <fstream>
#include <cmath>
#include <vector>
#include <GL/glut.h>

#include "Box.h"
#include "Camera.h"
#include "Renderer.h"
#include "DrawableObjectBase.h"
#include "KeyboardInput.h"

#define M_PI 3.1415

using namespace std;

void Display();
void Reshape(int w, int h);
void keyDown(unsigned char key, int x, int y);
void keyUp(unsigned char key, int x, int y);
void MouseMotion(int x, int y);
void Mouse(int button, int state, int x, int y);
void Timer(int value);
void Idle();

void Grid();

void ReadMazeFile();
void PrintMaze();

int g_viewport_width = 0;
int g_viewport_height = 0;

int main(int argc, char **argv) 
{
	glutInit(&argc, argv);
	glutInitDisplayMode(GLUT_DOUBLE | GLUT_DEPTH);
	glutInitWindowSize(640, 480);
	glutCreateWindow("Lab-Display");

	glutIgnoreKeyRepeat(1);

	glutDisplayFunc(Display);
	glutIdleFunc(Display);
	glutReshapeFunc(Reshape);
	glutMotionFunc(MouseMotion);
	glutPassiveMotionFunc(MouseMotion);
	glutKeyboardFunc(keyDown);
	glutKeyboardUpFunc(keyUp);
	glutIdleFunc(Idle);

	Camera::getInstance().setRotationSpeed(M_PI / 180 * 0.2);
	Camera::getInstance().setTranslationSpeed(0.2);

	ReadMazeFile();

	glutTimerFunc(1, Timer, 0);
	glutMainLoop();

	return 0;
}

void ReadMazeFile()
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
				position = new Vertex3D(x, 0, y);
				box = new Box(position, 1);
				box->generate();
				Renderer::getInstance().addDrawableObject(box);
			case ' ':
				x++;
				break;

			case -1:
				continue;
		}
	}

	mazeFile.close();
}

void Grid()
{
	// TODO: build drawable object for this
	glPushMatrix();
	glColor3f(1, 1, 1);

	for (int i = 0; i < 100; i++) {
		glBegin(GL_LINES);
		glVertex3f(i, 0, 0);
		glVertex3f(i, 0, 100);
		glEnd();
	}

	for (int i = 0; i < 100; i++) {
		glBegin(GL_LINES);
		glVertex3f(0, 0, i);
		glVertex3f(100, 0, i);
		glEnd();
	}

	glPopMatrix();
}

void Display(void) {
	glClearColor(0.0, 0.0, 0.0, 1.0); //clear the screen to black
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT); //clear the color buffer and the depth buffer
	glLoadIdentity();

	//Grid();

	Camera::getInstance().refresh();
	Renderer::getInstance().render();

	glutSwapBuffers(); //swap the buffers
}

void Reshape(int w, int h) {
	g_viewport_width = w;
	g_viewport_height = h;

	glViewport(0, 0, (GLsizei)w, (GLsizei)h); //set the viewport to the current window specifications
	glMatrixMode(GL_PROJECTION); //set the matrix to projection

	glLoadIdentity();
	gluPerspective(60, (GLfloat)w / (GLfloat)h, 0.1, 100.0); //set the perspective (angle of sight, width, height, ,depth)
	glMatrixMode(GL_MODELVIEW); //set the matrix back to model
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
				glutWarpPointer(g_viewport_width / 2, g_viewport_height / 2);
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

void Timer(int value)
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

	glutTimerFunc(1, Timer, 0);
}

void Idle()
{
	Display();
}

void MouseMotion(int x, int y)
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
		int dx = x - g_viewport_width / 2;
		int dy = y - g_viewport_height / 2;

		if (dx) 
		{
			camera.rotateYaw(speed * dx);
		}

		if (dy) 
		{
			camera.rotatePitch(speed * dy);
		}

		glutWarpPointer(g_viewport_width / 2, g_viewport_height / 2);

		just_warped = true;
	}
}
