#include "Triangle.h"

Triangle::Triangle()
{
	v0 = Vector(0, 0, 6);
	v1 = Vector(1, 0, 6);
	v2 = Vector(1, 1, 6);
	normal = GetNormal(v0, v1, v2);
}

Vector Triangle::GetNormal(Vector v0, Vector v1, Vector v2)
{
	Vector A = v1 - v0;
	Vector B = v2 - v0;
	Vector C = (A.Cross(B)).Normalize(); // normal of the triangle
	return C;
}

Vector Triangle::GetNormalAt(const Vector point)
{
	return GetNormal(v0, v1, v2);
}

FPType Triangle::GetIntersection(Ray ray)
{

	// check if ray and plane are parallel ?
	FPType NdotRayDirection = normal.Dot(ray.GetDirection());
	if(fabs(NdotRayDirection) < BIAS) // almost 0 
		return false; // they are parallel so they don't intersect ! 

	FPType D = normal.Dot(v0); // Dist from point to plane
	FPType t = (normal.Dot(ray.GetOrigin()) + D) / (normal.Dot(ray.GetDirection()));
	if(t < 0)
		return false; // the triangle is behind 
	Vector P = ray.GetOrigin() + ray.GetDirection()*t;
	
	//Inside-outside test
	Vector C; // vector perpendicular to triangle's plane 

	// edge 0
	Vector edge0 = v1 - v0;
	Vector vp0 = P - v0;
	C = edge0.Cross(vp0);
	if(normal.Dot(C) < 0)
		return false; // P is on the right side 

	// edge 1
	Vector edge1 = v2 - v1;
	Vector vp1 = P - v1;
	C = edge1.Cross(vp1);
	if(normal.Dot(C) < 0) 
		return false; // P is on the right side 

	// edge 2
	Vector edge2 = v0 - v2;
	Vector vp2 = P - v2;
	C = edge2.Cross(vp2);
	if(normal.Dot(C) < 0)
		return false; // P is on the right side; 

	return t; // this ray hits the triangle 
}
