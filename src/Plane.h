#pragma once

#include "Vector.h"
#include "Object.h"
#include "Ray.h"

class Plane : public Object
{
public:
    FPType distance;
    Vector normal, center;

    Plane();
    Plane(Vector center_, FPType distance_, Vector normal_, Color color_);
    
    virtual Color GetColor();
    virtual Vector GetNormalAt(Vector point);
    virtual FPType GetIntersection(Ray ray);
};
