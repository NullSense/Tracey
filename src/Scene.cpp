#include "Scene.h"

std::vector<std::shared_ptr<Object>> Scene::InitObjects()
{
	std::shared_ptr<Plane> backPlane = std::make_shared<Plane>(Vector(0, 0, 15), Vector(0, 0, -1));
	backPlane->SetMaterial(blueM);
	std::shared_ptr<Plane> behindPlane = std::make_shared<Plane>(Vector(0, 0, -11), Vector(0, 0, 1));
	behindPlane->SetMaterial(blueM);
	std::shared_ptr<Plane> floorPlane = std::make_shared<Plane>(Vector(0, 0, 0), Vector(0, 1, 0));
	floorPlane->SetMaterial(tileFloorM);
	std::shared_ptr<Plane> leftPlane = std::make_shared<Plane>(Vector(-4, 0, 0), Vector(1, 0, 0));
	leftPlane->SetMaterial(maroonM);
	std::shared_ptr<Plane> rightPlane = std::make_shared<Plane>(Vector(5, 0, 0), Vector(-1, 0, 0));
	rightPlane->SetMaterial(prettyGreenM);
	std::shared_ptr<Plane> topPlane = std::make_shared<Plane>(Vector(0, 6, 0), Vector(0, -1, 0));
	topPlane->SetMaterial(yellowM);

	std::shared_ptr<Sphere> sphere1 = std::make_shared<Sphere>(1, Vector(0, 1, 7));
	sphere1->SetMaterial(mirrorM);
	std::shared_ptr<Sphere> sphere2 = std::make_shared<Sphere>(1, Vector(-3, 1, 7));
	sphere2->SetMaterial(silverM);
	std::shared_ptr<Sphere> sphere3 = std::make_shared<Sphere>(1, Vector(3.5, 1, 7));
	sphere3->SetMaterial(brassM);
	std::shared_ptr<Sphere> sphere4 = std::make_shared<Sphere>(0.8, Vector(sphere1->GetCenter().x + 1.5, 0.8, sphere1->GetCenter().z + 5.5));
	sphere4->SetMaterial(maroonM);
	std::shared_ptr<Sphere> sphere5 = std::make_shared<Sphere>(0.4, Vector(floorPlane->GetCenter().x + 2, 0.4, floorPlane->GetCenter().z));
	sphere5->SetMaterial(maroonM);
	std::shared_ptr<Sphere> sphere6 = std::make_shared<Sphere>(1, Vector(floorPlane->GetCenter().x, floorPlane->GetCenter().y + 3, floorPlane->GetCenter().z + 3.5));
	sphere6->SetMaterial(maroonM);

	std::vector<std::shared_ptr<Object>> sceneObjects;
	sceneObjects.push_back(sphere1);
	sceneObjects.push_back(sphere2);
	sceneObjects.push_back(sphere3);
	//sceneObjects.push_back(sphere4);
	//sceneObjects.push_back(sphere5);
	//sceneObjects.push_back(sphere6);

	sceneObjects.push_back(floorPlane);
	//sceneObjects.push_back(backPlane);
	//sceneObjects.push_back(behindPlane);
	//sceneObjects.push_back(leftPlane);
	//sceneObjects.push_back(rightPlane);
	//sceneObjects.push_back(topPlane);

	return sceneObjects;
}

std::vector<std::shared_ptr<Light>> Scene::InitLightSources()
{
	std::vector<std::shared_ptr<Light>> lightSources;
	Vector light1Position(7, 5, 3);
	std::shared_ptr<Light> light1 = std::make_shared<Light>(light1Position, orange, 2);
	std::shared_ptr<Light> light2 = std::make_shared<Light>(Vector(-2, 3, 3), yellow, 2);
	std::shared_ptr<Light> light3 = std::make_shared<Light>(Vector(0, 2, 9), white, 4);

	lightSources.push_back(light1);
	lightSources.push_back(light2);
	lightSources.push_back(light3);

	return lightSources;
}