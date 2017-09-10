#include "scene.h"

Scene::Scene()
    : ambient(Vector3(1, 1, 1)) { }

bool Scene::intersects(const Ray& ray, float min, float max, Intersection& intersection) const
{
    Intersection temp;
    bool hit = false;
    float closest = max;
    for (size_t i = 0; i < objects.size(); i++)
    {
        if (objects[i]->intersects(ray, min, closest, temp))
        {
            hit = true;
            closest = temp.distance;
            intersection = temp;
        }
    }

    return hit;
}

void Scene::forEach(std::function<void(const std::unique_ptr<Traceable>&)> callback) const
{
    for (size_t i = 0; i < objects.size(); i++)
    {
        callback(objects[i]);
    }
}