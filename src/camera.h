#pragma once
#include "math.h"

class Camera
{
public:
    Camera();
    Ray cast(float x, float y);

private:
    Vector3 origin;
    Vector3 zero;
    Vector3 horizontal;
    Vector3 vertical;
};

Ray camera_cast_ray(const Camera& camera, float x, float y);