#pragma once
#include "..\math.h"

class Random
{
  public:
    static bool reseed();
    static float random();
    static Vector3 randomInUnitSphere();
};