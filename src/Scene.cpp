#include "Scene.h"

std::vector<std::shared_ptr<Object>> Scene::InitObjects()
{
	std::shared_ptr<Plane> backPlane = std::make_shared<Plane>(Vector(0, 0, 15), Vector(0, 0, -1));
	backPlane->SetMaterial(blueM);
	std::shared_ptr<Plane> floorPlane = std::make_shared<Plane>(Vector(0, 0, 0), Vector(0, 1, 0));
	floorPlane->SetMaterial(silverM);
	std::shared_ptr<Plane> leftPlane = std::make_shared<Plane>(Vector(-4, 0, 0), Vector(1, 0, 0));
	leftPlane->SetMaterial(maroonM);
	std::shared_ptr<Plane> rightPlane = std::make_shared<Plane>(Vector(5, 0, 0), Vector(-1, 0, 0));
	rightPlane->SetMaterial(prettyGreen);


	std::shared_ptr<Sphere> sphere1 = std::make_shared<Sphere>(0.5, Vector(-2, 0.5, 2.5));
	sphere1->SetMaterial(brassM);
	std::shared_ptr<Sphere> sphere2 = std::make_shared<Sphere>(0.5, Vector(1, 0.5, -2));
	sphere2->SetMaterial(brassM);
	std::shared_ptr<Sphere> sphere3 = std::make_shared<Sphere>(0.6, Vector(7, 0.6, 4));
	sphere3->SetMaterial(maroonM);
	std::shared_ptr<Sphere> sphere4 = std::make_shared<Sphere>(0.8, Vector(sphere1->GetCenter().x + 0.5, 0.8, sphere1->GetCenter().z + 5.5));
	sphere4->SetMaterial(silverM);
	std::shared_ptr<Sphere> sphere5 = std::make_shared<Sphere>(0.4, Vector(floorPlane->GetCenter().x + 4, 0.4, floorPlane->GetCenter().z - 2));
	sphere5->SetMaterial(silverM);
	//std::shared_ptr<Sphere> sphere6 = std::make_shared<Sphere>(1, Vector(sphere4->GetCenter().x + 3, 1, sphere4->GetCenter().z + 3));
	//sphere6->SetMaterial(brassM);

	std::vector<std::shared_ptr<Object>> sceneObjects;
	sceneObjects.push_back(sphere1);
	sceneObjects.push_back(sphere2);
	sceneObjects.push_back(sphere3);
	sceneObjects.push_back(sphere4);
	sceneObjects.push_back(sphere5);
	//sceneObjects.push_back(sphere6);

	sceneObjects.push_back(floorPlane);
	//sceneObjects.push_back(backPlane);
	//sceneObjects.push_back(leftPlane);
	//sceneObjects.push_back(rightPlane);

	return sceneObjects;
}

std::vector<std::shared_ptr<Light>> Scene::InitLightSources()
{
	std::vector<std::shared_ptr<Light>> lightSources;
	Vector light1Position(4, 3, 2);
	std::shared_ptr<Light> light1 = std::make_shared<Light>(light1Position, orange, 1);
	std::shared_ptr<Light> light2 = std::make_shared<Light>(Vector(light1Position.x - 15, light1Position.y, light1Position.z - 3), yellow, 1);
	std::shared_ptr<Light> light3 = std::make_shared<Light>(Vector(0, 2, 12.5), white, 1);

	lightSources.push_back(light1);
	//lightSources.push_back(light2);
	lightSources.push_back(light3);

	return lightSources;
}