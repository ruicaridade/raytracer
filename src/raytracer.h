#pragma once
#include <vector>
#include <string>
#include "color.h"
#include "scene.h"
#include "camera.h"
#include "math.h"

class Raytracer
{
public:
    // TODO: Resolution will be decided by the Camera.
    Raytracer(int width, int height, int depth, float gamma = 2.2f);
    void render(const Scene& scene, const Camera& camera);
    void saveAsImageFile(const std::string& filename);

private:
    Color trace(const Scene& scene, const Ray& ray, int depth);
    
    int width, height;
    int maxDepth;
    float gamma;
    std::vector<std::vector<Color>> output;
};