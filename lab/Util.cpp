#include "Util.h"
#include "Vertex3D.h"
#include <algorithm>


Util::Util()
{
}

long Util::avg(std::vector<long> * vector)
{
	long tmp = 0;

	for(unsigned int i = 0; i < vector->size(); ++i)
	{
		tmp += vector->at(i);
	}

	return tmp / vector->size();
}

Vertex3D * Util::normal(Vertex3D * c1, Vertex3D * c2, Vertex3D * c3, Vertex3D * c4)
{
	Vertex3D * v1 = vec(c1, c2);
	Vertex3D * v2 = vec(c3, c4);

	return new Vertex3D(
		v1->getY() * v2->getZ() - v1->getZ() * v2->getY(),
		v2->getX() * v1->getZ() - v2->getZ() * v1->getX(),
		v1->getX() * v2->getY() - v1->getY() * v2->getX()
	);
}

Vertex3D * Util::vec(Vertex3D * p1, Vertex3D * p2)
{
	return new Vertex3D(p2->getX() + p1->getX(), p2->getY() + p1->getY(), p2->getZ() + p1->getZ());
}

Util::~Util()
{
}
