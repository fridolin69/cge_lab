#ifndef _WINDOW_H_
#define _WINDOW_H

#include <string>

class Window
{
private:
	int width;
	int height;
	std::string title;

public:
	Window(std::string title);
	Window(int width, int height, std::string title);
	~Window();

	void create();
	void resize(int newWidth, int newHeight);

	int getWidth();
	int getHeight();
};

#endif