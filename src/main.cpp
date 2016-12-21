#define _SCL_SECURE_NO_WARNINGS

#include "bitmap_image.hpp"
#include "Globals.h"
#include "Light.h"
#include "Material.h"
#include "Scene.h"
#include "Camera.h"
#include <vector>
#include <iostream>
#include <time.h>
#include <sstream>
#include <algorithm>
#include <thread>

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
			// All intersections were negative (didn't hit anything)
			return -1;
		}
	}
}

// Forward declare for GetReflections()
Color GetColorAt(Vector &point, Vector &sceneDirection, const std::vector<std::shared_ptr<Object>> &sceneObjects, unsigned indexOfClosestObject,
				 const std::vector<std::shared_ptr<Light>> &lightSources);

// Calculate reflections
Color GetReflections(Material &closestObjectMaterial, Vector &closestObjectNormal, Vector &sceneDirection, const std::vector<std::shared_ptr<Object>> &sceneObjects, int indexOfClosestObject, Vector &point, const std::vector<std::shared_ptr<Light>> &lightSources)
{
	if(closestObjectMaterial.GetReflection() > 0 && REFLECTIONS_ON)
	{
		if(closestObjectMaterial.GetSpecular() > 0 && closestObjectMaterial.GetSpecular() <= 1)
		{
			FPType nDotV = closestObjectNormal.Dot(-sceneDirection);

			Vector resultantReflection = (closestObjectNormal * nDotV * 2) - (-sceneDirection);
			Vector reflectionDirection = resultantReflection.Normalize();
			Vector offset = reflectionDirection * 0.001; // The rays that start from reflecting object A are considered hitting itself, since it's the nearest object from the ray start position

			Ray reflectionRay(point + offset, resultantReflection);

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
					Vector reflectionIntersectionPosition = point + (resultantReflection * (reflectionIntersections[closestObjectWithReflection]));
					Vector reflectionIntersectionRayDirection = resultantReflection;
					Color reflectionIntersectionColor = GetColorAt(reflectionIntersectionPosition, reflectionIntersectionRayDirection, sceneObjects, closestObjectWithReflection, lightSources) * closestObjectMaterial.GetReflection();
					return reflectionIntersectionColor;
				}
			}
		}
	}
}

// Get the color of the pixel at the ray-object intersection point
Color GetColorAt(Vector &point, Vector &sceneDirection, const std::vector<std::shared_ptr<Object>> &sceneObjects, unsigned indexOfClosestObject,
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

	Color finalColor;
	Color ambient;
	Color diffuse;
	FPType lambertian;
	FPType phong;
	Color specular;

	// Shadows, Diffuse, Specular
	for(const auto &lightSource : lightSources)
	{
		bool shadowed = false;
		Vector lightDir;
		if(lightSource->POINT)
			lightDir = (lightSource->GetPosition() - point); // Calculate the directional vector towards the lightSource

		/*if(lightSource->AREA)
		{
			Vector newLocation;
			newLocation.x = position.x + radius * (2.0 * rand_float() - 1.0);
			return (newLocation - point).Normalize();
		}*/

		FPType distance = lightDir.Magnitude();
		lightDir = lightDir.Normalize();
		lambertian = closestObjectNormal.Dot(lightDir);

		// Shadows
		if(SHADOWS_ON && lambertian > 0)
		{

			Ray shadowRay(point, lightDir); // Cast a ray from the first intersection to the light

			std::vector<FPType> secondaryIntersections;
			for(const auto &sceneObject : sceneObjects)
			{
				secondaryIntersections.push_back(sceneObject->GetIntersection(shadowRay));
			}

			for(const auto &secondaryIntersection : secondaryIntersections)
			{
				if(secondaryIntersection > TOLERANCE) // If shadow ray intersects with some object along the way
				{
					if(secondaryIntersection <= distance)
					{
						shadowed = true;
						break;
					}
				}
			}
		}

		// Diffuse
		if(DIFFUSE_ON && shadowed == false)
		{
			diffuse = closestObjectMaterial.GetColor().Average(lightSource->GetColor()) * closestObjectMaterial.GetDiffuse() * lightSource->GetIntensity() * std::fmax(lambertian, 0) / distance;
			finalColor += diffuse;
		}

		// Specular
		if(shadowed == false && SPECULAR_ON)
		{
			if(closestObjectMaterial.GetSpecular() > 0 && closestObjectMaterial.GetSpecular() <= 1)
			{
				Vector V = -sceneDirection;
				// Blinn-Phong
				Vector H = (lightDir + V).Normalize();
				FPType NdotH = closestObjectNormal.Dot(H);

				phong = pow(NdotH, 350);
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

	// Ambient
	if(AMBIENT_ON)
	{
		ambient = closestObjectMaterial.GetColor() * AMBIENT_LIGHT * closestObjectMaterial.GetAmbient();
		finalColor += ambient;
	}
	
	Color reflections = GetReflections(closestObjectMaterial, closestObjectNormal, sceneDirection, sceneObjects, indexOfClosestObject, point, lightSources);
	finalColor += reflections;
	// Reflection & Refraction
	if(closestObjectMaterial.GetReflection() > 0 && closestObjectMaterial.GetRefraction() > 0 && REFLECTIONS_ON && REFRACTIONS_ON)
	{
		//n = closestObjectMaterial.GetRefraction() / 
	}


	return finalColor.Clip();
}

void Render(bitmap_image &image, unsigned x, unsigned y, FPType tempRed[], FPType tempGreen[], FPType tempBlue[])
{
	FPType totalRed = 0;
	FPType totalGreen = 0;
	FPType totalBlue = 0;

	for(int iRed = 0; iRed < SUPERSAMPLING*SUPERSAMPLING; iRed++)
	{
		totalRed = totalRed + tempRed[iRed];
	}
	for(int iGreen = 0; iGreen < SUPERSAMPLING*SUPERSAMPLING; iGreen++)
	{
		totalGreen = totalGreen + tempGreen[iGreen];
	}
	for(int iBlue = 0; iBlue < SUPERSAMPLING*SUPERSAMPLING; iBlue++)
	{
		totalBlue = totalBlue + tempBlue[iBlue];
	}

	FPType avgRed = totalRed / (SUPERSAMPLING*SUPERSAMPLING);
	FPType avgGreen = totalGreen / (SUPERSAMPLING*SUPERSAMPLING);
	FPType avgBlue = totalBlue / (SUPERSAMPLING*SUPERSAMPLING);

	//image.set_pixel(x, y, avgRed, avgGreen, avgBlue);
	image.set_pixel(x, y, 255, 0, 0);
}

// Camera pos, dir here
void EvaluateIntersections(FPType xCamOffset, FPType yCamOffset, unsigned aaIndex, FPType tempRed[], FPType tempGreen[], FPType tempBlue[])
{
	Camera camera(Vector(-0.5, 1, -2.3), Vector(-0.5, -1.3, 4));

	// Set up scene
	Scene scene;
	std::vector<std::shared_ptr<Object>> sceneObjects = scene.InitObjects();
	std::vector<std::shared_ptr<Light>> lightSources = scene.InitLightSources();

	// Camera direction for every ray shot through each pixel
	Vector camRayDir = (camera.GetCameraDirection() + camera.GetCamX() * (xCamOffset - 0.5) + camera.GetCamY() * (yCamOffset - 0.5)).Normalize();
	camera.SetSceneDirection(camRayDir);

	// Shoot ray into evey pixel of the image
	Ray camRay(camera.GetOrigin(), camera.GetSceneDirection());

	std::vector<FPType> intersections;
	intersections.reserve(1024);

	// Check if ray intersects with any scene objects
	for(const auto &sceneObject : sceneObjects)
	{
		intersections.push_back(sceneObject->GetIntersection(camRay));
	}
	unsigned indexOfClosestObject = ClosestObjectIndex(intersections);
	// If it doesn't register a ray trace set that pixel to be black (ray missed everything)
	if(indexOfClosestObject == -1)
	{
		tempRed[aaIndex] = 255;
		tempGreen[aaIndex] = 0;
		tempBlue[aaIndex] = 0;
	}
	else // Ray hit an object
	{
		if(intersections[indexOfClosestObject] > TOLERANCE) // If intersection at that point > accuracy, get color of object
		{
			// If ray hit something, set point position to ray-object intersection
			Vector point((camera.GetOrigin() + (camera.GetSceneDirection() * intersections[indexOfClosestObject])));
			Color intersectionColor = GetColorAt(point, camera.GetSceneDirection(), sceneObjects, indexOfClosestObject, lightSources);
			tempRed[aaIndex] = intersectionColor.GetRed();
			tempGreen[aaIndex] = intersectionColor.GetGreen();
			tempBlue[aaIndex] = intersectionColor.GetBlue();
		}
	}
}

void launchThread(unsigned start, unsigned end, bitmap_image &image)
{
	unsigned width = WIDTH;
	unsigned heigh = HEIGHT;

	FPType tempRed[SUPERSAMPLING*SUPERSAMPLING];
	FPType tempGreen[SUPERSAMPLING*SUPERSAMPLING];
	FPType tempBlue[SUPERSAMPLING*SUPERSAMPLING];
	unsigned aaIndex;
	FPType xCamOffset, yCamOffset; // Offset position of rays from the direction where camera is pointed (x & y positions)

	for(unsigned z = start; z < end; z++)
	{
		unsigned x = z % width;
		unsigned y = z / width;

		//// Calculates % of render completed
		//columnsCompleted++;
		//percentage = columnsCompleted / (FPType) WIDTH * 100;
		//std::cout << '\r' << "Completion: " << (int) percentage << '%';

		//// Calculates Time left
		//end = clock();
		//FPType diff = ((FPType) end - (FPType) start) / CLOCKS_PER_SEC;
		//timeToComplete = (diff / columnsCompleted) * (WIDTH - columnsCompleted);
		//if(timeToCompleteMax < timeToComplete)
		//	timeToCompleteMax = timeToComplete;
		//std::cout << "\tTime Left: " << timeToComplete << "s";
		//std::cout << "\tTime To Render Image: " << timeToCompleteMax / 60 << "min " << timeToCompleteMax % 60 << "s";
		//fflush(stdout);

		for(unsigned i = 0; i < SUPERSAMPLING; i++)
		{
			for(unsigned j = 0; j < SUPERSAMPLING; j++)
			{
				aaIndex = j*SUPERSAMPLING + i;
				// No Anti-aliasing
				if(SUPERSAMPLING == 1)
				{
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
				}

				// Supersampling anti-aliasing
				else 
				{
					if(WIDTH > HEIGHT)
					{
						xCamOffset = ((x + (double) i / ((double) SUPERSAMPLING - 1)) / WIDTH)*ASPECT_RATIO - (((WIDTH - HEIGHT) / (double) HEIGHT) / 2);
						yCamOffset = (y + (j + 0.5) / SUPERSAMPLING) / HEIGHT;
					}
					else if(HEIGHT > WIDTH) // Not sure if works
					{
						// the imager is taller than it is wide
						xCamOffset = (x + (double) i / ((double) SUPERSAMPLING - 1)) / WIDTH;
						yCamOffset = (((HEIGHT - y) + (double) i / ((double) SUPERSAMPLING - 1)) / HEIGHT) / ASPECT_RATIO - (((HEIGHT - WIDTH) / (double) WIDTH) / 2);
					}
					else
					{
						xCamOffset = (x + (i + 0.5) / SUPERSAMPLING) / WIDTH, HEIGHT;
						yCamOffset = (y + (j + 0.5) / SUPERSAMPLING) / WIDTH, HEIGHT;
					}
				}
				EvaluateIntersections(xCamOffset, yCamOffset, aaIndex, tempRed, tempGreen, tempBlue);
			}
		}
		Render(image, x, y, tempRed, tempGreen, tempBlue);
	}
}

void CalcIntersections()
{
	clock_t end, start = clock();
	bitmap_image image(WIDTH, HEIGHT);

	unsigned nThreads = std::thread::hardware_concurrency();
	std::cout << "Threads: " << nThreads << std::endl;

	std::thread* tt = new std::thread[nThreads];

	unsigned size = WIDTH*HEIGHT;

	FPType chunk = size / nThreads;
	FPType rem = size % nThreads;

	//launch threads
	for(unsigned i = 0; i < nThreads - 1; i++)
	{
		// Doesn't render image properly (just black)
		tt[i] = std::thread(launchThread, i*chunk, (i + 1)*chunk, image);
	}

	// This renders the image properly
	launchThread((nThreads - 1)*chunk, (nThreads) *chunk + rem, image);

	for(unsigned int i = 0; i < nThreads - 1; i++)
		tt[i].join();

	end = clock();
	FPType diff = ((FPType) end - (FPType) start) / CLOCKS_PER_SEC;
	std::cout << "\n\nResolution: " << WIDTH << "x" << HEIGHT << std::endl;
	std::cout << "Time: " << diff << " seconds" << std::endl;

	std::string saveString = std::to_string(int(WIDTH)) + "x" + std::to_string(int(HEIGHT)) + "render " + std::to_string(SUPERSAMPLING) + "x SS.bmp";
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