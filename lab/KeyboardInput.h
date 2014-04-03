#ifndef _KEYBOARD_INPUT_H
#define _KEYBOARD_INPUT_H

// singleton class that handles keyboard input
class KeyboardInput
{
private:
	bool keysDown[256];

private:
	KeyboardInput();
	~KeyboardInput();
	KeyboardInput(KeyboardInput const&);

private:
	void operator=(KeyboardInput const&);

public:
	static KeyboardInput & getInstance()
	{
		static KeyboardInput instance;
		return instance;
	}

	void keyDown(unsigned char key);
	void keyUp(unsigned char key);

	bool isDown(unsigned char key);
};

#endif