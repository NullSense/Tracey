#include "Triangle.h"

Triangle::Triangle()
{
	v0 = Vector3(0, 0, 6);
	v1 = Vector3(1, 0, 6);
	v2 = Vector3(1, 1, 6);
	normal = (v1 - v0).Cross(v2 - v0).Normalize();
}

Triangle::Triangle(Vector3 v0_, Vector3 v1_, Vector3 v2_)
	:v0{v0_}, v1{v1_}, v2{v2_}, normal{(v1 - v0).Cross(v2 - v0).Normalize()}
{}

Vector3 Triangle::GetNormal()
{
	Vector3 A = v1 - v0;
	Vector3 B = v2 - v0;
	Vector3 normal = (A.Cross(B)).Normalize(); // normal of the triangle
	return normal;
}

Vector3 Triangle::GetNormalAt(const Vector3 point)
{
	return -normal;
}

FPType Triangle::GetIntersection(Ray ray)
{
	Vector3 rayDir = ray.GetDirection();
	Vector3 rayPos = ray.GetOrigin();

	FPType NdotRayDirection = normal.Dot(rayDir);
	
	// check if ray and plane are parallel
	if(NdotRayDirection < BIAS)
		return false;
	FPType D = normal.Dot(v0); // Dist from point to plane
	FPType b = normal.Dot(rayPos + (normal * (-D)));
	//FPType b = (normal.Dot(rayPos) + D); // scratch
	FPType t = (-b / NdotRayDirection);
	//FPType t = b / NdotRayDirection; // scratch

	if(t < 0)
		return false; // the triangle is behind 

	Vector3 Q = rayPos + rayDir * t;

	//Inside-outside test
	Vector3 C; // vector perpendicular to triangle's plane 

	// edge 0
	Vector3 edge0 = v1 - v0;
	Vector3 vp0 = Q - v0;
	C = edge0.Cross(vp0);
	if(normal.Dot(C) < 0)
		return false; // Q is on the right side 

	// edge 1
	Vector3 edge1 = v2 - v1;
	Vector3 vp1 = Q - v1;
	C = edge1.Cross(vp1);
	if(normal.Dot(C) < 0) 
		return false; // Q is on the right side 

	// edge 2
	Vector3 edge2 = v0 - v2;
	Vector3 vp2 = Q - v2;
	C = edge2.Cross(vp2);
	if(normal.Dot(C) < 0)
		return false; // Q is on the right side;

	return t; // this ray hits the triangle 
}
