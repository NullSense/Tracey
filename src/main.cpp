#define _SCL_SECURE_NO_WARNINGS

#include "bitmap_image.hpp"
#include "Globals.h"
#include "Sphere.h"
#include "Plane.h"
#include "Light.h"
#include <vector>
#include <iostream>
#include <time.h>

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
	Color closestObjectColor = sceneObjects[indexOfClosestObject]->color;
	Vector closestObjectNormal = sceneObjects[indexOfClosestObject]->GetNormalAt(intersectionRayPos);

	if(closestObjectColor.special == 2) // Checkerboard pattern floor
	{
		int square = int(floor(intersectionRayPos.x)) + int(floor(intersectionRayPos.z)); // (floor() rounds down)

		if(square % 2 == 0) // black tile
		{
			closestObjectColor.red = 0;
			closestObjectColor.green = 0;
			closestObjectColor.blue = 0;
		}
		else // white tile
		{
			closestObjectColor.red = 255;
			closestObjectColor.green = 255;
			closestObjectColor.blue = 255;
		}
	}

	bool shadowed = false;
	Color finalColor = closestObjectColor.Scalar(AMBIENTLIGHT); // Add ambient light to the calculation
	for(const auto &lightSource : lightSources)
	{
		Vector lightDir = (lightSource->position - intersectionRayPos).Normalize(); // Calculate the directional vector towards the lightSource
		FPType cosineAngle = closestObjectNormal.Dot(lightDir);
		finalColor = finalColor.Scalar(cosineAngle);
		if(cosineAngle > 0)
		{

			Ray shadowRay(intersectionRayPos, (lightSource->position - intersectionRayPos).Normalize()); // Cast a ray from the first intersection to the light

			std::vector<FPType> secondaryIntersections;
			for(const auto &sceneObject : sceneObjects)
			{
				secondaryIntersections.push_back(sceneObject->GetIntersection(shadowRay));
			}

			Vector distanceToLight = lightSource->position + (intersectionRayPos.Negative()).Normalize();
			FPType distanceToLightMagnitude = distanceToLight.Magnitude();

			for(const auto &secondaryIntersection : secondaryIntersections)
			{
				if(secondaryIntersection > TOLERANCE)
				{
					if(secondaryIntersection <= distanceToLightMagnitude)
					{
						shadowed = true;
						finalColor = finalColor.Scalar(cosineAngle);
					}
					break;
				}
			}
		}

	}
	return finalColor.Clip();

	//if(closestObjectColor.special > 0 && closestObjectColor.special <= 1) // Phong illumination
	//{
	//}
}

int main()
{
	clock_t end, start = clock();
	bitmap_image image(WIDTH, HEIGHT);
	std::cout << "Rendering..." << std::endl;

	Vector camPos(0, 1, -2);
	Vector lookAt(0, -1, 4);

	Vector camDiff = camPos - lookAt;
	Vector camDir = camDiff.Negative().Normalize();
	Vector camRight = Vector(0, 1, 0).Cross(camDir).Normalize();
	Vector camDown = camRight.Cross(camDir);

	Color whiteLight(255, 255, 255, 0);
	Color prettyGreen(128, 255, 128, 0.5);
	Color maroon(128, 64, 64, 0);
	Color tileFloor(255, 255, 255, 2);
	Color gray(128, 128, 128, 0);
	Color black(0, 0, 0, 0);
	Color pureRed(255, 0, 0, 0);

	// Position, distance, normal, color 
	Plane plane(Vector(0, -1, 0), 1, Vector(0, 1, 0), tileFloor);
	// To place sphere on top of plane: (0 - sphere radius)
	Sphere sphere1(0.5f, Vector(-1, -0.5, 2.5), maroon);
	Sphere sphere2(0.3f, Vector(1, -0.3, 1), prettyGreen);

	// Contains position and color values
	std::vector<Light*> lightSources;
	Vector light1Position(plane.center.x - 2.5, plane.center.y + 1.5, plane.center.z + 1.6);
	Light light1(light1Position, whiteLight);
	Light light2(Vector(light1Position.x + 6, light1Position.y, light1Position.z - 1), whiteLight);
	lightSources.push_back(&light1);
	//lightSources.push_back(&light2);

	// To see where the light is positioned

	// Holds all scene objects
	std::vector<Object*> sceneObjects;
	sceneObjects.push_back(&sphere1);
	sceneObjects.push_back(&sphere2);
	sceneObjects.push_back(&plane);

	std::vector<FPType> intersections;
	intersections.reserve(1024);

	FPType xCamOffset, yCamOffset; // Offset position of rays from the direction where camera is pointed (x & y positions)

	for(int x = 0; x < WIDTH; x++)
	{
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
					Vector intersectionRayPos = camera.origin + (camRayDir * intersections[indexOfClosestObject]);
					Vector intersectionRayDir = camRayDir;
					// If registers a ray trace, set pixel color to traced pixel color (the object color)
					Color intersectionColor = GetColorAt(intersectionRayPos, intersectionRayDir, sceneObjects, indexOfClosestObject, lightSources);
					image.set_pixel(x, y, intersectionColor.red, intersectionColor.green, intersectionColor.blue);
				}
			}
		}
	}

	image.save_image("output.bmp");
	end = clock();
	FPType diff = ((FPType) end - (FPType) start) / CLOCKS_PER_SEC;

	std::cout << "Render complete in: " << diff << " seconds" << std::endl;
	//std::cout << "Press enter to exit...";
	//std::cin.ignore();

	return 0;
}