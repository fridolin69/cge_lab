#include "Maze.h"
#include <fstream>
#include <algorithm>

using namespace std;

Maze::Maze(string path) : path(path)
{
	parsed = false;
}

Maze::~Maze()
{
	if (maze != nullptr)
		delete maze;
}

char Maze::at(int x, int y)
{
	if (!parsed)
	{
		this->parse();
	}

	if (x >= width || x < 0 || y >= height || y < 0)
	{
		return ' ';
	}

	return maze->at(y)->at(x);
}

void Maze::walk(function<void(int, int)> boxCallback, function<void(int, int)> pathCallback, function<void(int, int, int,char)> launchCallback)
{
	if (!parsed)
	{
		this->parse();
	}

	int levelnumber = 0;

	for (int x = 0; x < width; x++)
	{
		for (int y = 0; y < height; y++)
		{
			
			//#   # # # for the menu
			//#       #
			//#       #
			//# s s s #
			//# s x s #
			//# s s s #
			//#       #
			//#       #

			if (maze->at(y)->at(x) == 's' && launchCallback != nullptr)
			{
				launchCallback(x, y, -1, 's');
			}

			else if (maze->at(y)->at(x) == 'x' && launchCallback != nullptr) //found new level entry
			{
				launchCallback(x, y, ++levelnumber,'x');
			}

			else if (maze->at(y)->at(x) == '#' && boxCallback != nullptr)
			{
				boxCallback(x, y);
			}

			else if (maze->at(y)->at(x) == ' ' && pathCallback != nullptr)
			{
				pathCallback(x, y);
			}
		}
	}
}

int Maze::getHeight()
{
	return this->height;
}

int Maze::getWidth()
{
	return this->width;
}

void Maze::parse()
{
	fstream mazeFile;

	mazeFile.open(path, fstream::in);

	if (!mazeFile.is_open())
	{
		throw new exception("Cannot open maze-file!");
	}

	maze = new vector< vector<char> *>();

	int x = 0;
	int y = 0;
	int linelength = 0;

	maze->push_back(new vector < char >());

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
				maze->push_back(new vector < char >());
				x = 0;
			}
			break;

		case '#':
			x++;
			maze->at(y)->push_back('#');
			break;

		case ' ':
			x++;
			maze->at(y)->push_back(' ');
			break;

		case 's':
			x++;
			maze->at(y)->push_back('s');
			break;

		case 'x':
			x++;
			maze->at(y)->push_back('x');
			break;

		case 'f':
			x++;
			maze->at(y)->push_back('f');
			break;

		case -1:
			continue;
		}
		this ->parsed = true;
	}

	maze->resize(maze->size() - 1);

	width = linelength;
	height = y;

	mazeFile.close();

	this->parsed = true;
}
