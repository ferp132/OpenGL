#include "ControlledObject.h"

void ControlledObject::ProcessInput(float deltaTime)
{
	glm::vec3 MoveVec(0.0f, 0.0f, 0.0f);

	if (InputManager::Getinstance()->MouseState[MOUSE_LEFT] == DOWN)
	{
		
	}

	if (InputManager::Getinstance()->KeyState['w'] == DOWN)
	{
		yPos += 5.0f;
	}
	if (InputManager::Getinstance()->KeyState['s'] == DOWN)
	{
		yPos -= 5.0f;
	}
	if (InputManager::Getinstance()->KeyState['d'] == DOWN)
	{
		xPos += 5.0f;
	}
	if (InputManager::Getinstance()->KeyState['a'] == DOWN)
	{
		xPos -= 5.0f;
	}
	if (InputManager::Getinstance()->KeyState['w'] == DOWN)
	{
		yPos += 5.0f;
	}
	if (InputManager::Getinstance()->KeyState['q'] == DOWN)
	{
		Dir += 1.0f;
	}
	if (InputManager::Getinstance()->KeyState['e'] == DOWN)
	{
		Dir -= 1.0f;
	}

	if (Dir > 360) Dir = 0;
	else if (Dir < 0) Dir = 360;

	UpdateModel();
}
