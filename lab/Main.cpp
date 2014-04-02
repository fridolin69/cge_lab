/*
FPS control demo in GLUT by Nghia Ho

SPACEBAR - toggle FPS control
W,A,S,D - to move
mouse - look around, inverted mouse
left/right mouse - fly up/down
ESC - quit

*/

#include <stdio.h>
#include <iostream>
#include <fstream>
#include <cmath>
#include <vector>
#include <GL/glut.h>

#include "Camera.h"

#define M_PI 3.1415

using namespace std;

void Display();
void Reshape(int w, int h);
void Keyboard(unsigned char key, int x, int y);
void KeyboardUp(unsigned char key, int x, int y);
void MouseMotion(int x, int y);
void Mouse(int button, int state, int x, int y);
void Timer(int value);
void Idle();

void Grid();

void ReadMazeFile();
void PrintMaze();

Camera g_camera;
bool g_key[256];
bool g_shift_down = false;
bool g_fps_mode = false;
int g_viewport_width = 0;
int g_viewport_height = 0;
bool g_mouse_left_down = false;
bool g_mouse_right_down = false;

// Movement settings
const float g_translation_speed = 0.05;
const float g_rotation_speed = M_PI / 180 * 0.2;

int lab[100][100] = { { 0, 0 } };

int main(int argc, char **argv) {
	glutInit(&argc, argv);
	glutInitDisplayMode(GLUT_DOUBLE | GLUT_DEPTH);
	glutInitWindowSize(640, 480);
	glutCreateWindow("FPS demo by Nghia Ho - Hit SPACEBAR to toggle FPS mode");

	glutIgnoreKeyRepeat(1);

	glutDisplayFunc(Display);
	glutIdleFunc(Display);
	glutReshapeFunc(Reshape);
	glutMouseFunc(Mouse);
	glutMotionFunc(MouseMotion);
	glutPassiveMotionFunc(MouseMotion);
	glutKeyboardFunc(Keyboard);
	glutKeyboardUpFunc(KeyboardUp);
	glutIdleFunc(Idle);

	ReadMazeFile();

	glutTimerFunc(1, Timer, 0);
	glutMainLoop();

	return 0;
}

void DrawBox(float x, float y, float size)
{
	glPushMatrix();

		glTranslatef(x, 0, y);
		glColor3f(0, 1, 0);

		glBegin(GL_QUADS);

			// bottom

			glVertex3f(0, 0, 0);
			glVertex3f(0, 0, size);
			glVertex3f(size, 0, size);
			glVertex3f(size, 0, 0);

			// top

			glVertex3f(0, size, 0);
			glVertex3f(0, size, size);
			glVertex3f(size, size, size);
			glVertex3f(size, size, 0);

			// front

			glVertex3f(0, 0, size);
			glVertex3f(0, size, size);
			glVertex3f(size, size, size);
			glVertex3f(size, 0, size);

			// back

			glVertex3f(0, 0, 0);
			glVertex3f(0, size, 0);
			glVertex3f(size, size, 0);
			glVertex3f(size, 0, 0);

			// left

			glVertex3f(0, 0, 0);
			glVertex3f(0, 0, size);
			glVertex3f(0, size, size);
			glVertex3f(0, size, 0);

			// right

			glVertex3f(size, 0, 0);
			glVertex3f(size, 0, size);
			glVertex3f(size, size, size);
			glVertex3f(size, size, 0);

		glEnd();

	glPopMatrix();
}

void ReadMazeFile()
{
	fstream mazeFile;

	mazeFile.open("maze\\maze2_unicursal.txt", fstream::in);

	if (!mazeFile.is_open())
	{
		cerr << "Failed to open labyrinth-file!" << endl;
		return;
	}

	char readchar;

	int x = 0, y = 0, linelength = 0;

	while (mazeFile.good())
	{
		readchar = char(mazeFile.get());
		switch (readchar)
		{
			// EOL -> define linelength and increase linenumber (y)
		case '\n':
		case '\r':
			// do not increase linenumber for empty lines
			if (x != 0)
			{
				if (linelength != 0 && linelength != x)
				{

				}
				else
				{
					linelength = x;
					y++;
					x = 0;
				}
			}
			printf("\n");
			break;

			// on # or ' ' fall through and add char to vector
		case '#':
			lab[x][y] = 1;
			x++;
			break;

		case ' ':
			lab[x][y] = 0;
			x++;
			break;

		case -1:
			continue;
		}
	}

	mazeFile.close();
}

void PrintMaze()
{
	for (int y = 0; y < 100; y++)
	{
		for (int x = 0; x < 100; x++)
		{
			if (lab[x][y] == 1)
			{
				DrawBox(x, y, 1);
			}
		}
	}
}

void Grid()
{
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

	g_camera.Refresh();

	PrintMaze();

	Grid();

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

void Keyboard(unsigned char key, int x, int y)
{
	if (key == 27) {
		//exit(0);
	}

	if (key == ' ') {
		g_fps_mode = !g_fps_mode;

		if (g_fps_mode) {
			glutSetCursor(GLUT_CURSOR_NONE);
			glutWarpPointer(g_viewport_width / 2, g_viewport_height / 2);
		}
		else {
			glutSetCursor(GLUT_CURSOR_LEFT_ARROW);
		}
	}

	if (glutGetModifiers() == GLUT_ACTIVE_SHIFT) {
		g_shift_down = true;
	}
	else {
		g_shift_down = false;
	}

	g_key[key] = true;
}

void KeyboardUp(unsigned char key, int x, int y)
{
	g_key[key] = false;
}

void Timer(int value)
{
	if (g_fps_mode) {
		if (g_key['w'] || g_key['W']) {
			g_camera.Move(g_translation_speed);
		}

		if (g_key['s'] || g_key['S']) {
			g_camera.Move(-g_translation_speed);
		}

		if (g_key['a'] || g_key['A']) {
			g_camera.Strafe(g_translation_speed);
		}

		if (g_key['d'] || g_key['D']) {
			g_camera.Strafe(-g_translation_speed);
		}

		if (g_mouse_left_down) {
			g_camera.Fly(-g_translation_speed);
		}
		
		if (g_mouse_right_down) {
			g_camera.Fly(g_translation_speed);
		}
	}

	glutTimerFunc(1, Timer, 0);
}

void Idle()
{
	Display();
}

void Mouse(int button, int state, int x, int y)
{
	if (state == GLUT_DOWN) {
		if (button == GLUT_LEFT_BUTTON) {
			g_mouse_left_down = true;
		}
		else if (button == GLUT_RIGHT_BUTTON) {
			g_mouse_right_down = true;
		}
	}
	else if (state == GLUT_UP) {
		if (button == GLUT_LEFT_BUTTON) {
			g_mouse_left_down = false;
		}
		else if (button == GLUT_RIGHT_BUTTON) {
			g_mouse_right_down = false;
		}
	}
}

void MouseMotion(int x, int y)
{
	// This variable is hack to stop glutWarpPointer from triggering an event callback to Mouse(...)
	// This avoids it being called recursively and hanging up the event loop
	static bool just_warped = false;

	if (just_warped) {
		just_warped = false;
		return;
	}

	if (g_fps_mode) {
		int dx = x - g_viewport_width / 2;
		int dy = y - g_viewport_height / 2;

		if (dx) {
			g_camera.RotateYaw(g_rotation_speed*dx);
		}

		if (dy) {
			g_camera.RotatePitch(g_rotation_speed*dy);
		}

		glutWarpPointer(g_viewport_width / 2, g_viewport_height / 2);

		just_warped = true;
	}
}
