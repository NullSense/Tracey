#include "Scene.h"

std::vector<std::shared_ptr<Object>> Scene::InitObjects()
{
	//sceneObjects.reserve(50);
	std::shared_ptr<Plane> floorPlane = std::make_shared<Plane>(Vector3(0, -1, 0), Vector3(0, 1, 0));
	floorPlane->SetMaterial(tileFloorM);
	std::shared_ptr<Plane> topPlane = std::make_shared<Plane>(Vector3(0, 10, 0), Vector3(0, -1, 0));
	topPlane->SetMaterial(blueM);
	std::shared_ptr<Plane> backPlane = std::make_shared<Plane>(Vector3(0, 0, 15), Vector3(0, 0, -1));
	backPlane->SetMaterial(orangeM);
	std::shared_ptr<Plane> behindPlane = std::make_shared<Plane>(Vector3(0, 0, -15), Vector3(0, 0, 1));
	behindPlane->SetMaterial(prettyGreenM);

	std::shared_ptr<Sphere> sphere1 = std::make_shared<Sphere>(0.5, Vector3(1, -0.5, -2.5));
	sphere1->SetMaterial(maroonM);
	std::shared_ptr<Sphere> sphere2 = std::make_shared<Sphere>(1.3, Vector3(-1, 0.3, -4));
	sphere2->SetMaterial(mirrorM);
	std::shared_ptr<Sphere> sphere3 = std::make_shared<Sphere>(0.4, Vector3(sphere1->GetCenter().x - 1.6, sphere1->GetCenter().y + 0.2, sphere1->GetCenter().z + 1.7));
	sphere3->SetMaterial(silverM);
	std::shared_ptr<Sphere> sphere4 = std::make_shared<Sphere>(0.2, Vector3(sphere1->GetCenter().x - 1, sphere1->GetCenter().y + 0.4, sphere1->GetCenter().z + 1.2));
	sphere4->SetMaterial(blueM);
	std::shared_ptr<Sphere> sphere5 = std::make_shared<Sphere>(0.6, Vector3(floorPlane->GetCenter().x - 4, 0, floorPlane->GetCenter().z - 5));
	sphere5->SetMaterial(waterM);
	std::shared_ptr<Sphere> sphere6 = std::make_shared<Sphere>(0.35, Vector3(sphere2->GetCenter().x + 0.45, sphere1->GetCenter().y + 0.6, sphere1->GetCenter().z + 5.5));
	sphere6->SetMaterial(glassM);
	std::shared_ptr<Sphere> sphere7 = std::make_shared<Sphere>(0.4, Vector3(sphere2->GetCenter().x + 0.55, sphere1->GetCenter().y + 1, sphere1->GetCenter().z + 7));
	sphere7->SetMaterial(transparentM);
	std::shared_ptr<Sphere> sphere8 = std::make_shared<Sphere>(0.5, Vector3(floorPlane->GetCenter().x - 2.1, -0.5, floorPlane->GetCenter().z + 0.5));
	sphere8->SetMaterial(mirrorM);

	std::shared_ptr<Disk> disk1 = std::make_shared<Disk>();
	disk1->SetMaterial(waterM);

	std::shared_ptr<Triangle> triangle1 = std::make_shared<Triangle>(Vector3(-1.5, -1, 0), Vector3(-2.5, 2, 0), Vector3(-2.5, -1, -0.2));
	triangle1->SetMaterial(prettyGreenM);

	std::shared_ptr<Triangle> triangle2 = std::make_shared<Triangle>(Vector3(0, -1, -4), Vector3(2, 3, -4), Vector3(2, -1, -4));
	triangle2->SetMaterial(prettyGreenM);

	std::shared_ptr<Box> box1 = std::make_shared<Box>(Vector3(0.3), Vector3(0.7, 0.7, 1));
	box1->SetMaterial(orangeM);
	std::shared_ptr<Box> box2 = std::make_shared<Box>(Vector3(0, -1, -5), Vector3(1, 0.5, -6));
	box2->SetMaterial(orangeM);

	//sceneObjects.emplace_back(box1);
	//sceneObjects.emplace_back(box2);

	//sceneObjects.emplace_back(disk1);
	sceneObjects.emplace_back(sphere1);
	//sceneObjects.emplace_back(triangle1);
	//sceneObjects.emplace_back(triangle2);
	sceneObjects.emplace_back(sphere2);
	//sceneObjects.emplace_back(sphere3);
	sceneObjects.emplace_back(sphere4);
	sceneObjects.emplace_back(sphere5);
	sceneObjects.emplace_back(sphere6);
	sceneObjects.emplace_back(sphere7);
	sceneObjects.emplace_back(sphere8);
	sceneObjects.emplace_back(floorPlane);
	sceneObjects.emplace_back(topPlane);
	sceneObjects.emplace_back(backPlane);
	sceneObjects.emplace_back(behindPlane);

	return sceneObjects;
}

std::vector<std::shared_ptr<Light>> Scene::InitLightSources()
{
	//lightSources.reserve(5);
	Vector3 light1Position(-2.5, 1, 1);
	Vector3 light2Position(2.5, 2, -4.6);
	std::shared_ptr<Light> light1 = std::make_shared<Light>(light1Position, Color(255), 1.5, Light::POINT);
	std::shared_ptr<Light> light2 = std::make_shared<Light>(light2Position, Color(255), 1.5, Light::POINT);
	std::shared_ptr<Light> light3 = std::make_shared<Light>(light1Position, Color(0, 0, 255), 1, Light::POINT);
	lightSources.emplace_back(light1);
	lightSources.emplace_back(light2);
	//lightSources.emplace_back(light3);

	return lightSources;
}