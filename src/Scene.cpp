#include "Scene.h"

std::vector<std::shared_ptr<Object>> Scene::InitObjects()
{
	std::shared_ptr<Plane> backPlane = std::make_shared<Plane>(Vector(0, 0, 15), Vector(0, 0, -1));
	backPlane->SetMaterial(blueM);
	std::shared_ptr<Plane> floorPlane = std::make_shared<Plane>(Vector(0, 0, 0), Vector(0, 1, 0));
	floorPlane->SetMaterial(gray);
	std::shared_ptr<Plane> leftPlane = std::make_shared<Plane>(Vector(-4, 0, 0), Vector(1, 0, 0));
	leftPlane->SetMaterial(maroonM);
	std::shared_ptr<Plane> rightPlane = std::make_shared<Plane>(Vector(5, 0, 0), Vector(-1, 0, 0));
	rightPlane->SetMaterial(prettyGreenM);
	std::shared_ptr<Plane> topPlane = std::make_shared<Plane>(Vector(0, 6, 0), Vector(0, -1, 0));
	topPlane->SetMaterial(yellowM);

	std::shared_ptr<Sphere> sphere1 = std::make_shared<Sphere>(1, Vector(0, 1, -3));
	sphere1->SetMaterial(maroon);
	std::shared_ptr<Sphere> sphere2 = std::make_shared<Sphere>(1, Vector(-3, 1, -3));
	sphere2->SetMaterial(orange);
	std::shared_ptr<Sphere> sphere3 = std::make_shared<Sphere>(1, Vector(3, 1, -3));
	sphere3->SetMaterial(yellow);
	std::shared_ptr<Sphere> sphere4 = std::make_shared<Sphere>(1, Vector(4, 1, 5));
	sphere4->SetMaterial(maroon);
	std::shared_ptr<Sphere> sphere5 = std::make_shared<Sphere>(1, Vector(-3, 1, 5));
	sphere5->SetMaterial(maroon);
	std::shared_ptr<Sphere> hovering = std::make_shared<Sphere>(1, Vector(-2, 5, floorPlane->GetCenter().z + 3.5));
	hovering->SetMaterial(maroon);

	std::vector<std::shared_ptr<Object>> sceneObjects;
	sceneObjects.push_back(sphere1);
	sceneObjects.push_back(sphere2);
	sceneObjects.push_back(sphere3);
	sceneObjects.push_back(sphere4);
	sceneObjects.push_back(sphere5);
	sceneObjects.push_back(hovering);

	sceneObjects.push_back(floorPlane);
	//sceneObjects.push_back(backPlane);
	//sceneObjects.push_back(leftPlane);
	//sceneObjects.push_back(rightPlane);
	//sceneObjects.push_back(topPlane);

	return sceneObjects;
}

std::vector<std::shared_ptr<Light>> Scene::InitLightSources()
{
	std::vector<std::shared_ptr<Light>> lightSources;
	Vector light1Position(4, 3, 2);
	std::shared_ptr<Light> light1 = std::make_shared<Light>(light1Position, white, 1);
	std::shared_ptr<Light> light2 = std::make_shared<Light>(Vector(light1Position.x - 15, light1Position.y, light1Position.z - 3), yellow, 1);
	std::shared_ptr<Light> light3 = std::make_shared<Light>(Vector(0, 2, 10), white, 1);

	lightSources.push_back(light1);
	lightSources.push_back(light2);
	//lightSources.push_back(light3);

	return lightSources;
}