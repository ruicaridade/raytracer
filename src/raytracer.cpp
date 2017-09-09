#include "raytracer.h"
#include <cmath>
#include <limits>
#include <iostream>
#include <glm\glm.hpp>
#include <thread>
#include <future>
#include <algorithm>
#include "external\TinyPngOut.h"
#include "utilities\random.h"

Raytracer::Raytracer(int width, int height, int depth, float gamma)
    : width(width), height(height), maxDepth(depth), gamma(gamma) {}

static Vector3 linearToGamma(const Vector3 &color, float value)
{
    float gamma = 1.0f / value;
    return Vector3(pow(color.x, gamma), pow(color.y, gamma), pow(color.z, gamma));
}

Raytracer::RenderResult Raytracer::render(const Scene &scene, const Camera &camera, int passes, int index, int minY, int maxY)
{
    RenderResult result;
    result.index = index;

    for (int y = maxY - 1; y >= minY; y--)
    {
        std::vector<Vector3> colors;

        Vector3 color;
        for (size_t x = 0; x < width; x++)
        {
            for (size_t i = 0; i < passes; i++)
            {
                float xx = float(x + Random::random()) / float(width);
                float yy = float(y + Random::random()) / float(height);
                color = color + trace(scene, camera.cast(xx, yy), 0);
            }

            color = color / (float)passes;
            colors.push_back(linearToGamma(color, gamma));
        }

        result.colors.push_back(colors);
    }

    return result;
}

void Raytracer::render(const Scene &scene, const Camera &camera, int passes, int maxThreads)
{
    output.clear();

    int linesPerThread = height / maxThreads;

    std::vector<std::future<RenderResult>> futures;
    std::vector<RenderResult> results;

    for (size_t i = 0; i < maxThreads; i++)
    {
        int minY = i * linesPerThread;
        int maxY = minY + linesPerThread;

        auto future = std::async(std::launch::async, [this, &scene, &camera, &passes, &i, minY, maxY] {
            return render(scene, camera, passes, i, minY, maxY);
        });

        futures.push_back(std::move(future));
    }

    for (int i = futures.size() - 1; i >= 0; i--)
    {
        results.push_back(futures[i].get());
    }

    for (size_t i = 0; i < results.size(); i++)
    {
        auto &result = results[i];
        for (size_t j = 0; j < result.colors.size(); j++)
        {
            output.push_back(result.colors[j]);
        }
    }
}

Vector3 Raytracer::trace(const Scene &scene, const Ray &ray, int depth) const
{
    Intersection intersection;
    if (scene.intersects(ray, 0.0001f, std::numeric_limits<float>::max(), intersection))
    {
        auto material = intersection.object->getMaterial();
        Vector3 attenuation;
        Ray scattered;

        if (depth < maxDepth && material->scatter(ray, intersection, attenuation, scattered))
        {
            return attenuation * trace(scene, scattered, depth + 1);
        }

        return Vector3(0, 0, 0);
    }
    else
    {
        Vector3 direction = glm::normalize(ray.direction);
        float t = 0.5f * (direction.y + 1.0f);
        return (1.0f - t) * Vector3(1, 1, 1) + t * Vector3(0.5f, 0.7f, 1);
    }
}

void Raytracer::saveAsImageFile(const std::string &filename) const
{
    if (output.size() == 0)
        return;

    unsigned int height = output.size();
    unsigned int width = output[0].size();

    std::vector<uint8_t> image;

    for (size_t j = 0; j < height; j++)
    {
        for (size_t i = 0; i < width; i++)
        {
            image.push_back((uint8_t)(glm::clamp(output[j][i].x, 0.0f, 1.0f) * 255));
            image.push_back((uint8_t)(glm::clamp(output[j][i].y, 0.0f, 1.0f) * 255));
            image.push_back((uint8_t)(glm::clamp(output[j][i].z, 0.0f, 1.0f) * 255));
        }
    }

    FILE *file = fopen(filename.c_str(), "wb");

    if (file == nullptr)
    {
        std::cout << "Couldn't open file stream " << filename << std::endl;
        return;
    }

    struct TinyPngOut png;

    if (TinyPngOut_init(&png, file, width, height) != TINYPNGOUT_OK)
    {
        fclose(file);
        std::cout << "Couldn't load png file " << filename << std::endl;
        return;
    }

    if (TinyPngOut_write(&png, image.data(), width * height) != TINYPNGOUT_OK)
    {
        fclose(file);
        std::cout << "Couldn't write to png file " << filename << std::endl;
        return;
    }

    if (TinyPngOut_write(&png, nullptr, 0) != TINYPNGOUT_DONE)
    {
        std::cout << "File might be corrupted " << filename << std::endl;
    }

    fclose(file);
}