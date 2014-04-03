#include "KeyboardInput.h"

KeyboardInput::KeyboardInput()
{
	
}

KeyboardInput::~KeyboardInput()
{

}

void KeyboardInput::keyDown(unsigned char key)
{
	this->keysDown[key] = true;
}

void KeyboardInput::keyUp(unsigned char key)
{
	this->keysDown[key] = false;
}

bool KeyboardInput::isDown(unsigned char key)
{
	return this->keysDown[key];
}