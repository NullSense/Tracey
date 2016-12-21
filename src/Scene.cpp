#include "Scene.h"

std::vector<std::shared_ptr<Object>> Scene::InitObjects()
{
	std::shared_ptr<Plane> floorPlane = std::make_shared<Plane>(Vector(0, -1, 0), Vector(0, 1, 0));
	floorPlane->SetMaterial(tileFloorM);
	std::shared_ptr<Plane> backPlane = std::make_shared<Plane>(Vector(0, 0, 20), Vector(0, 0, -1));
	backPlane->SetMaterial(prettyGreenM);

	std::shared_ptr<Sphere> sphere1 = std::make_shared<Sphere>(0.5, Vector(1, -0.5, 2.5));
	sphere1->SetMaterial(maroonM);
	std::shared_ptr<Sphere> sphere2 = std::make_shared<Sphere>(1.3, Vector(-1, 0.3, 4));
	sphere2->SetMaterial(mirrorM);
	std::shared_ptr<Sphere> sphere3 = std::make_shared<Sphere>(0.2, Vector(sphere1->GetCenter().x - 2, sphere1->GetCenter().y, sphere1->GetCenter().z - 1));
	sphere3->SetMaterial(silverM);
	std::shared_ptr<Sphere> sphere4 = std::make_shared<Sphere>(0.2, Vector(sphere1->GetCenter().x - 1, sphere1->GetCenter().y + 0.4, sphere1->GetCenter().z - 0.71));
	sphere4->SetMaterial(waterM);
	std::shared_ptr<Sphere> sphere5 = std::make_shared<Sphere>(0.4, Vector(floorPlane->GetCenter().x - 3.5, -0.6, floorPlane->GetCenter().z + 2.9));
	sphere5->SetMaterial(waterM);

	std::vector<std::shared_ptr<Object>> sceneObjects;
	sceneObjects.push_back(sphere1);
	sceneObjects.push_back(sphere2);
	sceneObjects.push_back(sphere3);
	sceneObjects.push_back(sphere4);
	sceneObjects.push_back(sphere5);
	sceneObjects.push_back(floorPlane);
	sceneObjects.push_back(backPlane);

	return sceneObjects;
}

std::vector<std::shared_ptr<Light>> Scene::InitLightSources()
{
	std::vector<std::shared_ptr<Light>> lightSources;
	Vector light1Position(-2.5, 1, 0.6);
	std::shared_ptr<Light> light1 = std::make_shared<Light>(light1Position, white, 1, Light::POINT);
	std::shared_ptr<Light> light2 = std::make_shared<Light>(Vector(light1Position.x + 6, light1Position.y, light1Position.z + 4), yellow, 0.8, Light::POINT);
	lightSources.push_back(light1);
	lightSources.push_back(light2);

	return lightSources;
}