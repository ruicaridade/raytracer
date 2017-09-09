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
    struct Row
    {
      int index;
      std::vector<Vector3> colors;
    };

    Vector3 trace(const Scene &scene, const Ray &ray, int depth) const;
    Row renderRow(const Scene& scene, const Camera& camera, int passes, int y);

    int width, height;
    int maxDepth;
    float gamma;
    std::vector<std::vector<Vector3>> output;
};