#pragma once
#include <random>
#include "..\math.h"

class Random
{
public:
    static bool reseed();
    static float random();
    static Vector3 randomInUnitSphere();

private:
    static std::random_device device;
	static std::mt19937 generator;
};