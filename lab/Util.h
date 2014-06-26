#pragma once

#include <vector>
#include "Vertex3D.h"

class Util
{
public:
	Util();
	virtual ~Util();

	static long avg(std::vector<long> * vector);
	static Vertex3D * normal(Vertex3D * c1, Vertex3D * c2, Vertex3D * c3, Vertex3D * c4);
	static Vertex3D * vec(Vertex3D * p1, Vertex3D * p2);
};