#pragma once
#include "math.h"

class Texture
{
  public:
    virtual Vector3 color(int u, int v, const Vector3& point) = 0;
};