#include "Scene.h"

std::vector<std::shared_ptr<Object>> Scene::InitObjects()
{
	sceneObjects.reserve(15000);
	std::shared_ptr<TriangleMesh> triMesh = std::make_shared<TriangleMesh>("obj/bunny.obj");
	triMesh->material = orangeM;

	std::shared_ptr<Plane> floorPlane = std::make_shared<Plane>(Vector3d(0, 0, 0), Vector3d(0, 1, 0));
	floorPlane->material = tileFloorM;
	std::shared_ptr<Plane> topPlane = std::make_shared<Plane>(Vector3d(0, 10, 0), Vector3d(0, -1, 0));
	topPlane->material = blueM;
	std::shared_ptr<Plane> backPlane = std::make_shared<Plane>(Vector3d(0, 0, 10), Vector3d(0, 0, -1));
	backPlane->material = orangeM;
	std::shared_ptr<Plane> behindPlane = std::make_shared<Plane>(Vector3d(0, 0, -12), Vector3d(0, 0, 1));
	behindPlane->material = prettyGreenM;
	std::shared_ptr<Plane> leftPlane = std::make_shared<Plane>(Vector3d(-12, 0, 0), Vector3d(1, 0, 0));
	leftPlane->material = yellowM;
	std::shared_ptr<Plane> rightPlane = std::make_shared<Plane>(Vector3d(12, 0, 0), Vector3d(-1, 0, 0));
	rightPlane->material = maroonM;

	std::shared_ptr<Sphere> sphere1 = std::make_shared<Sphere>(0.5, Vector3d(1, 0.5, -2.5));
	sphere1->material = maroonM;
	std::shared_ptr<Sphere> sphere2 = std::make_shared<Sphere>(1.3, Vector3d(-3.2, 1.3, -2.2));
	sphere2->material = mirrorM;
	std::shared_ptr<Sphere> sphere3 = std::make_shared<Sphere>(0.4, Vector3d(sphere1->GetCenter().x - 1.6, sphere1->GetCenter().y + 1.2, sphere1->GetCenter().z + 1.7));
	sphere3->material = silverM;
	std::shared_ptr<Sphere> sphere4 = std::make_shared<Sphere>(0.2, Vector3d(sphere1->GetCenter().x - 1, sphere1->GetCenter().y + 1.8, sphere1->GetCenter().z + 1.2));
	sphere4->material = blueM;
	std::shared_ptr<Sphere> sphere5 = std::make_shared<Sphere>(0.6, Vector3d(floorPlane->GetCenter().x + 1.5, 1.3, floorPlane->GetCenter().z - 1));
	sphere5->material = mirrorM;
	std::shared_ptr<Sphere> sphere6 = std::make_shared<Sphere>(0.35, Vector3d(floorPlane->GetCenter().x + 0.25, floorPlane->GetCenter().y + 1, floorPlane->GetCenter().z + 4));
	sphere6->material = glassM;
	std::shared_ptr<Sphere> sphere7 = std::make_shared<Sphere>(0.4, Vector3d(sphere2->GetCenter().x + 0.55, sphere1->GetCenter().y + 2, sphere1->GetCenter().z + 7));
	sphere7->material = transparentM;
	std::shared_ptr<Sphere> sphere8 = std::make_shared<Sphere>(0.5, Vector3d(floorPlane->GetCenter().x - 2.1, 0.5, floorPlane->GetCenter().z + 0.5));
	sphere8->material = mirrorM;

	std::shared_ptr<Disk> disk1 = std::make_shared<Disk>();
	disk1->material = waterM;

	std::shared_ptr<Triangle> triangle1 = std::make_shared<Triangle>(Vector3d(-1, -1, -2), Vector3d(-1, 2, -2), Vector3d(0, -1, -2.7));
	triangle1->material = prettyGreenM;

	std::shared_ptr<Triangle> triangle2 = std::make_shared<Triangle>(Vector3d(0, -1, -4), Vector3d(2, 3, -4), Vector3d(2, -1, -4));
	triangle2->material = prettyGreenM;

	std::shared_ptr<Box> box1 = std::make_shared<Box>(Vector3d(0.3), Vector3d(0.7, 0.7, 1));
	box1->material = orangeM;
	std::shared_ptr<Box> box2 = std::make_shared<Box>(Vector3d(0, -1, -5), Vector3d(1, 0.5, -6));
	box2->material = orangeM;

	//sceneObjects.emplace_back(box1);
	//sceneObjects.emplace_back(box2);

	//sceneObjects.emplace_back(disk1);
	//sceneObjects.emplace_back(sphere1);
	//sceneObjects.emplace_back(triangle1);
	//sceneObjects.emplace_back(triMesh);
	sceneObjects.emplace_back(triMesh);
	//sceneObjects.emplace_back(triangle2);
	sceneObjects.emplace_back(sphere2);
	//sceneObjects.emplace_back(sphere3);
	//sceneObjects.emplace_back(sphere4);
	sceneObjects.emplace_back(sphere5);
	//sceneObjects.emplace_back(sphere6);
	//sceneObjects.emplace_back(sphere7);
	//sceneObjects.emplace_back(sphere8);
	sceneObjects.emplace_back(floorPlane);
	sceneObjects.emplace_back(topPlane);
	sceneObjects.emplace_back(backPlane);
	sceneObjects.emplace_back(behindPlane);
	sceneObjects.emplace_back(leftPlane);
	sceneObjects.emplace_back(rightPlane);

	return sceneObjects;
}

std::vector<std::shared_ptr<Light>> Scene::InitLightSources()
{
	lightSources.reserve(3);
	Vector3d light1Position(-2, 3, 1);
	Vector3d light2Position(0, 2, 3);
	std::shared_ptr<Light> light1 = std::make_shared<Light>(light1Position, Color(255), 1.5, Light::POINT);
	std::shared_ptr<Light> light2 = std::make_shared<Light>(light2Position, Color(255), 1.5, Light::POINT);
	std::shared_ptr<Light> light3 = std::make_shared<Light>(light1Position, Color(0, 0, 255), 1, Light::POINT);
	lightSources.emplace_back(light1);
	lightSources.emplace_back(light2);
	//lightSources.emplace_back(light3);

	return lightSources;
}