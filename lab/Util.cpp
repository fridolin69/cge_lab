#include "Util.h"
#include <algorithm>


Util::Util()
{
}

long Util::avg(std::vector<long> * vector)
{
	long tmp = 0;

	for(int i = 0; i < vector->size(); ++i)
	{
		tmp += vector->at(i);
	}

	return tmp / vector->size();
}

Util::~Util()
{
}
