#pragma once
#include "Vector.h"
#include "Ray.h"

class Camera
{
public:
	Camera();
	Camera(const Vector &origin, const Vector &direction);
	Vector GetOrigin();
	Vector GetSceneDirection();
	Vector GetCameraDirection();
	Vector GetCamX();
	Vector GetCamY();
	void SetSceneDirection(const Vector &dir);
	
private:
	Vector origin;
	// Where the camera looks at in the scene
	Vector sceneDirection;

	// Where camera's view is centered
	Vector camDirection = (GetSceneDirection() - GetOrigin()).Normalize();

	// camX and Y represent the 2D coordinate system on the IMAGE plane
	Vector camX = Vector(0, 1, 0).Cross(GetCameraDirection()).Normalize();
	Vector camY = camX.Cross(GetCameraDirection());
};

Camera::Camera()
	:origin {0, 0, 0}, sceneDirection {0, 0, 1}
{}

inline Camera::Camera(const Vector &origin, const Vector &sceneDirection)
	: origin(origin), sceneDirection(sceneDirection)
{}

inline Vector Camera::GetOrigin()
{
	return origin;
}

inline Vector Camera::GetSceneDirection()
{
	return sceneDirection;
}

inline Vector Camera::GetCameraDirection()
{
	return camDirection;
}

inline Vector Camera::GetCamX()
{
	return camX;
}

inline Vector Camera::GetCamY()
{
	return camY;
}

void Camera::SetSceneDirection(const Vector &dir)
{
	sceneDirection = dir;
}
