#include "random.h"

std::random_device Random::device;
std::mt19937 Random::generator(device());

bool Random::reseed()
{
	generator.seed(device());
}

float Random::random()
{
	static std::uniform_real_distribution<float> dist(-1, 1);
	return dist(generator);
}

Vector3 Random::randomInUnitSphere()
{
    static std::uniform_real_distribution<float> dist(-1, 1);
    // generator.seed(device());
    
    Vector3 p = Vector3(dist(generator), dist(generator), dist(generator)) * 2.0f - Vector3(1, 1, 1);
	while(dot(p, p) >= 1.0f) 
	{
		p = Vector3(dist(generator), dist(generator), dist(generator)) * 2.0f - Vector3(1, 1, 1);
	}

	return p;
}