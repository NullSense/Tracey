#pragma once

#include "Vector3.h"
#include "Object.h"
#include "Ray.h"

class Plane : public Object
{
public:
    Plane();
    Plane(Vector3 center_, Vector3 normal_);
    
    virtual Vector3 GetNormalAt(const Vector3 point);
    virtual FPType GetIntersection(const Ray ray);
	FPType GetIntersectionDisk(const Ray ray, const Vector3 normal_, const Vector3 position);
	Vector3 GetCenter() const;

private:
	Vector3 normal, center;
};
