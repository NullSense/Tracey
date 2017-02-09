#pragma once

#include "Vector.h"
#include "Object.h"
#include "Ray.h"

class Plane : public Object
{
public:
    Plane();
    Plane(Vector center_, Vector normal_);
    
    virtual Vector GetNormalAt(const Vector point);
    virtual FPType GetIntersection(const Ray ray);
	FPType GetIntersectionDisk(const Ray ray, const Vector normal_, const Vector position);
	Vector GetCenter() const;

private:
	Vector normal, center;
};
