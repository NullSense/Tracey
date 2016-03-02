#pragma once
#include "Object.h"
#include <vector>

class Scene
{
public:
	Scene();

	std::vector<Object> InitObjects();
};