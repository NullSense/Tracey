#include "Camera.h"

Camera::Camera()
	:from{ 0 }, to{ 0, 0, -1 }
{}

Camera::Camera(const Vector3d &from, const Vector3d &to)
	: from(from), to(to)
{}

Vector3d Camera::GetFrom() const
{
	return from;
}

Vector3d Camera::GetTo() const
{
	return to;
}

Vector3d Camera::GetForward() const
{
	return forward;
}

Vector3d Camera::GetRight() const
{
	return right;
}

Vector3d Camera::GetUp() const
{
	return up;
}

void Camera::SetTo(const Vector3d &to_)
{
	to = to_;
}
