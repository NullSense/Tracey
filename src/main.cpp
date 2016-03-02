#define _SCL_SECURE_NO_WARNINGS

#include "bitmap_image.hpp"
#include "Globals.h"
#include "Sphere.h"
#include "Plane.h"
#include "Light.h"
#include "Material.h"
#include "Vector.h"
#include <vector>
#include <iostream>
#include <time.h>
#include <sstream>

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

Color GetColorAt(Vector intersectionRayPos, Vector intersectingRayDir, const std::vector<Object*> &sceneObjects, int indexOfClosestObject, const std::vector<Light*> &lightSources)
{
	Material closestObjectMaterial = sceneObjects[indexOfClosestObject]->GetMaterial();
	Vector closestObjectNormal = sceneObjects[indexOfClosestObject]->GetNormalAt(intersectionRayPos);

	if(closestObjectMaterial.GetSpecial() == 2) // Checkerboard pattern floor
	{
		int square = int(floor(intersectionRayPos.x)) + int(floor(intersectionRayPos.z)); // (floor() rounds down)
		if(square % 2 == 0) // black tile
			closestObjectMaterial.SetColor(Color(0, 0, 0));
		else // white tile
			closestObjectMaterial.SetColor(Color(255, 255, 255));
	}

	bool shadowed = false;
	Color finalColor = closestObjectMaterial.GetColor() * AMBIENT_LIGHT; // Add ambient light to the calculation

	// Reflections
	if(REFLECTIONS_ON)
	{
		if(closestObjectMaterial.GetSpecular() > 0 && closestObjectMaterial.GetSpecular() <= 1)
		{
			Vector scalar = closestObjectNormal * (closestObjectNormal.Dot(intersectingRayDir.Negative()));
			Vector resultantReflection = intersectingRayDir.Negative() + ((scalar + (intersectingRayDir)) * 2);
			Vector reflectionDirection = resultantReflection.Normalize();

			Vector offset = reflectionDirection * 0.001; // Offset is added to cancel out the grainyness effect in the reflections

			Ray reflectionRay(intersectionRayPos + offset, resultantReflection);

			// determine what the ray intersects with first
			std::vector<FPType> reflectionIntersections;
			for(auto sceneObject : sceneObjects)
			{
				reflectionIntersections.push_back(sceneObject->GetIntersection(reflectionRay));
			}

			int closestObjectWithReflection = ClosestObjectIndex(reflectionIntersections);

			if(closestObjectWithReflection != -1 && closestObjectWithReflection != indexOfClosestObject) // Depth checking
			{
				// reflection ray missed everthing else
				if(reflectionIntersections[closestObjectWithReflection] > TOLERANCE)
				{
					// determine the position and direction at the point of intersection with the reflection ray
					// the ray only affects the color if it reflected off something
					Vector reflectionIntersectionPosition = intersectionRayPos + (resultantReflection * (reflectionIntersections[closestObjectWithReflection]));
					Vector reflectionIntersectionRayDirection = resultantReflection;
					Color reflectionIntersectionColor = GetColorAt(reflectionIntersectionPosition, reflectionIntersectionRayDirection, sceneObjects, closestObjectWithReflection, lightSources);
					finalColor += (reflectionIntersectionColor * closestObjectMaterial.GetReflection());
				}
			}
		}
	}

	for(const auto &lightSource : lightSources)
	{
		Vector lightDir = (lightSource->GetPosition() - intersectionRayPos).Normalize(); // Calculate the directional vector towards the lightSource
		FPType cosineAngle = closestObjectNormal.Dot(lightDir);
		
		// Diffuse shading
		if(DIFFUSE_ON)
		{
			finalColor *= cosineAngle * AMBIENT_LIGHT;
		}
		if(cosineAngle > 0)
		{
			// Shadows
			if(SHADOWS_ON) 
			{
				Ray shadowRay(intersectionRayPos, (lightSource->GetPosition() - intersectionRayPos).Normalize()); // Cast a ray from the first intersection to the light

				std::vector<FPType> secondaryIntersections;
				for(const auto &sceneObject : sceneObjects)
				{
					secondaryIntersections.push_back(sceneObject->GetIntersection(shadowRay));
				}

				for(const auto &secondaryIntersection : secondaryIntersections)
				{
					if(secondaryIntersection > TOLERANCE)
					{
						// Shadows
						shadowed = true;
						finalColor *= closestObjectMaterial.GetDiffuse() * AMBIENT_LIGHT;
						break;
					}
				}
			}
			// Specular intensity / Phong illumination
			if(shadowed == false && SPECULAR_ON)
			{
				if(closestObjectMaterial.GetSpecular() > 0 && closestObjectMaterial.GetSpecular() <= 1)
				{ 
					Vector scalar1 = closestObjectNormal * (closestObjectNormal.Dot(intersectingRayDir.Negative()));
					Vector resultantReflection = intersectingRayDir.Negative() + ((scalar1 + (intersectingRayDir)) * 2);

					FPType specular = resultantReflection.Dot(lightDir);
					if(specular > 0)
					{
						// pow(specular, shininess factor (higher shine = more condensed phong light)) 
						specular = pow(specular, 120) * closestObjectMaterial.GetSpecular();
						finalColor += (lightSource->GetMaterial().GetColor() * AMBIENT_LIGHT) * (specular * closestObjectMaterial.GetSpecular());
					}
				}
			}
		}
	}
	return finalColor.Clip();
}

int main()
{
	clock_t end, start = clock();
	bitmap_image image(WIDTH, HEIGHT);

	Vector camPos(0, 1, -2);
	//Vector camPos(0, 0, -2);
	Vector lookAt(0, -1, 4);

	Vector camDiff = camPos - lookAt;
	Vector camDir = camDiff.Negative().Normalize();
	Vector camRight = Vector(0, 1, 0).Cross(camDir).Normalize();
	Vector camDown = camRight.Cross(camDir);

	Color blue(0, 255, 255);
	Color maroon(128, 64, 64);
	Color gray(128, 128, 128);
	Color orange(245, 77, 15);

	// Color, diffusion [0-1] (lower = more intense phong illumination), reflection, special (tile floor)
	Material tileFloor(Color(255, 255, 255), 0.2, 1, 2);
	Material whiteLight(Color(255, 255, 255));
	Material prettyGreen(Color(128, 255, 128), 0.2, 1);
	Material blueM(blue, 0, 0);
	Material silver(gray, 0, 1);
	Material orangeM(orange, 0.8, 1);
	Material maroonM(maroon, 0.5, 1);

	// Position, distance, normal, color 
	Plane floorPlane(Vector(0, -1, 0), Vector(0, 1, 0));
	floorPlane.SetMaterial(tileFloor);

	// To place sphere on top of plane: (-1 + sphere radius)
	Sphere sphere1(0.5, Vector(1, -0.5, 2.5));
	sphere1.SetMaterial(maroonM);
	Sphere sphere2(0.5, Vector(-1.5, -0.5, 4));
	sphere2.SetMaterial(prettyGreen);
	Sphere sphere3(0.2, Vector(sphere1.position.x - 2, sphere1.position.y, sphere1.position.z - 2));
	sphere3.SetMaterial(blueM);
	Sphere sphere4(0.2, Vector(sphere1.position.x - 0.8, sphere1.position.y + 0.4, sphere1.position.z - 0.67));
	sphere4.SetMaterial(silver);
	Sphere sphere5(0.4, Vector(floorPlane.center.x - 3.5, -0.6, floorPlane.center.z + 2.9));
	sphere5.SetMaterial(orangeM);

	// Contains position and color values (currently only 1 light source works, 2 = bugs)
	std::vector<Light*> lightSources;
	Vector light1Position(floorPlane.center.x - 2.5, floorPlane.center.y + 2, floorPlane.center.z + 0.6);
	Light light1(light1Position, whiteLight);
	Light light2(Vector(light1Position.x + 6, light1Position.y, light1Position.z - 1), whiteLight);
	lightSources.push_back(&light1);
	//lightSources.push_back(&light2); 

	// Holds all scene objects
	std::vector<Object*> sceneObjects;
	sceneObjects.push_back(&sphere1);
	sceneObjects.push_back(&sphere2);
	sceneObjects.push_back(&sphere3);
	sceneObjects.push_back(&sphere4);
	sceneObjects.push_back(&sphere5);
	sceneObjects.push_back(&floorPlane);

	std::vector<FPType> intersections;
	intersections.reserve(1024);

	int columnsCompleted = 0;
	int raysCast = 0;
	FPType percentage;
	FPType xCamOffset, yCamOffset; // Offset position of rays from the direction where camera is pointed (x & y positions)
	for(int x = 0; x < WIDTH; x++)
	{
		// Calculates % of render completed
		columnsCompleted++;
		percentage = columnsCompleted / (FPType) WIDTH * 100;
		std::cout << '\r' << "Completion: " << (int) percentage << '%';
		fflush(stdout);

		for(int y = 0; y < HEIGHT; y++)
		{
			// No Anti-aliasing
			if(WIDTH > HEIGHT)
			{
				xCamOffset = ((x + 0.5) / WIDTH) * ASPECT_RATIO - (WIDTH - HEIGHT) / HEIGHT / 2;
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
				xCamOffset = (x + 0.5) / WIDTH;
				yCamOffset = (y + 0.5) / HEIGHT;
			}
			Vector camRayDir = (camDir + camRight * (xCamOffset - 0.5) + camDown * (yCamOffset - 0.5)).Normalize();
			Ray camera(camPos, camRayDir);

			intersections.clear();

			// Check if ray intersects with any scene objects
			for(const auto &sceneObject : sceneObjects)
			{
				intersections.push_back(sceneObject->GetIntersection(camera));
			}
			// Check which object is closest to the camera
			int indexOfClosestObject = ClosestObjectIndex(intersections);

			if(indexOfClosestObject == -1)
			{
				// If it doesn't register a ray trace set that pixel to be black
				image.set_pixel(x, y, 0, 0, 0);
			}
			else
			{
				// If intersection at that point > accuracy, get color of object
				if(intersections[indexOfClosestObject] > TOLERANCE)
				{
					raysCast++;
					Vector intersectionRayPos = camera.origin + (camRayDir * intersections[indexOfClosestObject]);
					Vector intersectionRayDir = camRayDir;
					// If registers a ray trace, set pixel color to traced pixel color (the object color)
					Color intersectionColor = GetColorAt(intersectionRayPos, intersectionRayDir, sceneObjects, indexOfClosestObject, lightSources);
					image.set_pixel(x, y, intersectionColor.red, intersectionColor.green, intersectionColor.blue);
				}
			}
		}
	}

	end = clock();
	FPType diff = ((FPType) end - (FPType) start) / CLOCKS_PER_SEC;

	std::string saveString = "render.bmp";
	image.save_image(saveString);

	std::cout << "\n\nRays cast: " << raysCast << std::endl;
	std::cout << "Resolution: " << WIDTH << "x" << HEIGHT << std::endl;
	std::cout << "Time: " << diff << " seconds" << std::endl;
	std::cout << "Output filename: " << saveString << std::endl;
	std::cout << "\nPress enter to exit...";
	std::cin.ignore();

	return 0;
}
