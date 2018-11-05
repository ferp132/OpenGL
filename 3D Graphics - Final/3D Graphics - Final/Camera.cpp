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
	PosType = false;
	RotbyFollowing = false;
}

void Camera::Update(float deltaTime)
{
	if (PosType)	//true = birdsEye
	{
		CamPos = Following->GetCenter();
		CamPos.y += 25.0f;
	}
	else
	{
		if(RotbyFollowing)	CamPos = Following->GetCenter() + Following->GetAppFoward() * glm::vec3(25.0f);
		else
		{
			float radius = 10.0f;
			CamPos = Following->GetCenter() - Following->GetBaseFoward() * glm::vec3(25.0f) + Following->GetVelocity();
		}
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
	if (PosType)	return glm::lookAt(CamPos, Following->GetCenter(), CamUpDir);
	else			return glm::lookAt(CamPos, Following->GetCenter(), Following->GetUpDir());
}

glm::mat4 Camera::GetProjMatrix()
{
	//return glm::ortho(-400.0f, 400.0f, -400.0f,  400.0f, 0.1f, 100.0f);
	return glm::perspective(45.0f, 1.0f, 1.0f, 100000.0f);

}
