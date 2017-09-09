#pragma once
#include "math.h"

class Camera
{
public:
    Camera(Vector3 position, Vector3 up, Vector3 lookAt, float aspectRatio, float fov);
    Ray cast(float x, float y) const;

private:
    Vector3 origin;
    Vector3 zero;
    Vector3 horizontal;
    Vector3 vertical;
};