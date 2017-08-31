#include "camera.h"

Camera::Camera()
{
    origin = Vector3(0, 0, 0);    
    zero = Vector3(-2, -1, -1);
    vertical = Vector3(0, 2, 0);
    horizontal = Vector3(4, 0, 0);
}

Ray camera_cast_ray(const Camera& camera, float x, float y)
{
    return Ray(camera.origin, camera.zero + camera.horizontal * x + camera.vertical * y);
}