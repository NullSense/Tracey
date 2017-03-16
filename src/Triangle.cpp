#include "Triangle.h"

Triangle::Triangle()
{
	v0 = Vector3d(0, 0, 6);
	v1 = Vector3d(1, 0, 6);
	v2 = Vector3d(1, 1, 6);
	normal = (v1 - v0).Cross(v2 - v0).Normalize();
}

Triangle::Triangle(Vector3d v0_, Vector3d v1_, Vector3d v2_)
	:v0{v0_}, v1{v1_}, v2{v2_}, normal{(v1 - v0).Cross(v2 - v0).Normalize()}
{}

Vector3d Triangle::GetNormal()
{
	Vector3d A = v1 - v0;
	Vector3d B = v2 - v0;
	Vector3d normal = (A.Cross(B)).Normalize(); // normal of the triangle
	return normal;
}

Vector3d Triangle::GetNormalAt(const Vector3d point)
{
	return -normal;
}

FPType Triangle::GetIntersection(Ray ray)
{
	Vector3d rayDir = ray.GetDirection();
	Vector3d rayPos = ray.GetOrigin();

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

	Vector3d Q = rayPos + rayDir * t;

	//Inside-outside test
	Vector3d C; // vector perpendicular to triangle's plane 

	// edge 0
	Vector3d edge0 = v1 - v0;
	Vector3d vp0 = Q - v0;
	C = edge0.Cross(vp0);
	if(normal.Dot(C) < 0)
		return false; // Q is on the right side 

	// edge 1
	Vector3d edge1 = v2 - v1;
	Vector3d vp1 = Q - v1;
	C = edge1.Cross(vp1);
	if(normal.Dot(C) < 0) 
		return false; // Q is on the right side 

	// edge 2
	Vector3d edge2 = v0 - v2;
	Vector3d vp2 = Q - v2;
	C = edge2.Cross(vp2);
	if(normal.Dot(C) < 0)
		return false; // Q is on the right side;

	return t; // this ray hits the triangle 
}
