#pragma once
#include "Plane.h"
#include "Sphere.h"
#include "Material.h"
#include "Light.h"
#include <memory>
#include <vector>

class Scene
{
public:
	std::vector<std::shared_ptr<Object>> InitObjects();
	std::vector<std::shared_ptr<Light>> InitLightSources();

private:
	const Color blue = Color(0, 255, 255);
	const Color maroon = Color(128, 64, 64);
	const Color gray = Color(128, 128, 128);
	const Color orange = Color(245, 77, 15);
	const Color white = Color(255, 255, 255);

	const Material tileFloor = Material(Color(255, 255, 255), 0.2, 1, 2);
	const Material prettyGreen = Material(Color(128, 255, 128), 0.2, 1);
	const Material blueM = Material(blue, 0, 0);
	const Material silver = Material(gray, 0, 1);
	const Material orangeM = Material(orange, 0.8, 1);
	const Material maroonM = Material(maroon, 0.5, 1);
};