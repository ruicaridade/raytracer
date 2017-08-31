#pragma once

struct Vector3
{
    Vector3(float x = 0, float y = 0, float z = 0);

    Vector3 operator+(const Vector3& vector);
    Vector3 operator-(const Vector3& vector);
    
    Vector3 operator*(float scalar);
    void operator*=(float scalar);

    float x;
    float y;
    float z;
};

float length(const Vector3& vector);
float dot(const Vector3& a, const Vector3& b);
void normalize(Vector3& vector);