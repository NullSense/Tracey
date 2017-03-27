#include "Triangle.h"

Triangle::Triangle()
{
	v0 = Vector3d(0, 0, 6);
	v1 = Vector3d(1, 0, 6);
	v2 = Vector3d(1, 1, 6);
	/*normal = (v1 - v0).Cross(v2 - v0).Normalize();*/
}

Triangle::Triangle(Vector3d &v0_, Vector3d &v1_, Vector3d &v2_)
	:v0 {v0_}, v1 {v1_}, v2 {v2_}/*, normal {(v1 - v0).Cross(v2 - v0).Normalize()}*/
{}

Vector3d Triangle::GetNormalAt(const Vector3d &)
{
	return normal; // Has to be inverted for some reason
}

FPType Triangle::GetIntersection(const Ray &ray, FPType &u, FPType &v)
{
	Vec3d v0v1 = v1 - v0;
	Vec3d v0v2 = v2 - v0;
	Vec3d pvec = ray.GetDirection().Cross(v0v2);
	FPType det = v0v1.Dot(pvec);

	// ray and triangle are parallel if det is close to 0
	if(abs(det) < BIAS) return false;

	FPType invDet = 1 / det;

	Vec3d tvec = ray.GetOrigin() - v0;
	u = tvec.Dot(pvec) * invDet;
	if(u < 0 || u > 1) return false;

	Vec3d qvec = tvec.Cross(v0v1);
	v = ray.GetDirection().Dot(qvec) * invDet;
	if(v < 0 || u + v > 1) return false;

	FPType t = v0v2.Dot(qvec) * invDet;

	return (t > BIAS) ? t : false;
}