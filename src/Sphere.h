#pragma once
#include "Vector.h"
#include "Object.h"

class Sphere: public Object
{
public:
	Sphere();
	Sphere(FPType radius_, Vector center_);

	Vector GetNormalAt(Vector point);
	virtual FPType GetIntersection(Ray ray);
	FPType GetRadius() const;
	Vector GetCenter() const;
	void SetRadius(const FPType &radius_);
	void SetCenter(const Vector &center_);

private:
	FPType radius;
	Vector center;
};
