#pragma once
#include "Plane.h"
#include "Sphere.h"
#include "Material.h"
#include "Light.h"
#include "Disk.hpp"
#include "Box.h"
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
	const Color gray = Color(192, 192, 192);
	const Color orange = Color(245, 77, 15);
	const Color white = Color(255, 255, 255);
	const Color yellow = Color(255, 255, 50);

	const Color brass = Color(0.30 * 255, 0.20 * 255, 0.10 * 255);
	const Color silver = Color(0.94 * 255, 0.93 * 255, 0.90 * 255);

	// Color, ambient, reflective, refractive, diffusive, special
	const Material prettyGreenM = Material(Color(128, 255, 128), 0.8, 0, 0, 1, 0);
	const Material blueM = Material(blue, 0.8, 0, 0, 1, 0);
	const Material orangeM = Material(orange, 0.8, 0, 0, 1, 0);
	const Material yellowM = Material(yellow, 0.8, 0, 0, 1, 0);
	const Material maroonM = Material(maroon, 0.8, 0, 0, 1, 0);

	// Color, ambient (more == brighter), reflective, refractive, diffusive (more == matte), special (2 == tile floor, for planes)
	const Material brassM = Material(brass, 0.3, 0.25, 0, 0.4, 0);
	const Material silverM = Material(silver, 0.1, 0.8, 0, 0.7, 0);
	const Material mirrorM = Material(white, 0, 1, 0, 0, 0);
	const Material tileFloorM = Material(Color(255, 255, 255), 0.9, 0.1, 0, 0.9, 2);
};