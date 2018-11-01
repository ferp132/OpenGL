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

	Movx = 0.0f;
	Movy = 0.0f;
	Movz = 0.0f;
}

void Camera::Update(float deltaTime)
{
	float radius = 9.0f;
	CamPos.y = 50.0f;
	CamPos.x = sin(deltaTime) * radius * 10;
	CamPos.z = cos(deltaTime) * radius * 10;
}

void Camera::ProcessInput()
{
	if (InputManager::Getinstance()->KeyState['w'] == DOWN)
	{
		Movy += 1.0f;
	}
	if (InputManager::Getinstance()->KeyState['s'] == DOWN)
	{
		Movy -= 1.0f;
	}
	if (InputManager::Getinstance()->KeyState['d'] == DOWN)
	{
		Movx += 1.0f;
	}
	if (InputManager::Getinstance()->KeyState['a'] == DOWN)
	{
		Movx -= 1.0f;
	}

	CamLookDir.y = Movy;
	CamLookDir.x = Movx;
	CamLookDir.z = Movz;

}

glm::mat4 Camera::GetPxV()
{
	return GetProjMatrix() * GetViewMatrix();
}

glm::mat4 Camera::GetViewMatrix()
{
	//return glm::lookAt(CamPos, glm::vec3(0.0f, 0.0f, 0.0f), CamUpDir);
	return glm::lookAt(CamPos, CamLookDir, CamUpDir);
	//return  glm::translate(glm::mat4(1.0f), glm::vec3(0, 0, -1));
}

glm::mat4 Camera::GetProjMatrix()
{
	//return glm::ortho(-400.0f, 400.0f, -400.0f,  400.0f, 0.1f, 100.0f);
	return glm::perspective(45.0f, 1.0f, 10.0f, 10000.0f);

}
