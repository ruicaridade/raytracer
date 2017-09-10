#pragma once
#include <memory>
#include "..\texture.h"

class CheckerTexture : public Texture
{
  public:
    CheckerTexture(const Vector3& odd, const Vector3& even);

    virtual Vector3 color(int u, int v, const Vector3 &point) override;

  private:
    Vector3 odd;
    Vector3 even;
};