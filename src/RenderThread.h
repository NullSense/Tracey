#pragma once
#include "Globals.h"
#include "Scene.h"
#include "Camera.h"
#include "bitmap_image.hpp"
#include "Matrix44.h"

class RenderThread
{
public:
	RenderThread();
	Color Trace(const Vector3d &intersection, const Vector3d &direction, const std::vector<std::shared_ptr<Object>> &sceneObjects, const int indexOfClosestObject,
		const std::vector<std::shared_ptr<Light>> &lightSources, const int &depth);
	Color GetRefractions(const Vector3d &position, const Vector3d &dir, const std::vector<std::shared_ptr<Object>> &sceneObjects,
		const int &indexOfClosestObject, const std::vector<std::shared_ptr<Light>> &lightSources, int depth);
	Color GetReflections(const Vector3d &position, const Vector3d &sceneDirection, const std::vector<std::shared_ptr<Object>> &sceneObjects,
		const int indexOfClosestObject, const std::vector<std::shared_ptr<Light>> &lightSources, int depth);
	Vector3d GetRefraction(const Vector3d &incident, const Vector3d &normal, const FPType ior) const;
	static Ray GetReflectionRay(const Vector3d &normal, const Vector3d &sceneDirection, const Vector3d &position);
	FPType Fresnel(const Vector3d &sceneDirection, const Vector3d &normal, const FPType ior) const;
	static FPType Deg2rad(const FPType deg);
	FPType Clamp(const FPType lo, const FPType hi, const FPType v) const;

	void Render(const unsigned x, const unsigned y, const Color tempColor[]) const;
	void EvaluateIntersections(const FPType xCamOffset, const FPType yCamOffset, const unsigned aaIndex, Color tempColor[], const Matrix44f &cameraToWorld, const std::vector<std::shared_ptr<Object>> &sceneObjects, const std::vector<std::shared_ptr<Light>> &lightSources);
	void LaunchThread(const unsigned start, const unsigned end, std::shared_ptr<bitmap_image> image);
	static int ClosestObjectIndex(const std::vector<FPType> &intersections);

	/*int triangleCount;
	int bboxTests;
	int bboxIntersections;
	int triangleTests;
	int triangleIntersections;*/
	int numPrimaryRays;
	int numPrimaryHitRays;
	int numSecondaryRays;
	int numSecondaryHitRays;
	std::shared_ptr<bitmap_image> image1;
};