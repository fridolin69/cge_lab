#ifndef _RENDERER_H_
#define _RENDERER_H_

#include <vector>
#include "DrawableObjectBase.h"

// singleton class that handles rendering
// info: because glut does not allow a class method as glutDisplayFunc() we need a proxy function that just calls the render method from this singleton class
class Renderer
{
private:
	std::vector<GLuint> * displayLists;
	std::vector<DrawableObjectBase *> * objects;

private:
	Renderer();
	~Renderer();
	Renderer(Renderer const&);

private:
	void operator=(Renderer const&);

public:
	static Renderer & getInstance()
	{
		static Renderer instance;
		return instance;
	}

	void createDisplayList(); // create new display list, draw all items, close display list and add to vector
	void preRender();
	void postRender();
	void render(); // call all display lists

	void addDrawableObject(DrawableObjectBase * object);
};

#endif