#include "camera.h"

Camera::Camera()
{
    origin = Vector3(0, 0, 0);    
    zero = Vector3(-2, -1, -1);
    vertical = Vector3(0, 2, 0);
    horizontal = Vector3(4, 0, 0);
}

Ray Camera::cast(float x, float y)
{
    return Ray(origin, zero + horizontal * x + vertical * y - origin);
}