#include "Camera.h"
//=======================================================================
float cam_speed; // amount in pixels
int	cam_level;
//=======================================================================
int Camera::getCamLevel()
{
	return cam_level;
}
//=======================================================================
float Camera::getCamSpeed()
{
	return cam_speed;
}
//=======================================================================
void Camera::setCamLevel(int value)
{
	cam_level = value;
}
//=======================================================================
void Camera::setCamSpeed(float value)
{
	cam_speed = value;
}
//=======================================================================
void Camera::stop()
{
	cam_speed = 0;
	cam_level = 0;
}
