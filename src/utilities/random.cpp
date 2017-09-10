#include "random.h"
#include <cstdlib>
#include <ctime>

bool Random::reseed()
{
	srand(time(NULL));
	return true;
}

float Random::random()
{
	return -1 + (float)(rand()) / ((float)(RAND_MAX / (1 - (-1))));
}

Vector3 Random::randomInUnitSphere()
{
	Vector3 p = Vector3(random(), random(), random()) * 2.0f - Vector3(1, 1, 1);
	while (dot(p, p) >= 1.0f)
	{
		p = Vector3(random(), random(), random()) * 2.0f - Vector3(1, 1, 1);
	}

	return p;
}