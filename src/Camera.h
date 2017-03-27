#pragma once
#include "Vector3.h"

class Camera
{
public:
	Camera();
	Camera(const Vector3d &from, const Vector3d &to);
	Vector3d GetFrom() const;
	Vector3d GetTo() const;
	Vector3d GetForward() const;
	Vector3d GetRight() const;
	Vector3d GetUp() const;
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