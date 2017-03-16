#pragma once
#include "Globals.h"
#include "Vector3.h"
#include "Ray.h"
#include "Plane.h"

class Disk : public Plane
{
public:
	Disk();
	Disk(FPType radius_, Vector3 position_, Vector3 normal_);
	FPType GetIntersection(const Ray ray);

	Vector3 GetNormalAt(const Vector3 point);
	Vector3 GetPosition() const;

private:
	Vector3 position;
	Vector3 normal;
	FPType radius;
};