#include "raytracer.h"
#include <cmath>
#include "utilities\random.h"

Raytracer::Raytracer(int width, int height, int depth, float gamma)
    : width(width), height(height), maxDepth(depth), gamma(gamma) {}

static Color linearToGamma(const Color &color, float value)
{
    Vector3 c = color.vector();
    float gamma = 1.0f / value;
    Vector3 result = Vector3(pow(c.x, gamma), pow(c.y, gamma), pow(c.z, gamma));
    return Color::fromVector(result);
}

void Raytracer::render(const Scene &scene, const Camera &camera, bool antialiasing, int passes)
{
    output.clear();
    for (int y = height - 1; y >= 0; y--)
    {
        std::vector<Color> row;
        for (int x = 0; x < width; x++)
        {
            if (antialiasing)
            {
                Vector3 color;
                for (size_t i = 0; i < passes; i++)
                {
                    float xx = float(x + Random::random()) / float(width);
                    float yy = float(y + Random::random()) / float(height);
                    color = color + trace(scene, camera.cast(xx, yy), 0).vector(); 
                }
                
                color = color / passes;
                row.push_back(linearToGamma(Color::fromVector(color), gamma));
            }
            else
            {
                float xx = (float)x / width;
                float yy = (float)y / height;
    
                row.push_back(linearToGamma(trace(scene, camera.cast(xx, yy), 0), gamma));
            }
        }

        output.push_back(row);
    }
}

Color Raytracer::trace(const Scene &scene, const Ray &ray, int depth)
{
    Intersection intersection;
    scene.forEach([&intersection, ray](const std::unique_ptr<Traceable> &traceable) {
        Intersection temp;
        traceable->intersects(ray, temp);
        if (temp.distance < intersection.distance)
        {
            intersection = temp;
        }
    });

    if (intersection.hit)
    {
        auto material = intersection.object->getMaterial();
        Vector3 attenuation;
        Ray scatteredRay;

        if (depth < maxDepth && material->scatter(ray, intersection, attenuation, scatteredRay))
        {
            return attenuation * trace(scene, scatteredRay, depth + 1);
        }
        else
        {
            return Color(0, 0, 0, 0);
        }
    }
    else
    {
        float t = 0.5f * (ray.direction.y + 1);
        return Color((1 - t) * 255 + t * 128, (1 - t) * 255 + t * 179, (1 - t) * 255 + t * 255, 255);
    }
}

void Raytracer::saveAsImageFile(const std::string& filename)
{
    Color::saveToPng(filename, output);
}