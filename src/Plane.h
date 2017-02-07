#pragma once

#include "Vector.h"
#include "Object.h"
#include "Ray.h"

class Plane : public Object
{
public:
    Plane();
    Plane(Vector center_, Vector normal_);
    
    virtual Vector GetNormalAt(Vector point);
    virtual FPType GetIntersection(Ray ray);
	FPType GetIntersectionDisk(Ray ray, Vector normal_, Vector position);
	Vector GetCenter() const;

private:
	Vector normal, center;
};
