#include "Camera.h"
#include "InputManager.h"

Camera::Camera()
{
}

Camera::~Camera()
{
}

void Camera::Init(float InitWinWidth, float InitWinHeight, Object* Player)
{
	WinWidth = InitWinWidth;
	WinHeight = InitWinHeight;

	Following = Player;
}

void Camera::Update(float deltaTime)
{
	if (PosType)	//true = birdsEye
	{
		CamPos = Following->GetPosition() + Following->GetScale() * glm::vec3(0.5, 0.5, 0.5);
		CamPos.y += 25.0f;
	}
	else
	{
		CamPos = Following->GetPosition() - Following->GetScale() * glm::vec3(0.5, 0.5, 0.5) + Following->GetAppFoward() * glm::vec3(25.0f);
	}
}

void Camera::ProcessInput()
{
}

glm::mat4 Camera::GetPxV()
{
	return GetProjMatrix() * GetViewMatrix();
}

glm::mat4 Camera::GetViewMatrix()
{
	if (PosType)	return glm::lookAt(CamPos, Following->GetPosition() - Following->GetScale() * glm::vec3(0.5, 0.5, 0.5), CamUpDir);
	else			return glm::lookAt(CamPos, Following->GetPosition() - Following->GetScale() * glm::vec3(0.5, 0.5, 0.5), Following->GetUpDir());
}

glm::mat4 Camera::GetProjMatrix()
{
	//return glm::ortho(-400.0f, 400.0f, -400.0f,  400.0f, 0.1f, 100.0f);
	return glm::perspective(45.0f, 1.0f, 1.0f, 10000.0f);

}
