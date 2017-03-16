#pragma once
#include "Globals.h"
#include "Vector3.h"
#include "Ray.h"
#include "Plane.h"

class Disk : public Plane
{
public:
	Disk();
	Disk(FPType radius_, Vector3d position_, Vector3d normal_);
	FPType GetIntersection(const Ray ray);

	Vector3d GetNormalAt(const Vector3d point);
	Vector3d GetPosition() const;

private:
	Vector3d position;
	Vector3d normal;
	FPType radius;
};