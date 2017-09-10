#include <iostream>
#include <chrono>
#include <fstream>
#include <toml/toml.h>
#include "raytracer.h"
#include "geometry\sphere.h"
#include "materials\diffuse.h"
#include "materials\metal.h"
#include "materials\refractive.h"
#include "utilities\random.h"
#include "textures\checker_texture.h"

float elapsedSeconds()	
{
	static auto previous = std::chrono::high_resolution_clock::now();
    auto now = std::chrono::high_resolution_clock::now();
    std::chrono::duration<float> elapsed = now - previous;
    previous = now;
    return elapsed.count();
}

int main()
{
	Random::reseed();

	printf("Parsing config... ");
	std::ifstream file("config.toml");
	toml::ParseResult parseResult = toml::parse(file);
	if (!parseResult.valid())
	{
		std::cout << parseResult.errorReason << std::endl;
		return 1;
	}

	const toml::Value& value = parseResult.value;
	int width = value.get<int>("width");
	int height = value.get<int>("height");
	int depth = value.get<int>("depth");
	int antiAliasingPasses = value.get<int>("aa_passes");
	int threadCount = value.get<int>("threads");

	printf("Done!\n");

	printf("Resolution: %i, %i\n", width, height);
	printf("Ray depth: %i\n", depth);
	printf("Anti-aliasing: %i\n\n", antiAliasingPasses);
	printf("Drawing scene... ");

	Raytracer raytracer(width, height, depth);

	Material::create<Diffuse>("green", Vector3(0.5f, 0.8f, 0.25f), nullptr);
	
	Material::create<Metal>("ground", Vector3(1, 1, 1), 0.2f,
		std::make_shared<CheckerTexture>(Vector3(0.35f, 0.35f, 0.35f), Vector3(0.5f, 0.5f, 0.5f)));
	Material::create<Metal>("gold", Vector3(0.8f, 0.7f, 0.5f), 0.4f, nullptr);
	Material::create<Metal>("chrome", Vector3(0.8f, 0.8f, 0.8f), 0.1f, nullptr);
	
	Material::create<Refractive>("glass", 1.5f);

	Scene scene;
	scene.ambient = Vector3(0.5f, 0.5f, 0.5f);
	scene.addLight<Light>(Vector3(1, 1, -1), Vector3(0.5f, 0.5f, 0.5f));

	scene.add<Sphere>(Vector3(0, -100.5f, -1), 100, "ground");

	scene.add<Sphere>(Vector3(-0.5f, 0, 0), 0.4f, "green");
	scene.add<Sphere>(Vector3(0.5f, 0, -1), 0.4f, "chrome");
	scene.add<Sphere>(Vector3(0.5f, 0, 0), 0.4f, "gold");

	scene.add<Sphere>(Vector3(-0.5f, 0, -1), 0.4f, "glass");
	scene.add<Sphere>(Vector3(-0.5f, 0, -1), -0.35f, "glass");

	Camera camera(Vector3(-1.5f, 1, 1), Vector3(0, 1, 0), Vector3(0, 0, -0.5f), float(width) / float(height), 45.0f);

	elapsedSeconds();
	raytracer.render(scene, camera, antiAliasingPasses, threadCount);
	float elapsed = elapsedSeconds();
	printf("Done in %.2fms!\n", elapsed*1000);

	printf("Writing to image file... ");
	
	elapsedSeconds();
	raytracer.saveAsImageFile("output.png");
	elapsed = elapsedSeconds();
	printf("Done in %.2fms!\n", elapsed*1000);
	return 0;
}