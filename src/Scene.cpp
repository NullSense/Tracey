#include "Scene.h"
#include <random>

std::vector<std::shared_ptr<Object>> Scene::InitObjects()
{
	std::shared_ptr<Plane> backPlane = std::make_shared<Plane>(Vector(0, 0, 15), Vector(0, 0, -1));
	backPlane->SetMaterial(blueM);
	std::shared_ptr<Plane> floorPlane = std::make_shared<Plane>(Vector(0, 0, 0), Vector(0, 1, 0));
	floorPlane->SetMaterial(tileFloorM);
	std::shared_ptr<Plane> leftPlane = std::make_shared<Plane>(Vector(-7, 0, 0), Vector(1, 0, 0));
	leftPlane->SetMaterial(maroonM);
	std::shared_ptr<Plane> rightPlane = std::make_shared<Plane>(Vector(7, 0, 0), Vector(-1, 0, 0));
	rightPlane->SetMaterial(prettyGreenM);
	std::shared_ptr<Plane> topPlane = std::make_shared<Plane>(Vector(0, 7, 0), Vector(0, -1, 0));
	topPlane->SetMaterial(yellowM);

	std::shared_ptr<Sphere> sphere1 = std::make_shared<Sphere>(0.5, Vector(-2, 0.5, 2.5));
	sphere1->SetMaterial(mirrorM);
	std::shared_ptr<Sphere> sphere2 = std::make_shared<Sphere>(0.5, Vector(-1, 0.5, -3));
	sphere2->SetMaterial(mirrorM);
	std::shared_ptr<Sphere> sphere3 = std::make_shared<Sphere>(0.6, Vector(3.5, 0.6, 4));
	sphere3->SetMaterial(mirrorM);
	std::shared_ptr<Sphere> sphere4 = std::make_shared<Sphere>(0.8, Vector(sphere1->GetCenter().x + 1.5, 0.8, sphere1->GetCenter().z + 5.5));
	sphere4->SetMaterial(maroonM);
	std::shared_ptr<Sphere> sphere5 = std::make_shared<Sphere>(0.4, Vector(floorPlane->GetCenter().x + 2, 0.4, floorPlane->GetCenter().z));
	sphere5->SetMaterial(mirrorM);
	std::shared_ptr<Sphere> sphere6 = std::make_shared<Sphere>(1, Vector(1.5, 3, 0.5));
	sphere6->SetMaterial(mirrorM);

	std::shared_ptr<Disk> disk1 = std::make_shared<Disk>(Vector(0, 4, 0), 1, Vector(0, 1, 0));
	disk1->SetMaterial(maroonM);
	std::shared_ptr<Disk> disk2 = std::make_shared<Disk>(Vector(0, 3.5, 0), 2, Vector(0, 1, 0));
	disk2->SetMaterial(maroonM);
	std::shared_ptr<Disk> disk3 = std::make_shared<Disk>(Vector(0, 3, 0), 3, Vector(0, 1, 0));
	disk3->SetMaterial(maroonM);
	std::shared_ptr<Disk> disk4 = std::make_shared<Disk>(Vector(-2, 0.5, 0), 1, Vector(0, 1, 0));
	disk4->SetMaterial(maroonM);

	// Fix ray-box intersections
	std::shared_ptr<Box> box1 = std::make_shared<Box>(Vector(1, 0, 0), Vector(2, 2, 1));
	box1->SetMaterial(maroonM);

	std::vector<std::shared_ptr<Object>> sceneObjects;
	sceneObjects.push_back(sphere1);
	sceneObjects.push_back(sphere2);
	sceneObjects.push_back(sphere3);
	sceneObjects.push_back(sphere4);
	sceneObjects.push_back(sphere5);
	sceneObjects.push_back(sphere6);

	sceneObjects.push_back(box1);
	/*std::random_device rd;
	std::mt19937 gen(rd());
	std::uniform_real_distribution<> dis(0, 1);
	uint32_t numSpheres = 2;
	gen.seed(0);
	for(uint32_t i = 0; i < numSpheres; ++i)
	{
	Vector randPos((0.5 - dis(gen)) * 10, (0.5 - dis(gen)) * 10, (0.5 + dis(gen) * 10));
	float randRadius = (0.5 + dis(gen) * 0.5);
	std::shared_ptr<Object> obj = std::make_shared<Sphere>(randRadius, randPos);
	obj->SetColor(maroonM);
	sceneObjects.push_back(obj);
	}*/


	//sceneObjects.push_back(disk1);
	//sceneObjects.push_back(disk2);
	//sceneObjects.push_back(disk3);
	sceneObjects.push_back(disk4);

	sceneObjects.push_back(floorPlane);
	sceneObjects.push_back(backPlane);
	sceneObjects.push_back(leftPlane);
	sceneObjects.push_back(rightPlane);
	sceneObjects.push_back(topPlane);

	return sceneObjects;
}

std::vector<std::shared_ptr<Light>> Scene::InitLightSources()
{
	std::vector<std::shared_ptr<Light>> lightSources;
	Vector light1Position(4, 3, 2);
	std::shared_ptr<Light> light1 = std::make_shared<Light>(light1Position, white, 1);
	std::shared_ptr<Light> light2 = std::make_shared<Light>(Vector(-4, 4, light1Position.z - 3), white, 1);
	std::shared_ptr<Light> light3 = std::make_shared<Light>(Vector(0, 5, 8), white, 1.4);

	lightSources.push_back(light1);
	lightSources.push_back(light2);
	lightSources.push_back(light3);

	return lightSources;
}