#pragma once
#include "Globals.h"
#include "Vector.h"
#include "Ray.h"
#include "Plane.h"

class Disk : public Plane
{
public:
	Disk(Vector position_, FPType radius_, Vector normal_);
	FPType GetIntersection(Ray ray);

	virtual Vector GetNormalAt(Vector point);
	Vector GetPosition() const;
	void SetNormal(const Vector &normal_);
	void SetPosition(const Vector &position_);

private:
	Vector position;
	Vector normal;
	FPType radius;
};