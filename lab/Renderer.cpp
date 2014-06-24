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
		//glLoadIdentity();
		glPushMatrix();
			glTranslatef(object->getPosition()->getX(), object->getPosition()->getY(), object->getPosition()->getZ()); // translate to object position

			glTexEnvf(GL_TEXTURE_ENV, GL_TEXTURE_ENV_MODE, GL_DECAL);

			glBindTexture(GL_TEXTURE_2D, object->getTexture()->getTextureId());
			glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, object->getTexture()->getWrapMode());
			glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, object->getTexture()->getWrapMode());

			glBegin(object->getObjectType()); // request object type

				Vertex3D ** vertices = object->getVertices(); // request vertex-Array
				TexCoords ** texCoords = object->getTexCoords();

				if (vertices == nullptr)
				{
					continue;
				}

				// draw every vertex of the object
				for (int i = 0; i < object->getVertexCount(); i++)
				{
					if (vertices[i] == nullptr) // prevent objects from crashing the render engine
					{
						continue;
					}

					glTexCoord2f(texCoords[i]->getX(), texCoords[i]->getY());
					glVertex3f(vertices[i]->getX(), vertices[i]->getY(), vertices[i]->getZ());
				}

			glEnd();

		glPopMatrix();
	}
}

void Renderer::preRender()
{
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

	glLoadIdentity();
}

void Renderer::postRender()
{
	glutSwapBuffers();
}