#pragma once
#include <vector>
#include <functional>

using namespace std;

class Maze
{
private:
	string path;
	vector<vector<char> *> * maze;

	int width;
	int height;

	bool parsed;

public:
	Maze(string path);

	void parse();
	char at(int x, int y);

	void walk(function<void(int, int)> boxCallback, function<void(int, int)> pathCallback, function<void(int, int, int, char)> launchCallback);

	int getWidth();
	int getHeight();

	virtual ~Maze();
};

