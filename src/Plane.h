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
	Vector GetNormal();
	Vector GetCenter();
	void SetNormal(Vector &normal_);
	void SetCenter(Vector &center_);

private:
	Vector normal, center;
};
