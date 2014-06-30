#include "Maze.h"
#include <fstream>
#include <algorithm>



using namespace std;

Maze::Maze(string path) : path(path)
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

void Maze::walk(function<void(int, int)> boxCallback, function<void(int, int)> pathCallback, function<void(int, int, int, char)> launchCallback, function<void(int, int, char)> inOutCallback)
{
	int levelnumber = 1;
	int sCounter = 0;
	for (int y = 0; y < height; y++)

	{
	for (int x = 0; x < width; x++)
	{
			
			//#####
			//# E #
			//#sss#
			//#sxs#
			//#sss#
			//#   #
			//#   #
			//# A #
			//#####
			if (maze->at(y)->at(x) == 's' && launchCallback != nullptr)
			{
				++sCounter;
				if (sCounter == 9)
				{
					sCounter = 0;
					++levelnumber;
			}
				launchCallback(x, y, levelnumber, 's');
			}
			else if (maze->at(y)->at(x) == 'x' && launchCallback != nullptr)
			{
				launchCallback(x, y, levelnumber, 'x');
			}

			else if (maze->at(y)->at(x) == '#' && boxCallback != nullptr)
			{
				boxCallback(x, y);
			}

			else if (maze->at(y)->at(x) == ' ' && pathCallback != nullptr)
			{

				pathCallback(x, y);
			}

			else if (maze->at(y)->at(x) == 'E' && inOutCallback != nullptr)
			{
				inOutCallback(x, y, 'E');
			}

			else if (maze->at(y)->at(x) == 'A' && inOutCallback != nullptr)
			{
				inOutCallback(x, y, 'A');
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
		char buf = char(mazeFile.get());
		switch (buf)
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
		case ' ':
		case 's':
		case 'x':
		case 'E':
		case 'A':
			x++;
			maze->at(y)->push_back(buf);
			break;

		case -1:
			continue;
		}
		this->parsed = true;
	}

	maze->resize(maze->size() - 1);

	width = linelength;
	height = y;

	mazeFile.close();

	this->parsed = true;
}

Maze::~Maze()
{
	if (maze != nullptr)
		delete maze;
}
