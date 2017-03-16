#pragma once
#include "Vector3.h"
#include "Ray.h"

class Camera
{
public:
	Camera();
	Camera(const Vector3d &from, const Vector3d &to);
	Vector3d GetFrom();
	Vector3d GetTo();
	Vector3d GetForward();
	Vector3d GetRight();
	Vector3d GetUp();
	void SetTo(const Vector3d &to_);
	
private:
	Vector3d from;
	Vector3d to;
	Vector3d tmp = Vector3d(0, 1, 0);

	// Camera coordinates
	Vector3d forward = (from - to).Normalize(); // Where camera's view is centered
	Vector3d right = (tmp.Normalize()).Cross(forward);
	Vector3d up = forward.Cross(right);
};

Camera::Camera()
	:from {0}, to {0, 0, -1}
{}

inline Camera::Camera(const Vector3d &from, const Vector3d &to)
	: from(from), to(to)
{}

inline Vector3d Camera::GetFrom()
{
	return from;
}

inline Vector3d Camera::GetTo()
{
	return to;
}

inline Vector3d Camera::GetForward()
{
	return forward;
}

inline Vector3d Camera::GetRight()
{
	return right;
}

inline Vector3d Camera::GetUp()
{
	return up;
}

void Camera::SetTo(const Vector3d &to_)
{
	to = to_;
}
