#pragma once

struct Vector3
{
    Vector3(float x = 0, float y = 0, float z = 0);

    float x;
    float y;
    float z;
};

Vector3 operator+(const Vector3& v1, const Vector3& v2);
Vector3 operator-(const Vector3& v1, const Vector3& v2);
Vector3 operator*(const Vector3& vector, float scalar);

float length(const Vector3& vector);
float dot(const Vector3& a, const Vector3& b);
Vector3& normalize(Vector3& vector);

struct Ray
{
    Ray(const Vector3& origin, const Vector3& direction);

    Vector3 origin;
    Vector3 direction;
};

Vector3 ray_get_point(const Ray& ray, float t);