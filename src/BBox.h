#pragma once
#include "Globals.h"

class BBox
{
public:
	BBox()
	{}
	BBox(Vector3d min_, Vector3d max_)
	{
		bounds[0] = min_;
		bounds[1] = max_;
	}
	BBox& extendBy(const Vector3d &p)
	{
		if(p.x < bounds[0].x) bounds[0].x = p.x;
		if(p.y < bounds[0].y) bounds[0].y = p.y;
		if(p.z < bounds[0].z) bounds[0].z = p.z;
		if(p.x > bounds[1].x) bounds[1].x = p.x;
		if(p.y > bounds[1].y) bounds[1].y = p.y;
		if(p.z > bounds[1].z) bounds[1].z = p.z;

		return *this;
	}

	FPType GetIntersection(const Ray &r) const
	{
		FPType tmin, tmax, tymin, tymax, tzmin, tzmax;

		tmin = (bounds[r.sign[0]].x - r.GetOrigin().x) * r.invDir.x;
		tmax = (bounds[1 - r.sign[0]].x - r.GetOrigin().x) * r.invDir.x;
		tymin = (bounds[r.sign[1]].y - r.GetOrigin().y) * r.invDir.y;
		tymax = (bounds[1 - r.sign[1]].y - r.GetOrigin().y) * r.invDir.y;

		if((tmin > tymax) || (tymin > tmax))
			return false;

		if(tymin > tmin)
			tmin = tymin;
		if(tymax < tmax)
			tmax = tymax;

		tzmin = (bounds[r.sign[2]].z - r.GetOrigin().z) * r.invDir.z;
		tzmax = (bounds[1 - r.sign[2]].z - r.GetOrigin().z) * r.invDir.z;

		if((tmin > tzmax) || (tzmin > tmax))
			return false;

		if(tzmin > tmin)
			tmin = tzmin;
		if(tzmax < tmax)
			tmax = tzmax;

		FPType t = tmin;

		if(t < 0)
		{
			t = tmax;
			if(t < 0) return false;
		}

		return t;
	}

	//Vector3<T> GetIntersection(const Ray &ray) const;
	//Vector3<T> GetNormalAt(const Vector3d &point);
	Vec3d bounds[2];

private:
	Vector3d min;
	Vector3d max;
};
