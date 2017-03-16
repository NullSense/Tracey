#pragma once
#include "Vector3.h"
#include "Ray.h"

class Camera
{
public:
	Camera();
	Camera(const Vector3 &from, const Vector3 &to);
	Vector3 GetFrom();
	Vector3 GetTo();
	Vector3 GetForward();
	Vector3 GetRight();
	Vector3 GetUp();
	void SetTo(const Vector3 &to_);
	
private:
	Vector3 from;
	Vector3 to;
	Vector3 tmp = Vector3(0, 1, 0);

	// Camera coordinates
	Vector3 forward = (from - to).Normalize(); // Where camera's view is centered
	Vector3 right = (tmp.Normalize()).Cross(forward);
	Vector3 up = forward.Cross(right);
};

Camera::Camera()
	:from {0}, to {0, 0, -1}
{}

inline Camera::Camera(const Vector3 &from, const Vector3 &to)
	: from(from), to(to)
{}

inline Vector3 Camera::GetFrom()
{
	return from;
}

inline Vector3 Camera::GetTo()
{
	return to;
}

inline Vector3 Camera::GetForward()
{
	return forward;
}

inline Vector3 Camera::GetRight()
{
	return right;
}

inline Vector3 Camera::GetUp()
{
	return up;
}

void Camera::SetTo(const Vector3 &to_)
{
	to = to_;
}
