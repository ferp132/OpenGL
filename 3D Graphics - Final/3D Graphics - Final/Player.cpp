#include "Player.h"
#include "InputManager.h"
#include "GameManager.h"

void Player::ProcessInput()
{
	float RotationSpeeed = 0.1f;
	MaxSpd = 0.2f;
	AccSpd = 0.001f;
	Friction = 0.00025f;
	glm::vec3 Acc = glm::vec3(0.0f);
	Foward =  (QuatRotx * QuatRoty * QuatRotz) * glm::vec3(0.0f, -1.0f, 0.0f);
	upDir = (QuatRotx * QuatRoty * QuatRotz) * glm::vec3(1.0f, 0.0f, 0.0f);

	if (InputManager::Getinstance()->MouseState[MOUSE_LEFT] == DOWN)
	{
		
	}

	if (InputManager::Getinstance()->KeyState['w'] == DOWN)
	{
		Rotx += RotationSpeeed;
	}
	if (InputManager::Getinstance()->KeyState['s'] == DOWN)
	{
		Rotx -= RotationSpeeed;
		
	}
	if (InputManager::Getinstance()->KeyState['d'] == DOWN)
	{
		Rotz += RotationSpeeed;
	}
	if (InputManager::Getinstance()->KeyState['a'] == DOWN)
	{
		Rotz -= RotationSpeeed;
	}
	if (InputManager::Getinstance()->KeyState['x'] == DOWN)
	{
		Roty += RotationSpeeed;
	}
	if (InputManager::Getinstance()->KeyState['z'] == DOWN)
	{
		Roty -= RotationSpeeed;
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
	if (InputManager::Getinstance()->KeyState[' '] == DOWN)
	{
		Velocity -= glm::vec3(AccSpd) * Foward;
		
	}

	if (Velocity.x > 0) Velocity.x -= Friction;
	if (Velocity.x < 0) Velocity.x += Friction;
	if (Velocity.y > 0) Velocity.y -= Friction;
	if (Velocity.y < 0) Velocity.y += Friction;
	if (Velocity.z > 0) Velocity.z -= Friction;
	if (Velocity.z < 0) Velocity.z += Friction;
	Position += Velocity;
}
