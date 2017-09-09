#pragma once
#include <vector>
#include <string>
#include <memory>
#include "scene.h"
#include "camera.h"
#include "math.h"

class Raytracer
{
public:
  Raytracer(int width, int height, int depth, float gamma = 2.2f);
  void render(const Scene &scene, const Camera &camera, int passes = 100, int maxThreads = 4);
  void saveAsImageFile(const std::string &filename) const;

private:
  struct RenderResult
  {
    int index;
    std::vector<std::vector<Vector3>> colors;
  };

  Vector3 trace(const Scene &scene, const Ray &ray, int depth) const;
  RenderResult render(const Scene &scene, const Camera &camera, int passes, int index, int minY, int maxY);

  int width, height;
  int maxDepth;
  float gamma;
  std::vector<std::vector<Vector3>> output;
};