#pragma once
#include "math.h"

class Camera
{
public:
    Camera();
    Ray cast(float x, float y) const;

private:
    Vector3 origin;
    Vector3 zero;
    Vector3 horizontal;
    Vector3 vertical;
};