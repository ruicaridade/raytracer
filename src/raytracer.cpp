#include "raytracer.h"
#include <cmath>
#include <limits>
#include "utilities\random.h"

Raytracer::Raytracer(int width, int height, int depth, float gamma)
    : width(width), height(height), maxDepth(depth), gamma(gamma) {}

static Vector3 linearToGamma(const Vector3 &color, float value)
{
    float gamma = 1.0f / value;
    return Vector3(pow(color.x, gamma), pow(color.y, gamma), pow(color.z, gamma));
}

void Raytracer::render(const Scene &scene, const Camera &camera, bool antialiasing, int passes)
{
    output.clear();
    for (int y = height - 1; y >= 0; y--)
    {
        std::vector<Vector3> row;
        for (int x = 0; x < width; x++)
        {
            if (antialiasing)
            {
                Vector3 color;
                for (size_t i = 0; i < passes; i++)
                {
                    float xx = float(x + Random::random()) / float(width);
                    float yy = float(y + Random::random()) / float(height);
                    color = color + trace(scene, camera.cast(xx, yy), 0);
                }
                
                color = color / passes;
                row.push_back(linearToGamma(color, gamma));
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

Vector3 Raytracer::trace(const Scene &scene, const Ray &ray, int depth)
{
    Intersection intersection;
    if (scene.intersects(ray, 0.0001f, std::numeric_limits<float>::max(), intersection))
    {
        auto material = intersection.object->getMaterial();
        Vector3 attenuation;
        Ray scattered;

        if (depth < maxDepth && material->scatter(ray, intersection, attenuation, scattered))
        {
            // Vector3 lightOutput;
            // scene.forEach([&lightOutput, scene, ray, intersection](const std::unique_ptr<Light>& light)
            // {
            //     Intersection lightIntersection;
            //     if (!scene.intersects(Ray(intersection.point, light->getDirection()), 
            //         0.001f, std::numeric_limits<float>::max(), lightIntersection))
            //     {
            //         lightOutput = lightOutput + light->process(ray, intersection);
            //     }
            // });
            // return lightOutput + scene.ambient * attenuation * trace(scene, scattered, depth + 1);
            return attenuation * trace(scene, scattered, depth + 1);
        }

        return Vector3(0, 0, 0);
    }
    else
    {
        Vector3 direction = normalize(ray.direction);
        float t = 0.5f * (direction.y + 1.0f);
        return (1.0f - t) * Vector3(1, 1, 1) + t * Vector3(0.5f, 0.7f, 1);
    }
}

void Raytracer::saveAsImageFile(const std::string& filename)
{
    Vector3::saveToPng(filename, output);
}