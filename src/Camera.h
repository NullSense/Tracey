#pragma once
#include "Vector.h"
#include "Ray.h"

class Camera
{
public:
	Camera();
	Camera(const Vector &from, const Vector &to);
	Vector GetFrom();
	Vector GetTo();
	Vector GetForward();
	Vector GetRight();
	Vector GetUp();
	void SetTo(const Vector &to_);
	
private:
	Vector from;
	Vector to;
	Vector tmp = Vector(0, 1, 0);

	// Camera coordinates
	Vector forward = (from - to).Normalize(); // Where camera's view is centered
	Vector right = (tmp.Normalize()).Cross(forward);
	Vector up = forward.Cross(right);
};

Camera::Camera()
	:from {0, 0, 0}, to {0, 0, -1}
{}

inline Camera::Camera(const Vector &from, const Vector &to)
	: from(from), to(to)
{}

inline Vector Camera::GetFrom()
{
	return from;
}

inline Vector Camera::GetTo()
{
	return to;
}

inline Vector Camera::GetForward()
{
	return forward;
}

inline Vector Camera::GetRight()
{
	return right;
}

inline Vector Camera::GetUp()
{
	return up;
}

void Camera::SetTo(const Vector &to_)
{
	to = to_;
}
