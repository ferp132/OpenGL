#include "Camera.h"

Camera::Camera()
{
}

Camera::~Camera()
{
}

void Camera::Init(float InitWinWidth, float InitWinHeight, Cube* Player)
{
	WinWidth = InitWinWidth;
	WinHeight = InitWinHeight;

	Following = Player;
}

void Camera::Update(float deltaTime)
{
	float radius = 10.0f;
	CamPos.y = (Following->GetHeight() / 2) + Following->GetyPos() + 5.0f;
	CamPos.x = Following->GetxPos() - Following->GetWidth()/2 - 10  ;
	CamPos.z = Following->GetzPos() + Following->GetLength()/2		;
}

void Camera::ProcessInput()
{
	if (InputManager::Getinstance()->KeyState['q'] == DOWN)
	{
		Rotation += 0.1f;
	}
	if (InputManager::Getinstance()->KeyState['e'] == DOWN)
	{
		Rotation -= 0.1f;
	}
}

glm::mat4 Camera::GetPxV()
{
	return GetProjMatrix() * GetViewMatrix();
}

glm::mat4 Camera::GetViewMatrix()
{
	return glm::lookAt(CamPos, glm::vec3(Following->GetxPos() + Following->GetWidth()/2, Following->GetyPos() + Following->GetHeight()/2, Following->GetzPos() + Following->GetLength()/2), CamUpDir);
	//return glm::lookAt(CamPos, CamLookDir, CamUpDir);
	//return  glm::translate(glm::mat4(1.0f), glm::vec3(0, 0, -1));
}

glm::mat4 Camera::GetProjMatrix()
{
	//return glm::ortho(-400.0f, 400.0f, -400.0f,  400.0f, 0.1f, 100.0f);
	return glm::perspective(45.0f, 1.0f, 1.0f, 10000.0f);

}
