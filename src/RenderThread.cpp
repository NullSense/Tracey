#include "RenderThread.h"

RenderThread::RenderThread()
{

}

inline FPType RenderThread::Clamp(const FPType lo, const FPType hi, const FPType v) const
{
	return std::max(lo, std::min(hi, v));
}

inline FPType RenderThread::Deg2rad(const FPType deg)
{
	return deg * M_PI / 180;
}

FPType RenderThread::Fresnel(const Vector3d &sceneDirection, const Vector3d &normal, const FPType ior) const
{
	FPType kr;
	Vector3d I = sceneDirection;
	Vector3d N = normal;
	auto cosi = Clamp(-1, 1, I.Dot(N));
	auto etai = GLOBAL_REFRACTION;
	FPType etat = ior;
	if (cosi > 0)
	{
		std::swap(etai, etat);
	}
	// Compute sini using Snell's law
	FPType sint = etai / etat * sqrt(std::fmax(0.f, 1 - cosi * cosi));
	// Total internal reflection
	if (sint >= 1)
	{
		kr = 1;
	}
	else
	{
		auto cost = sqrt(std::fmax(0.f, 1 - sint * sint));
		cosi = fabs(cosi);
		FPType Rs = ((etat * cosi) - (etai * cost)) / ((etat * cosi) + (etai * cost));
		FPType Rp = ((etai * cosi) - (etat * cost)) / ((etai * cosi) + (etat * cost));
		kr = (Rs * Rs + Rp * Rp) / 2;
	}
	return kr;
}

Ray RenderThread::GetReflectionRay(const Vector3d &normal, const Vector3d &sceneDirection, const Vector3d &position)
{
	const auto cosI = normal.Dot(sceneDirection);

	auto reflectionDirection = sceneDirection - normal * 2 * cosI;
	auto offset = reflectionDirection * BIAS;

	Ray reflectionRay(position + offset, reflectionDirection);
	return reflectionRay;
}

Vector3d RenderThread::GetRefraction(const Vector3d &incident, const Vector3d &normal, const FPType ior) const
{
	FPType cosi = Clamp(-1, 1, incident.Dot(normal));
	FPType etai = GLOBAL_REFRACTION;
	FPType etat = ior;
	Vector3d n = normal;
	if (cosi < 0)
		cosi = -cosi;
	else
		std::swap(etai, etat); n = -normal;
	FPType eta = etai / etat;
	FPType k = 1 - eta * eta * (1 - cosi * cosi);
	Vector3d a = incident * eta + normal * (eta * cosi - sqrt(k));

	//return k < 0 ? 0 : eta * incident + (eta * cosi - sqrtf(k)) * n;
	if (k < 0)
	{
		//return 0;
		a = incident * eta + normal * (eta * cosi - sqrt(k));
		Ray reflRay = GetReflectionRay(normal, incident, a);
		return reflRay.GetDirection();
	}
	else
		return a;
}

// Calculate reflection colors
Color RenderThread::GetReflections(const Vector3d &position, const Vector3d &sceneDirection, const std::vector<std::shared_ptr<Object>> &sceneObjects,
	const int indexOfClosestObject, const std::vector<std::shared_ptr<Light>> &lightSources, int depth)
{
	if (REFLECTIONS_ON && /*depth <= DEPTH && */indexOfClosestObject != -1) // Not checking depth for infinite mirror effect
	{
		std::shared_ptr<Object> sceneObject = sceneObjects[indexOfClosestObject];
		FPType reflection = sceneObject->material.GetReflection();
		if (reflection > 0 && sceneObject->material.GetRefraction() != GLOBAL_REFRACTION)
		{
			if (sceneObject->material.GetSpecular() > 0 && sceneObject->material.GetSpecular() <= 1)
			{
				Vector3d normal = sceneObject->GetNormalAt(position);
				auto reflectionRay = GetReflectionRay(normal, sceneDirection, position);

				// determine what the ray intersects with first
				std::vector<FPType> reflectionIntersections;
				reflectionIntersections.reserve(1024);
				for (const auto &object : sceneObjects)
				{
					reflectionIntersections.emplace_back(object->GetIntersection(reflectionRay));
					numSecondaryRays++;
				}

				int closestObjectWithReflection = ClosestObjectIndex(reflectionIntersections);

				if (closestObjectWithReflection != indexOfClosestObject) // Makes infinite mirror effect
				{
					numSecondaryHitRays++;
					// reflection ray missed everthing else
					if (reflectionIntersections[closestObjectWithReflection] > BIAS)
					{
						// determine the position and sceneDirectionection at the position of intersection with the reflection ray
						// the ray only affects the color if it reflected off something
						Vector3d reflectionIntersectionPosition = reflectionRay.GetOrigin() + (reflectionRay.GetDirection() * (reflectionIntersections[closestObjectWithReflection]));
						auto reflectionIntersectionColor = Trace(reflectionIntersectionPosition, reflectionRay.GetDirection(), sceneObjects, closestObjectWithReflection, lightSources, depth + 1);
						return reflectionIntersectionColor * reflection;
					}
					else
						return Color(0);
				}
				else
					return Color(0);
			}
			else
				return Color(0);
		}
		else
			return Color(0);
	}
	else
		return Color(0);
}

Color RenderThread::GetRefractions(const Vector3d &position, const Vector3d &dir, const std::vector<std::shared_ptr<Object>> &sceneObjects,
	const int &indexOfClosestObject, const std::vector<std::shared_ptr<Light>> &lightSources, int depth)
{
	if (indexOfClosestObject != -1)
	{
		std::shared_ptr<Object> sceneObject = sceneObjects[indexOfClosestObject];

		FPType ior = sceneObject->material.GetRefraction();
		if (ior > 0 && sceneObject->material.GetReflection() > 0)
		{
			Vector3d normal = sceneObject->GetNormalAt(position);
			Vector3d refractionDir = GetRefraction(dir, normal, ior).Normalize();
			Ray refractionRay(position, refractionDir);

			std::vector<FPType> refractionIntersections;
			refractionIntersections.reserve(10024);
			for (const auto &object : sceneObjects)
			{
				refractionIntersections.emplace_back(object->GetIntersection(refractionRay));
				numSecondaryRays++;
			}

			if (refractionIntersections.size() > 0)
			{
				int closestObjectWithRefraction = ClosestObjectIndex(refractionIntersections);
				if (closestObjectWithRefraction != -1)
				{
					numSecondaryHitRays++;
					Color refractionColor = 0;
					FPType kr = Fresnel(dir, normal, ior);
					bool outside = dir.Dot(normal) < 0;
					Vec3d bias = normal * BIAS;

					Color reflectionColor = GetReflections(position, dir, sceneObjects, indexOfClosestObject, lightSources, depth);
					// compute refraction if it is not a case of total internal reflection
					if (kr < 1)
					{
						Vector3d refractionIntersection = refractionRay.GetOrigin() + (refractionRay.GetDirection() * (refractionIntersections[closestObjectWithRefraction]));
						Vector3d refractionRayOrig = outside ? refractionIntersection - bias : refractionIntersection + bias;

						refractionColor = Trace(refractionRayOrig, refractionRay.GetDirection(), sceneObjects, closestObjectWithRefraction, lightSources, depth + 1);
					}
					else // TIR
						refractionColor += reflectionColor;
					//return 0;

					// mix the two
					Color refraReflColor = reflectionColor * kr + refractionColor * (1 - kr);
					return refraReflColor;
				}
				else
					return Color(0);
			}
			else
				return Color(0);
		}
		else
			return Color(0);
	}
	else
		return Color(0);
}

// Get the color of the pixel at the ray-object intersection position
Color RenderThread::Trace(const Vector3d &intersection, const Vector3d &direction, const std::vector<std::shared_ptr<Object>> &sceneObjects, const int indexOfClosestObject,
	const std::vector<std::shared_ptr<Light>> &lightSources, const int &depth = 0)
{
	if (indexOfClosestObject != -1 && depth <= DEPTH) // not checking depth for infinite mirror effect (not a lot of overhead)
	{
		std::shared_ptr<Object> sceneObject = sceneObjects[indexOfClosestObject];
		Vector3d normal = sceneObject->GetNormalAt(intersection);

		Color ambient;
		Color diffuse;
		FPType lambertian;
		FPType phong;
		Color specular;
		Color finalColor;

		if (sceneObject->material.GetSpecial() == 2) // Checkerboard pattern floor
		{
			unsigned square = int(floor(intersection.x)) + int(floor(intersection.z)); // (floor() rounds down)
			if (square % 2 == 0) // black tile
				sceneObject->material.SetColor(Color(0));
			else // white tile
				sceneObject->material.SetColor(Color(255));
		}
		if (sceneObject->material.GetSpecial() == 1) // Sphere checkerboard
		{
			FPType scale = 4;
			FPType pattern = (fmod(sceneObject->GetTexCoords(normal, intersection).x * scale, 1) > 0.5) ^ (fmod(sceneObject->GetTexCoords(normal, intersection).y * scale, 1) > 0.5);
			finalColor += sceneObject->material.GetColor() * pattern * std::fmax(0.f, normal.Dot(-direction));
		}

		// Ambient
		if (AMBIENT_ON)
		{
			ambient = sceneObject->material.GetColor() * AMBIENT_LIGHT * sceneObject->material.GetAmbient();
			finalColor += ambient;
		}

		// Shadows, Diffuse, Specular
		if (SHADOWS_ON || DIFFUSE_ON || SPECULAR_ON)
		{
			Vector3d lightDir;
			for (const auto &lightSource : lightSources)
			{
				bool shadowed = false;
				if (lightSource->POINT)
					lightDir = (lightSource->GetPosition() - intersection); // Calculate the sceneDirectionectional vector towards the lightSource

																			/*if(lightSource->AREA)
																			{

																			}*/

				FPType distance = lightDir.Magnitude();
				lightDir = lightDir.Normalize();
				lambertian = normal.Dot(lightDir.Normalize());

				// Shadows
				if (SHADOWS_ON && lambertian > 0)
				{
					Ray shadowRay(intersection, lightDir); // Cast a ray from the first intersection to the light
					std::vector<FPType> secondaryIntersections;
					secondaryIntersections.reserve(1024);

					for (const auto &object : sceneObjects)
					{
						secondaryIntersections.emplace_back(object->GetIntersection(shadowRay));
						numSecondaryRays++;
					}

					for (const auto &secondaryIntersection : secondaryIntersections)
					{
						if (secondaryIntersection > BIAS) // If shadow ray intersects with some object along the way
						{
							numSecondaryHitRays++;
							if (secondaryIntersection <= distance)
							{
								shadowed = true;
								break;
							}
						}
					}
				}

				// Diffuse
				if (DIFFUSE_ON && shadowed == false)
				{
					//diffuse = sceneObject->GetColor().Average(lightSource->GetColor()) * 0.18 * M_PI * lightSource->GetIntensity() * std::fmax(0, lambertian) / distance;
					diffuse = sceneObject->material.GetColor().Average(lightSource->GetColor()) * sceneObject->material.GetDiffuse() * lightSource->GetIntensity() * std::fmax(lambertian, 0) / distance;
					finalColor += diffuse;
				}

				// Specular
				if (shadowed == false && SPECULAR_ON)
				{
					if (sceneObject->material.GetSpecular() > 0 && sceneObject->material.GetSpecular() <= 1 && sceneObject->material.GetRefraction() != GLOBAL_REFRACTION)
					{
						Vector3d V = -direction;
						// Blinn-Phong
						Vector3d H = (lightDir + V).Normalize();
						FPType NdotH = normal.Dot(H);

						phong = pow(NdotH, 500);
						specular = lightSource->GetColor() * std::fmax(0, phong) * lightSource->GetIntensity(); // sceneObject->GetSpecular(); add or no?
						finalColor += specular * sceneObject->material.GetSpecular();
					}
				}
			}
		}

		// perfect mirrors
		if (REFLECTIONS_ON && sceneObject->material.GetRefraction() == 0 && sceneObject->material.GetReflection() > 0)
		{
			auto reflections = GetReflections(intersection, direction, sceneObjects, indexOfClosestObject, lightSources, depth + 1);
			finalColor += reflections;
		}

		//Reflections & Refractions
		if (REFRACTIONS_ON && sceneObject->material.GetRefraction() > 0 && sceneObject->material.GetReflection() > 0)
		{
			Color refractions = GetRefractions(intersection, direction, sceneObjects, indexOfClosestObject, lightSources, depth + 1);
			finalColor += refractions;
		}

		finalColor.Clip();
		return finalColor;
	}

	else
		return Color(0);
}

// Returns the closest object's index that the ray intersected with
int RenderThread::ClosestObjectIndex(const std::vector<FPType> &intersections)
{
	auto minValueIndex = 0;

	// Prevent unnecessary calculations (only check the ones that intersect)
	if (intersections.size() == 0) // No intersections
		return -1;

	else if (intersections.size() == 1)
	{
		if (intersections[0] > 0) // If intersection is greater than 0, then it's our index of minimum value (0th element in vector)
			return 0;
		else // Otherwise the only intersection value is negative (ray missed everything)
			return -1;
	}
	else // If there's more than 1 intersection, find the MAX value
	{
		FPType max = 0;
		for (FPType i : intersections)
		{
			if (max < i)
				max = i;
		}
		if (max > 0)
		{
			// Only searh for positive intersections
			// Find the minimum POSITIVE value
			for (auto intersectionIndex = 0; intersectionIndex < intersections.size(); intersectionIndex++)
			{
				// If intersection is positive and is lower or equal to the max intersection
				if (intersections[intersectionIndex] > 0 && intersections[intersectionIndex] <= max)
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

void RenderThread::Render(const unsigned x, const unsigned y, const Color tempColor[]) const
{
	auto totalColor = Color(0);

	for (auto col = 0; col < SUPERSAMPLING*SUPERSAMPLING; col++)
	{
		totalColor += tempColor[col];
	}

	auto avgColor = totalColor / (SUPERSAMPLING * SUPERSAMPLING);
	image1->set_pixel(x, y, char(avgColor.GetRed()), char(avgColor.GetGreen()), char(avgColor.GetBlue()));
}

// Camera pos, sceneDirection here
void RenderThread::EvaluateIntersections(const FPType xCamOffset, const FPType yCamOffset, const unsigned aaIndex, Color tempColor[], const Matrix44f &cameraToWorld,
	const std::vector<std::shared_ptr<Object>> &sceneObjects, const std::vector<std::shared_ptr<Light>> &lightSources)
{
	Camera camera(Vector3d(0, 1.8, 5), Vector3d(0, 0, -1));

	Vector3d camRayDir;
	cameraToWorld.MultDirMatrix(Vector3d(xCamOffset, yCamOffset - 0.1, -1), camRayDir);
	camRayDir.Normalize();
	camera.SetTo(camRayDir);
	// Shoot ray into evey pixel of the image
	Ray camRay(camera.GetFrom(), camera.GetTo());

	std::vector<FPType> intersections;
	intersections.reserve(2048);

	// Check if ray intersects with any scene sceneObjects
	for (const auto &sceneObject : sceneObjects)
	{
		//if(sceneObject->bbox.GetIntersection(camRay))
		intersections.emplace_back(sceneObject->GetIntersection(camRay));
		numPrimaryRays++;
	}

	int indexOfClosestObject = ClosestObjectIndex(intersections);

	// If it doesn't register a ray trace set that pixel to be black (ray missed everything)
	if (indexOfClosestObject == -1)
		tempColor[aaIndex] = Color(0);

	else // Ray hit an object
	{
		if (intersections[indexOfClosestObject] > BIAS) // If intersection at that position > accuracy, get color of object
		{
			numPrimaryHitRays++;
			// If ray hit something, set position position to ray-object intersection
			Vector3d intersection((camera.GetFrom() + (camera.GetTo() * intersections[indexOfClosestObject])));
			Color intersectionColor = Trace(intersection, camera.GetTo(), sceneObjects, indexOfClosestObject, lightSources);
			tempColor[aaIndex] = Color(intersectionColor.GetRed(), intersectionColor.GetGreen(), intersectionColor.GetBlue());
		}
	}
}

void RenderThread::LaunchThread(const unsigned start, const unsigned end, std::shared_ptr<bitmap_image> image)
{
	image1 = image;
	Color tempColor[SUPERSAMPLING*SUPERSAMPLING];
	unsigned aaIndex;
	FPType xCamOffset, yCamOffset; // Offset position of rays from the sceneDirectionection where camera is pointed (x & y positions)

	FPType scale = tan(Deg2rad(FOV * 0.5));

	Matrix44f cameraToWorld;
	Vector3d orig;
	cameraToWorld.MultVecMatrix(Vector3d(0), orig);

	// Set up scene
	Scene scene; // For some reason, when these objects are taken out of the threads, visual bugs occur
	std::vector<std::shared_ptr<Object>> sceneObjects = scene.InitObjects();
	std::vector<std::shared_ptr<Light>> lightSources = scene.InitLightSources();

	FPType aspectRatio = WIDTH / FPType(HEIGHT);
	for (unsigned z = start; z < end; z++)
	{
		unsigned x = z % WIDTH;
		unsigned y = z / WIDTH;

		for (unsigned i = 0; i < SUPERSAMPLING; i++)
		{
			for (unsigned j = 0; j < SUPERSAMPLING; j++)
			{
				// Heigh cannot be bigger than width
				aaIndex = j*SUPERSAMPLING + i;
				// Supersampling anti-aliasing
				if (SUPERSAMPLING != 1)
				{
					xCamOffset = (2 * (x + (0.5 + i) / (SUPERSAMPLING)) / FPType(WIDTH) - 1) * aspectRatio * scale;
					yCamOffset = (1 - 2 * (y + (j + 0.5) / SUPERSAMPLING) / FPType(HEIGHT)) * scale;
				}
				else // No Anti-aliasing
				{
					xCamOffset = (2 * (x + 0.5) / FPType(WIDTH) - 1) * aspectRatio * scale;
					yCamOffset = (1 - 2 * (y + 0.5) / FPType(HEIGHT)) * scale;
				}
				EvaluateIntersections(xCamOffset, yCamOffset, aaIndex, tempColor, cameraToWorld, sceneObjects, lightSources);
			}
		}
		Render(x, y, tempColor);
	}
}