#include "Maze.h"
#include <fstream>
#include <algorithm>

using namespace std;

Maze::Maze(char* path) : path(path)
{
	parsed = false;
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

void Maze::walk(function<void(int, int)> callback1, function<void(int, int)> callback2)
{
	for (int x = 0; x < width; ++x)
	{
		for (int y = 0; y < height; ++y)
		{
			if (maze->at(y)->at(x) == '#' && callback1 != nullptr)
			{
				callback1(x, y);
			}

			if (maze->at(y)->at(x) == ' ' && callback2 != nullptr)
			{
				callback2(x, y);
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

		case -1:
			continue;
		}
	}

	maze->resize(maze->size() - 1);

	width = linelength;
	height = y;

	mazeFile.close();
}

Maze::~Maze()
{
	if (maze != nullptr)
		delete maze;
}
