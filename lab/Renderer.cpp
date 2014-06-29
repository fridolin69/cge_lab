#include "Renderer.h"
#include <algorithm>

Renderer::Renderer()
{
	objects = new std::vector<DrawableObjectBase*>();
	displayLists = new std::vector<GLuint>();
}

void ::Renderer::createDisplayList()
{
	GLuint index = glGenLists(1);

	glNewList(index, GL_COMPILE);

		for_each(objects->begin(), objects->end(), [](DrawableObjectBase * object) -> void {
			glPushMatrix();
				glTranslatef(object->getPosition()->getX(), object->getPosition()->getY(), object->getPosition()->getZ()); // translate to object position

				glBindTexture(GL_TEXTURE_2D, object->getTexture()->getTextureId());
				glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, object->getTexture()->getWrapMode());
				glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, object->getTexture()->getWrapMode());

				glBegin(object->getObjectType()); // request object type

					Vertex3D ** vertices = object->getVertices();
					Vertex3D ** normals = object->getNormals();
					TexCoords ** texCoords = object->getTexCoords();

					if (vertices == nullptr)
					{
						return;
					}

					// draw every vertex of the object
					for (int i = 0; i < object->getVertexCount(); i++)
					{
						if (vertices[i] == nullptr) // prevent objects from crashing the render engine
						{
							continue;
						}

						glTexCoord2f(texCoords[i]->getX(), texCoords[i]->getY());
						glNormal3f(normals[i]->getX(), normals[i]->getY(), normals[i]->getZ());
						glVertex3f(vertices[i]->getX(), vertices[i]->getY(), vertices[i]->getZ());
					}

				glEnd();

			glPopMatrix();
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