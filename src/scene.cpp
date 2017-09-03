#include "scene.h"

void Scene::forEach(std::function<void(const std::unique_ptr<Traceable>&)> callback) const
{
    for (size_t i = 0; i < objects.size(); i++)
    {
        callback(objects[i]);
    }
}