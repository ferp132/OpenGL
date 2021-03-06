#include "Camera.h"

Camera::Camera()
{
}

Camera::~Camera()
{
}

void Camera::Init(float InitWinWidth, float InitWinHeight)
{
	WinWidth = InitWinWidth;
	WinHeight = InitWinHeight;
}

glm::mat4 Camera::GetPxV()
{
	return GetProjMatrix() * GetViewMatrix();
}

glm::mat4 Camera::GetViewMatrix()
{
	return glm::lookAt(CamPos, CamPos + CamLookDir, CamUpDir);
	//return  glm::translate(glm::mat4(1.0f), glm::vec3(0, 0, -1));
}

glm::mat4 Camera::GetProjMatrix()
{
	return glm::ortho(-400.0f, 400.0f, -400.0f,  400.0f, 0.1f, 100.0f);
}
