#include "Renderer.h"

Renderer::Renderer()
{

}

Renderer::~Renderer()
{

}

void Renderer::addDrawableObject(DrawableObjectBase * object)
{
	this->objects.push_back(object);
}

void Renderer::render()
{
	for each (DrawableObjectBase * object in this->objects)
	{
		glPushMatrix();
			glTranslatef(object->getPosition()->getX(), object->getPosition()->getY(), object->getPosition()->getZ()); // translate to object position

			glColor4f(object->getColor()->getRed(), object->getColor()->getGreen(), object->getColor()->getBlue(), object->getColor()->getAlpha());

			glBegin(object->getObjectType()); // request object type

				Vertex3D ** vertices = object->getVertices(); // request vertex-Array

				if (vertices == NULL)
				{
					continue;
				}

				// draw every vertex of the object
				for (int i = 0; i < object->getVertexCount(); i++)
				{
					if (vertices[i] == NULL) // prevent objects from crashing the render engine
					{
						continue;
					}
					glVertex3f(vertices[i]->getX(), vertices[i]->getY(), vertices[i]->getZ());
				}

			glEnd();
		glPopMatrix();
	}
}

void Renderer::preRender()
{
	glClearColor(0.0, 0.0, 0.0, 1.0); //clear the screen to black
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT); //clear the color buffer and the depth buffer
	glEnable(GL_DEPTH_TEST);
	glLoadIdentity();
}

void Renderer::postRender()
{
	glutSwapBuffers();
}