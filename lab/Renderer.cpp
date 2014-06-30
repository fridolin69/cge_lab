#include <algorithm>
#include "Renderer.h"

Renderer::Renderer()
{
	objects = new std::vector<DrawableObjectBase*>();
	displayLists = new std::vector<GLuint>();
}

void ::Renderer::createDisplayList()
{
	GLuint index = glGenLists(1);

	glNewList(index, GL_COMPILE);

		for_each(objects->begin(), objects->end(), [](DrawableObjectBase * drawable) -> void {
			glPushMatrix();
				glTranslatef(drawable->getPosition()->x, drawable->getPosition()->y, drawable->getPosition()->z); // translate to object position

				glBindTexture(GL_TEXTURE_2D, drawable->getTexture()->getTextureId());
				glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, drawable->getTexture()->getWrapMode());
				glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, drawable->getTexture()->getWrapMode());

				std::vector<Coord3D* > * vertices = drawable->getVertices();
				std::vector<Coord3D* > * normals = drawable->getNormals();
				std::vector<Coord2D* > * texCoords = drawable->getTexCoords();

				int iterationSize = vertices->size() / drawable->getIterations();

				for (int j = 0; j < drawable->getIterations(); j++)
				{
					glBegin(drawable->getObjectType()); // request object type

					for (int i = j * iterationSize; i < (j + 1) * iterationSize; i++)
					{
						glTexCoord2fv(texCoords->at(i)->toArray());
						glNormal3fv(normals->at(i)->toArray());
						glVertex3fv(vertices->at(i)->toArray());
					}

					glEnd();
				}

			glPopMatrix();

			delete drawable;
		});

	glEndList();

	objects->clear();
	displayLists->push_back(index);
}

Renderer::~Renderer()
{
	
}

void Renderer::addDrawableObject(DrawableObjectBase * object)
{
	// lazy initialize object
	if (object->getVertices() == nullptr)
	{
		object->generate();
	}
	objects->push_back(object);
}

void Renderer::render()
{
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

	for_each(displayLists->begin(), displayLists->end(), [](GLuint list) -> void {
		glCallList(list);
	});

	glutSwapBuffers();
}

void Renderer::clear()
{
	for_each(displayLists->begin(), displayLists->end(), [](GLuint list) -> void {
		glDeleteLists(list, 1);
	});
}