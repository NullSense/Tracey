#define _SCL_SECURE_NO_WARNINGS

#include "bitmap_image.hpp"
#include "Globals.h"
#include "Sphere.h"
#include "Plane.h"
#include "Light.h"
#include "Material.h"
#include "Scene.h"
#include "Camera.h"
#include <vector>
#include <iostream>
#include <time.h>
#include <sstream>
#include <algorithm>

// Returns the closest object's index that the ray intersected with
int ClosestObjectIndex(const std::vector<FPType> &intersections)
{
	int minValueIndex = 0;

	// Prevent unnecessary calculations (only check the ones that intersect)
	if(intersections.size() == 0) // No intersections
		return -1;

	else if(intersections.size() == 1)
	{
		if(intersections[0] > 0) // If intersection is greater than 0, then it's our index of minimum value (0th element in vector)
			return 0;
		else // Otherwise the only intersection value is negative (ray missed everything)
			return -1;
	}
	else // If there's more than 1 intersection, find the MAX value
	{
		FPType max = 0;
		for(FPType i : intersections)
		{
			if(max < i)
				max = i;
		}
		if(max > 0)
		{
			// Only searh for positive intersections
			// Find the minimum POSITIVE value
			for(unsigned intersectionIndex = 0; intersectionIndex < intersections.size(); intersectionIndex++)
			{
				// If intersection is positive and is lower or equal to the max intersection
				if(intersections[intersectionIndex] > 0 && intersections[intersectionIndex] <= max)
				{
					max = intersections[intersectionIndex];
					minValueIndex = intersectionIndex;
				}
			}
			return minValueIndex;
		}
		else
		{
			// All intersections were negative (didn't hit shit)
			return -1;
		}
	}
}

// Get the color of the pixel at the ray-object intersection point
Color GetColorAt(Vector point, Vector sceneDirection, const std::vector<std::shared_ptr<Object>> &sceneObjects, int indexOfClosestObject,
				 const std::vector<std::shared_ptr<Light>> &lightSources)
{
	Material closestObjectMaterial = sceneObjects[indexOfClosestObject]->GetMaterial();
	Vector closestObjectNormal = sceneObjects[indexOfClosestObject]->GetNormalAt(point);

	// Checkerboard pattern floor
	if(closestObjectMaterial.GetSpecial() == 2)
	{
		unsigned square = int(floor(point.x)) + int(floor(point.z)); // (floor() rounds down)
		if(square % 2 == 0) // black tile
			closestObjectMaterial.SetColor(Color(0, 0, 0));
		else // white tile
			closestObjectMaterial.SetColor(Color(255, 255, 255));
	}

	bool shadowed = false;
	Color finalColor;
	Color ambient;
	Color diffusive;
	FPType lambertian;
	FPType phong;
	Color specular;

	// Reflection & Refraction
	if(closestObjectMaterial.GetReflection() > 0 && closestObjectMaterial.GetRefraction() > 0 && REFLECTIONS_ON && REFRACTIONS_ON)
	{
	}
	// Reflective
	if(closestObjectMaterial.GetReflection() > 0 && REFLECTIONS_ON)
	{
	}
	if(AMBIENT_ON)
	{
		ambient =  closestObjectMaterial.GetColor() * AMBIENT_LIGHT * closestObjectMaterial.GetAmbient();
		finalColor += ambient;
	}
	// Diffuse
	if(DIFFUSE_ON)
	{
		for(const auto &lightSource : lightSources)
		{
			Vector lightDir = (lightSource->GetPosition() - point).Normalize(); // Calculate the directional vector towards the lightSource
			lambertian = closestObjectNormal.Dot(lightDir);
			diffusive = closestObjectMaterial.GetColor() * closestObjectMaterial.GetDiffuse() * lightSource->GetIntensity() * std::fmax(lambertian, 0);
			finalColor += diffusive;

			if(lambertian > 0)
			{
				if(SHADOWS_ON)
				{
					Ray shadowRay(point, lightDir); // Cast a ray from the first intersection to the light

					std::vector<FPType> secondaryIntersections;
					for(const auto &sceneObject : sceneObjects)
					{
						secondaryIntersections.push_back(sceneObject->GetIntersection(shadowRay));
					}

					for(const auto &secondaryIntersection : secondaryIntersections)
					{
						if(secondaryIntersection >= TOLERANCE) // If shadow ray intersects with some object along the way
						{
							shadowed = true;
							finalColor *= closestObjectMaterial.GetDiffuse() * AMBIENT_LIGHT;
							break;
						}
					}
				}

				if(shadowed == false && SPECULAR_ON)
				{
					if(closestObjectMaterial.GetSpecular() > 0 && closestObjectMaterial.GetSpecular() <= 1)
					{
						Vector V = -sceneDirection;

						// Blinn-Phong
						Vector H = (lightDir + V).Normalize();
						FPType NdotH = closestObjectNormal.Dot(H);

						phong = pow(NdotH, 300);
						specular = lightSource->GetColor() * std::fmax(0, phong) * lightSource->GetIntensity(); // closestObjectMaterial.GetSpecular(); add or no?
						finalColor += specular;
						
						
						/*//PHONG
						Vector R = ((closestObjectNormal * lightDir.Dot(closestObjectNormal)) * 2) - lightDir;
						FPType RV = R.Dot(V);
						if(RV > 0)
						{
							phong = closestObjectMaterial.GetSpecular() * pow(RV, 300);
							specular = (lightSource->GetColor()) * (phong);
							finalColor += specular;
						}*/

					}
				}
			}
		}
	}

	return finalColor.Clip();
}

void Draw(bitmap_image &image, int &x, int &y, Camera &camera, int &indexOfClosestObject, 
		  std::vector<FPType> &intersections, std::vector<std::shared_ptr<Object>> &sceneObjects, std::vector<std::shared_ptr<Light>> &lightSources)
{
	// If it doesn't register a ray trace set that pixel to be black (ray missed everything)
	if(indexOfClosestObject == -1)
		image.set_pixel(x, y, 0, 0, 0);
	else // Ray hit an object
	{
		if(intersections[indexOfClosestObject] > TOLERANCE) // If intersection at that point > accuracy, get color of object
		{
			// If ray hit something, set point position to ray-object intersection
			Vector point((camera.GetOrigin() + (camera.GetSceneDirection() * intersections[indexOfClosestObject])));

			// Get the color of the intersection point (pixel)
			Color intersectionColor = GetColorAt(point, camera.GetSceneDirection(), sceneObjects, indexOfClosestObject, lightSources);

			image.set_pixel(x, y, unsigned char(intersectionColor.GetRed()), unsigned char(intersectionColor.GetGreen()), unsigned char(intersectionColor.GetBlue()));
		}
	}
}

void CalcIntersections()
{
	clock_t end, start = clock();
	bitmap_image image(WIDTH, HEIGHT);

	Camera camera(Vector(3, 3, -7), Vector(0, -1, 6));
	
	int columnsCompleted = 0;
	FPType percentage;
	
	FPType xCamOffset, yCamOffset; // Offset position of rays from the direction where camera is pointed (x & y positions)
	for(int x = 0; x < WIDTH; x++)
	{
		// Calculates % of render completed
		columnsCompleted++;
		percentage = columnsCompleted / (FPType) WIDTH * 100;
		std::cout << '\r' << "Completion: " << (int)percentage << '%';
		fflush(stdout);

		for(int y = 0; y < HEIGHT; y++)
		{
			// No Anti-aliasing
			if(WIDTH > HEIGHT)
			{
				xCamOffset = (((x + 0.5) / WIDTH) * ASPECT_RATIO) - ((WIDTH - HEIGHT) / HEIGHT) / 2;
				yCamOffset = (y + 0.5) / HEIGHT;
			}
			else if(HEIGHT > WIDTH)
			{
				xCamOffset = (x + 0.5) / WIDTH;
				yCamOffset = ((y + 0.5) / HEIGHT) / ASPECT_RATIO - ((HEIGHT - WIDTH) / (WIDTH / 2));
			}
			else
			{
				// Image is square
				xCamOffset = (x + 0.5) / WIDTH, HEIGHT;
				yCamOffset = (y + 0.5) / WIDTH, HEIGHT;
			}

			// Set up scene
			Scene scene;
			std::vector<std::shared_ptr<Object>> sceneObjects = scene.InitObjects();
			std::vector<std::shared_ptr<Light>> lightSources = scene.InitLightSources();

			std::vector<FPType> intersections;
			intersections.reserve(1024);
			//intersections.clear();

			// Camera direction for every ray shot through each pixel
			Vector camRayDir = (camera.GetCameraDirection() + camera.GetCamX() * (xCamOffset - 0.5) + camera.GetCamY() * (yCamOffset - 0.5)).Normalize();
			camera.SetSceneDirection(camRayDir);

			// Shoot ray into evey pixel of the image
			Ray camRay(camera.GetOrigin(), camera.GetSceneDirection());

			// Check if ray intersects with any scene objects
			for(const auto &sceneObject : sceneObjects)
			{
				intersections.push_back(sceneObject->GetIntersection(camRay));
			}

			// Check which object is closest to the camera
			int indexOfClosestObject = ClosestObjectIndex(intersections);
			Draw(image, x, y, camera, indexOfClosestObject, intersections, sceneObjects, lightSources);
		}
	}

	end = clock();
	FPType diff = ((FPType) end - (FPType) start) / CLOCKS_PER_SEC;
	std::cout << "\n\nResolution: " << WIDTH << "x" << HEIGHT << std::endl;
	std::cout << "Time: " << diff << " seconds" << std::endl;

	std::string saveString = "render.bmp";
	image.save_image(saveString);
	std::cout << "Output filename: " << saveString << std::endl;
}

int main()
{
	CalcIntersections();

	std::cout << "\nPress enter to exit...";
	std::cin.ignore();

	return 0;
}