#pragma once
#include "Plane.h"
#include "Sphere.h"
#include "material.h"
#include "Light.h"
#include "Disk.hpp"
#include "Triangle.h"
#include "Box.h"
#include "TriangleMesh.h"
#include <memory>
#include <vector>

class Scene
{
public:
	std::vector<std::shared_ptr<Light>> lightSources;
	std::vector<std::shared_ptr<Object>> sceneObjects;

	std::vector<std::shared_ptr<Object>> InitObjects();
	std::vector<std::shared_ptr<Light>> InitLightSources();

	std::vector<std::shared_ptr<Object>> GetObjects()
	{
		return sceneObjects;
	}
	std::vector<std::shared_ptr<Light>> GetLightSources()
	{
		return lightSources;
	}


private:
	const Color black = Color(0);
	const Color blue = Color(0, 170, 255);
	const Color maroon = Color(190, 64, 64);
	const Color gray = Color(192, 192, 192);
	const Color orange = Color(245, 70, 10);
	const Color white = Color(255);
	const Color yellow = Color(255, 255, 50);
	const Color red = Color(255, 0, 0);
	const Color green = Color(0, 255, 0);

	const Color brass = Color(0.30 * 255, 0.20 * 255, 0.10 * 255);
	const Color silver = Color(0.94 * 255, 0.93 * 255, 0.90 * 255);

	// Color, ambient, reflective, refractive, diffusive, special
	const Material prettyGreenM = Material(Color(108, 255, 108), 0.8, 0, 0, 1, 0);
	const Material blueM = Material(blue, 0.2, 0, 0, 1, 0);
	const Material orangeM = Material(orange, 0.8, 0, 0, 1, 0);
	const Material yellowM = Material(yellow, 0.8, 0, 0, 1, 0);
	const Material maroonM = Material(maroon, 0.8, 0, 0, 1, 0);
	const Material blackM = Material(black, 0.6, 0.5, 0);

	// Color, ambient (more == brighter), reflective, refractive, diffusive (more == matte), special (2 == tile floor, for planes)
	const Material brassM = Material(brass,						0.3,  0.25, 0,     0.4, 0);
	const Material silverM = Material(silver,					0.1,  0.8,  0,     0.7, 0);
	const Material mirrorM = Material(white,					0,    1,    0,     0,   0);
	const Material tileFloorM = Material(Color(255),            0.4,  0,    0,     1, 2);

	const Material waterM = Material(Color(0, 0, 205),			0.1,  1,    1.333, 0,   0);
	const Material glassM = Material(white,						0.03, 1,    1.5,   0,   0);
	const Material diamondM = Material(white,					0.03, 0.7,  2,     0,   0);
	const Material transparentM = Material(white,				0.03, 0.001,GLOBAL_REFRACTION,     0,   0);
}; //															amb,  refl, refr, diff, special