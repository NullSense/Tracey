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

Color GetColorAt(Vector &position, Vector &sceneDirection, const std::vector<std::shared_ptr<Object>> &sceneObjects, unsigned indexOfClosestObject, const std::vector<std::shared_ptr<Light>> &lightSources, unsigned depth);

Ray GetReflectionRay(Vector &closestObjectNormal, Vector &sceneDirection, Vector &position);

Color GetReflections(Vector &position, Vector &sceneDirection, const std::vector<std::shared_ptr<Object>> &sceneObjects, int indexOfClosestObject, const std::vector<std::shared_ptr<Light>> &lightSources);

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

FPType clamp(const FPType &lo, const FPType &hi, const FPType &v)
{
	return std::max(lo, std::min(hi, v));
}

FPType fresnel(Vector &sceneDirection, Vector &closestObjectNormal, Material &closestObjectMaterial)
{
	FPType kr;
	Vector I = sceneDirection;
	Vector N = closestObjectNormal;
	FPType cosi = clamp(-1, 1, I.Dot(N));
	FPType etai = 1, etat = closestObjectMaterial.GetRefraction();
	if(cosi > 0)
	{
		std::swap(etai, etat);
	}
	// Compute sini using Snell's law
	FPType sint = etai / etat * sqrtf(std::fmax(0.f, 1 - cosi * cosi));
	// Total internal reflection
	if(sint >= 1)
	{
		kr = 1;
	}
	else
	{
		FPType cost = sqrtf(std::fmax(0.f, 1 - sint * sint));
		cosi = fabsf(cosi);
		FPType Rs = ((etat * cosi) - (etai * cost)) / ((etat * cosi) + (etai * cost));
		FPType Rp = ((etai * cosi) - (etat * cost)) / ((etai * cosi) + (etat * cost));
		kr = (Rs * Rs + Rp * Rp) / 2;
	}
	return kr;
	// As a consequence of the conservation of energy, transmittance is given by:
	// kt = 1 - kr;
}

Ray GetRefractionRay(Vector &position, Vector &sceneDirection, Vector &closestObjectNormal, Material &closestObjectMaterial)
{
	//Vector b = closestObjectNormal.Dot(sceneDirection) < 0 ? closestObjectNormal : -closestObjectNormal;
	//bool goingIn = closestObjectNormal.Dot(b) > 0; // Ray going into material? outside -> in inside == true
	//FPType cosI = sceneDirection.Dot(b);
	//// If going into material, do (global refraction (usually air) / material refraction); Else, material refraction/global refraction
	//FPType n = goingIn ? GLOBAL_REFRACTION / closestObjectMaterial.GetRefraction() : closestObjectMaterial.GetRefraction() / GLOBAL_REFRACTION;
	//FPType cos2T = n * n * (1 - cosI * cosI);

	//if(cos2T < 0) // TIR - Total Internal Reflection
	//	std::cout << "TIR";
	////	return ;

	//FPType cosT = sqrt(1 - cos2T);
	//Vector refractionDirection = sceneDirection * n + closestObjectNormal * (n * cosI - cosT);
	//Vector offset = refractionDirection * BIAS;
	//Ray refractionRay(position + offset, refractionDirection);
	//return refractionRay;

	Vector normal = closestObjectNormal;
	FPType nDotI = normal.Dot(sceneDirection);

	FPType n1 = GLOBAL_REFRACTION;
	FPType n2 = closestObjectMaterial.GetRefraction();

	if(nDotI < 0) // Ray is outside the surface
		nDotI = -nDotI;
	else // Ray is inside refractive surface
	{
		normal = -normal;
		std::swap(n1, n2);
	}
	FPType cosI = clamp(-1, 1, sceneDirection.Dot(normal)); // Refraction angle
	FPType n = n1 / n2;
	FPType k = 1 - n * n * (1 - cosI * cosI);

	Vector refractionDir = (sceneDirection * n) + normal * (n * cosI - sqrtf(k));
	Vector offset = refractionDir * BIAS;
	Ray refractionRay(position + offset, refractionDir);
	return refractionRay;
}

Color GetRefractions(Vector &position, Vector &direction, const std::vector<std::shared_ptr<Object>> &sceneObjects,
					 int indexOfClosestObject, const std::vector<std::shared_ptr<Light>> &lightSources)
{
	Material closestObjectMaterial = sceneObjects[indexOfClosestObject]->GetMaterial();
	Vector closestObjectNormal = sceneObjects[indexOfClosestObject]->GetNormalAt(position);
	if(closestObjectMaterial.GetRefraction() > 0)
	{
		Ray refractionRay = GetRefractionRay(position, direction, closestObjectNormal, closestObjectMaterial);

		std::vector<FPType> refractionIntersections;
		for(auto sceneObject : sceneObjects)
		{
			refractionIntersections.push_back(sceneObject->GetIntersection(refractionRay));
		}

		int closestObjectWithRefraction = ClosestObjectIndex(refractionIntersections);

		Color refractionColor;
		// compute fresnel
		//FPType kr = 1;
		FPType kr = fresnel(direction, closestObjectNormal, closestObjectMaterial);
		//std::cout << "KR: " << kr;
		bool outside = direction.Dot(closestObjectNormal) < 0;
		Vector bias = closestObjectNormal * BIAS;

		// compute refraction if it is not a case of total internal reflection
		if(kr < 1)
		{
			Vector refractionDirection = refractionRay.GetDirection().Normalize();
			Vector refractionIntersectionPosition = refractionRay.GetOrigin() + (refractionRay.GetDirection() * (refractionIntersections[closestObjectWithRefraction]));
			Vector refractionRayOrig = outside ? refractionIntersectionPosition - bias : refractionIntersectionPosition + bias;
			
			refractionColor = GetColorAt(refractionRayOrig, refractionDirection, sceneObjects, closestObjectWithRefraction, lightSources, + 1);
		}
		else
		{
			//std::cout << "TIR";
		}

		// GetReflections crashes
		//Color reflectionColor = GetReflections(position, sceneDirection, sceneObjects, indexOfClosestObject, lightSources);
		// mix the two
		Color refraReflColor = /*reflectionColor; * kr + */refractionColor * (1 - kr);
		return refraReflColor;
	}
}

Ray GetReflectionRay(Vector &closestObjectNormal, Vector &sceneDirection, Vector &position)
{
	FPType nDotV = closestObjectNormal.Dot(-sceneDirection);

	Vector resultantReflection = (closestObjectNormal * nDotV * 2) + sceneDirection;
	Vector reflectionDirection = resultantReflection.Normalize();

	// To not hit itself
	Vector offset = reflectionDirection * BIAS;

	Ray reflectionRay(position + offset, resultantReflection);
	return reflectionRay;
}

// Calculate reflection colors
Color GetReflections(Vector &position, Vector &sceneDirection, const std::vector<std::shared_ptr<Object>> &sceneObjects,
					 int indexOfClosestObject, const std::vector<std::shared_ptr<Light>> &lightSources, unsigned depth)
{
	Material closestObjectMaterial = sceneObjects[indexOfClosestObject]->GetMaterial();
	Vector closestObjectNormal = sceneObjects[indexOfClosestObject]->GetNormalAt(position);

	if(closestObjectMaterial.GetReflection() > 0 && REFLECTIONS_ON)
	{
		if(closestObjectMaterial.GetSpecular() > 0 && closestObjectMaterial.GetSpecular() <= 1)
		{
			Ray reflectionRay = GetReflectionRay(closestObjectNormal, sceneDirection, position);

			// determine what the ray intersects with first
			std::vector<FPType> reflectionIntersections;
			for(auto sceneObject : sceneObjects)
			{
				reflectionIntersections.push_back(sceneObject->GetIntersection(reflectionRay));
			}

			int closestObjectWithReflection = ClosestObjectIndex(reflectionIntersections);

			// reflection ray missed everthing else
			if(reflectionIntersections[closestObjectWithReflection] > BIAS)
			{
				// determine the position and sceneDirectionection at the position of intersection with the reflection ray
				// the ray only affects the color if it reflected off something
				Vector reflectionIntersectionPosition = reflectionRay.GetOrigin() + (reflectionRay.GetDirection() * (reflectionIntersections[closestObjectWithReflection]));
				Color reflectionIntersectionColor = GetColorAt(reflectionIntersectionPosition, reflectionRay.GetDirection(), sceneObjects, closestObjectWithReflection, lightSources, depth + 1);
				return reflectionIntersectionColor * closestObjectMaterial.GetReflection();
			}
		}
	}
}

// Get the color of the pixel at the ray-object intersection position
Color GetColorAt(Vector &origin, Vector &direction, const std::vector<std::shared_ptr<Object>> &sceneObjects, unsigned indexOfClosestObject,
				 const std::vector<std::shared_ptr<Light>> &lightSources, unsigned depth)
{
	Color finalColor;
	if(depth > DEPTH)
		return Color(0, 0, 0);
	
	Material closestObjectMaterial = sceneObjects[indexOfClosestObject]->GetMaterial();
	Vector closestObjectNormal = sceneObjects[indexOfClosestObject]->GetNormalAt(origin);

	// Checkerboard pattern floor
	if(closestObjectMaterial.GetSpecial() == 2)
	{
		unsigned square = int(floor(origin.x)) + int(floor(origin.z)); // (floor() rounds down)
		if(square % 2 == 0) // black tile
			closestObjectMaterial.SetColor(Color(0, 0, 0));
		else // white tile
			closestObjectMaterial.SetColor(Color(255, 255, 255));
	}

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
			lightDir = (lightSource->GetPosition() - origin); // Calculate the sceneDirectionectional vector towards the lightSource

		/*if(lightSource->AREA)
		{
			
		}*/

		FPType distance = lightDir.Magnitude();
		lightDir = lightDir.Normalize();
		lambertian = closestObjectNormal.Dot(lightDir);

		// Shadows
		if(SHADOWS_ON && lambertian > 0)
		{

			Ray shadowRay(origin, lightDir); // Cast a ray from the first intersection to the light

			std::vector<FPType> secondaryIntersections;
			for(const auto &sceneObject : sceneObjects)
			{
				secondaryIntersections.push_back(sceneObject->GetIntersection(shadowRay));
			}

			for(const auto &secondaryIntersection : secondaryIntersections)
			{
				if(secondaryIntersection > BIAS) // If shadow ray intersects with some object along the way
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
				Vector V = -direction;
				// Blinn-Phong
				Vector H = (lightDir + V).Normalize();
				FPType NdotH = closestObjectNormal.Dot(H);

				phong = pow(NdotH, 350);
				specular = lightSource->GetColor() * std::fmax(0, phong) * lightSource->GetIntensity(); // closestObjectMaterial.GetSpecular(); add or no?
				finalColor += specular;
			}
		}
	}

	// Ambient
	if(AMBIENT_ON)
	{
		ambient = closestObjectMaterial.GetColor() * AMBIENT_LIGHT * closestObjectMaterial.GetAmbient();
		finalColor += ambient;
	}

	if(REFLECTIONS_ON)
	{

		Color reflections = GetReflections(origin, direction, sceneObjects, indexOfClosestObject, lightSources, depth + 1);
		finalColor += reflections;
	}

	////Reflections & Refractions
	//if(REFRACTIONS_ON && REFLECTIONS_ON)
	//{
	//	Color refractions = GetRefractions(origin, direction, sceneObjects, indexOfClosestObject, lightSources);
	//	finalColor += refractions;
	//}

	return finalColor.Clip();
}

void Render(bitmap_image *image, unsigned x, unsigned y, Color tempColor[])
{
	Color totalColor = Color(0, 0, 0);

	for(int col = 0; col < SUPERSAMPLING*SUPERSAMPLING; col++)
	{
		totalColor += tempColor[col];
	}

	Color avgColor = totalColor / (SUPERSAMPLING * SUPERSAMPLING);

	image->set_pixel(x, y, avgColor.GetRed(), avgColor.GetGreen(), avgColor.GetBlue());
}

// Camera pos, sceneDirection here
void EvaluateIntersections(FPType xCamOffset, FPType yCamOffset, unsigned aaIndex, Color tempColor[])
{
	//Camera camera(Vector(-0.5, 1, -2.3), Vector(-0.5, -1.3, 4));
	Camera camera(Vector(0, 2, -7), Vector(0, -0.6, 4));

	// Set up scene
	Scene scene;
	std::vector<std::shared_ptr<Object>> sceneObjects = scene.InitObjects();
	std::vector<std::shared_ptr<Light>> lightSources = scene.InitLightSources();

	// Camera sceneDirectionection for every ray shot through each pixel
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
		tempColor[aaIndex] = Color(0, 0, 0);
	}
	else // Ray hit an object
	{
		if(intersections[indexOfClosestObject] > BIAS) // If intersection at that position > accuracy, get color of object
		{
			// If ray hit something, set position position to ray-object intersection
			Vector position((camera.GetOrigin() + (camera.GetSceneDirection() * intersections[indexOfClosestObject])));
			Color intersectionColor = GetColorAt(position, camera.GetSceneDirection(), sceneObjects, indexOfClosestObject, lightSources, 0);

			tempColor[aaIndex] = Color(intersectionColor.GetRed(), intersectionColor.GetGreen(), intersectionColor.GetBlue());
		}
	}
}

void launchThread(unsigned start, unsigned end, bitmap_image *image)
{
	unsigned width = WIDTH;
	unsigned heigh = HEIGHT;

	Color tempColor[SUPERSAMPLING*SUPERSAMPLING];
	unsigned aaIndex;
	FPType xCamOffset, yCamOffset; // Offset position of rays from the sceneDirectionection where camera is pointed (x & y positions)

	for(unsigned z = start; z < end; z++)
	{
		unsigned x = z % width;
		unsigned y = z / width;

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
				EvaluateIntersections(xCamOffset, yCamOffset, aaIndex, tempColor);
			}
		}
		Render(image, x, y, tempColor);
	}
}

void CalcIntersections()
{
	clock_t end, start = clock();
	bitmap_image *image = new bitmap_image(WIDTH, HEIGHT);

	unsigned nThreads = std::thread::hardware_concurrency();
	std::cout << "Threads: " << nThreads << std::endl;

	std::thread* tt = new std::thread[nThreads];

	unsigned size = WIDTH*HEIGHT;

	FPType chunk = size / nThreads;
	FPType rem = size % nThreads;

	//launch threads
	for(unsigned i = 0; i < nThreads - 1; i++)
	{
		tt[i] = std::thread(launchThread, i*chunk, (i + 1)*chunk, image);
	}

	launchThread((nThreads - 1)*chunk, (nThreads) *chunk + rem, image);

	for(unsigned int i = 0; i < nThreads - 1; i++)
		tt[i].join();

	end = clock();
	FPType diff = ((FPType) end - (FPType) start) / CLOCKS_PER_SEC;
	std::cout << "Resolution: " << WIDTH << "x" << HEIGHT << std::endl;
	std::cout << "Depth: " << DEPTH << std::endl;
	std::cout << "Time: " << diff << " seconds" << std::endl;

	std::string saveString = std::to_string(int(WIDTH)) + "x" + std::to_string(int(HEIGHT)) + " render, " + std::to_string(SUPERSAMPLING) + "x SS, " + std::to_string(DEPTH) + " depth.bmp";
	image->save_image(saveString);
	std::cout << "Output filename: " << saveString << std::endl;
}


int main()
{
	CalcIntersections();

	std::cout << "\nPress enter to exit...";
	std::cin.ignore();

	return 0;
}