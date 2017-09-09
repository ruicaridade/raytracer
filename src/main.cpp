#include <iostream>
#include <chrono>
#include <fstream>
#include <toml/toml.h>
#include "raytracer.h"
#include "geometry\sphere.h"
#include "materials\diffuse.h"
#include "materials\metal.h"

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

	printf("Done!\n");

	printf("Resolution: %i, %i\n", width, height);
	printf("Ray depth: %i\n", depth);
	printf("Anti-aliasing: %i\n\n", antiAliasingPasses);
	printf("Drawing scene... ");

	Raytracer raytracer(width, height, depth);

	Material::registerMaterial<Diffuse>("diffuse", Vector3(0.5f, 0.8f, 0.25f));
	Material::registerMaterial<Metal>("metal", Vector3(0.8f, 0.8f, 0.8f), 0.3f);

	Scene scene;
	scene.ambient = Vector3(0.5f, 0.5f, 0.5f);
	scene.addLight<Light>(Vector3(1, 1, -1), Vector3(0.5f, 0.5f, 0.5f));

	scene.add<Sphere>(Vector3(0, 0, -2), 1, "metal");
	// scene.add<Sphere>(Vector3(0, -100.5f, -1), 100, "metal");
	// scene.add<Sphere>(Vector3(1, 10, -1), 0.4f, "diffuse");
	// scene.add<Sphere>(Vector3(-1, 10, -1), 0.4f, "diffuse");

	Camera camera;

	elapsedSeconds();
	raytracer.render(scene, camera, true, antiAliasingPasses);
	float elapsed = elapsedSeconds();
	printf("Done in %.2fms!\n", elapsed*1000);

	printf("Writing to image file... ");
	
	elapsedSeconds();
	raytracer.saveAsImageFile("output.png");
	elapsed = elapsedSeconds();
	printf("Done in %.2fms!\n", elapsed*1000);
	return 0;
}