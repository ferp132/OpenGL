#include "Player.h"
#include "InputManager.h"
#include "GameManager.h"

void Player::ProcessInput()
{
	MaxSpd = 0.2f;
	AccSpd = 0.005f;
	Friction = 0.00025f;
	glm::vec3 Acc = glm::vec3(0.0f);

	if (InputManager::Getinstance()->MouseState[MOUSE_LEFT] == DOWN)
	{

	}

	if (InputManager::Getinstance()->KeyState['w'] == DOWN)
	{
		Acc.x += 1.0f;
	}
	if (InputManager::Getinstance()->KeyState['s'] == DOWN)
	{
		Acc.x -= 1.0f;
	}
	if (InputManager::Getinstance()->KeyState['d'] == DOWN)
	{
		Acc.z += 1.0f;
	}
	if (InputManager::Getinstance()->KeyState['a'] == DOWN)
	{
		Acc.z -= 1.0f;
	}
	if (InputManager::Getinstance()->KeyState['x'] == DOWN)
	{
		Acc.y += 1.0f;
	}
	if (InputManager::Getinstance()->KeyState['z'] == DOWN)
	{
		Acc.y -= 1.0f;
	}
	if (InputManager::Getinstance()->KeyState['r'] == DOWN && PlayingFX == false)
	{
		PlayingFX = true;
		GameManager::GetInstance()->GetAS()->PlaySFX();
		GameManager::GetInstance()->GetCam()->setPosType(!GameManager::GetInstance()->GetCam()->getPosType());
	}
	if (InputManager::Getinstance()->KeyState['r'] == UP)
	{
		PlayingFX = false;
	}

	if (Acc.x != 0 || Acc.y != 0 || Acc.z != 0)
	{
		Dir = glm::normalize(Acc);
		Velocity += Dir * glm::vec3(AccSpd);
		Velocity -= Dir * glm::vec3(Friction);
		Velocity = glm::clamp(Velocity, glm::vec3(-MaxSpd), glm::vec3(MaxSpd));
	}

	Position += Velocity;
}
