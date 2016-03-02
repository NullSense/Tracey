#include "Scene.h"

std::vector<Object*> Scene::InitObjects()
{
	Plane floorPlane(Vector(0, -1, 0), Vector(0, 1, 0));
	floorPlane.SetMaterial(tileFloor);

	Sphere sphere1(0.5, Vector(1, -0.5, 2.5));
	sphere1.SetMaterial(maroonM);
	Sphere sphere2(0.5, Vector(-1.5, -0.5, 4));
	sphere2.SetMaterial(prettyGreen);
	Sphere sphere3(0.2, Vector(sphere1.GetPosition().x - 2, sphere1.GetPosition().y, sphere1.GetPosition().z - 2));
	sphere3.SetMaterial(blueM);
	Sphere sphere4(0.2, Vector(sphere1.GetPosition().x - 0.8, sphere1.GetPosition().y + 0.4, sphere1.GetPosition().z - 0.67));
	sphere4.SetMaterial(silver);
	Sphere sphere5(0.4, Vector(floorPlane.GetCenter().x - 3.5, -0.6, floorPlane.GetCenter().z + 2.9));
	sphere5.SetMaterial(orangeM);

	std::vector<Object*> sceneObjects;
	sceneObjects.push_back(&sphere1);
	sceneObjects.push_back(&sphere2);
	sceneObjects.push_back(&sphere3);
	sceneObjects.push_back(&sphere4);
	sceneObjects.push_back(&sphere5);
	sceneObjects.push_back(&floorPlane);

	return sceneObjects;
}

std::vector<Light*> Scene::InitLightSources()
{
	std::vector<Light*> lightSources;
	Vector light1Position(- 2.5, 3, 0.6);
	Light light1(light1Position, white);
	Light light2(Vector(light1Position.x, light1Position.y, light1Position.z), white);
	lightSources.push_back(&light1);
	//lightSources.push_back(&light2);

	return lightSources;
}
