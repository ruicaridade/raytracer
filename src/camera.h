#pragma once
#include "math.h"

struct Camera
{
    Camera();

    Vector3 origin;
    Vector3 zero;
    Vector3 horizontal;
    Vector3 vertical;
};

Ray camera_cast_ray(const Camera& camera, float x, float y);