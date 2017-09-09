#include "camera.h"
#include <glm\glm.hpp>
#include <glm\gtc\constants.hpp>
#include <iostream>

Camera::Camera(Vector3 position, Vector3 up, Vector3 lookAt, float aspectRatio, float fov)
{
    origin = position;
    Vector3 u, v, w;

    float angle = fov * glm::pi<float>() / 180.0f;
    float hHeight = glm::tan(angle / 2.0f);
    float hWidth = aspectRatio * hHeight;
    
    w = glm::normalize(position - lookAt);
    u = glm::normalize(glm::cross(up, w));
    v = glm::cross(w, u);

    zero = position - (hWidth * u) - (hHeight * v) - w;
    horizontal = 2 * hWidth * u;
    vertical = 2 * hHeight * v;
}

Ray Camera::cast(float x, float y) const
{
    return Ray(origin, zero + (horizontal * x) + (vertical * y) - origin);
}