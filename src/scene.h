#pragma once
#include <vector>
#include <memory>
#include <functional>
#include "traceable.h"

class Scene
{
public:
    template <typename T, typename... TArgs>
    void add(TArgs... args);

    bool intersects(const Ray& ray, float min, float max, Intersection& intersection) const;

    void forEach(std::function<void(const std::unique_ptr<Traceable>&)> callback) const;

private:
    std::vector<std::unique_ptr<Traceable>> objects;
};

template <typename T, typename... TArgs>
void Scene::add(TArgs... args)
{
    objects.push_back(std::make_unique<T>(args...));
}