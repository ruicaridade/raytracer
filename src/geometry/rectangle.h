#pragma once
#include "..\traceable.h"

class Rectangle : public Traceable
{
  public:
    Rectangle(const Vector2 &p0, const Vector2 &p1, float k, const std::string &materialName);

    virtual bool intersects(const Ray &ray, float min, float max, Intersection &intersection) const override;

  private:
    Vector2 p0;
    Vector2 p1;
    float k;
};