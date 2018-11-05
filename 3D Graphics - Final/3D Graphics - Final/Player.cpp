#include "Player.h"
#include "InputManager.h"
#include "GameManager.h"

void Player::ProcessInput(float deltaTime)
{
	if (InputManager::Getinstance()->MouseState[MOUSE_LEFT] == DOWN)
	{	
	}

	//-----X axis Rotation
	if (InputManager::Getinstance()->KeyState['w'] == DOWN)
	{
		Rotx += RotSpd * deltaTime;
	}
	if (InputManager::Getinstance()->KeyState['s'] == DOWN)
	{
		Rotx -= RotSpd * deltaTime;
	}
	//-----Z axis Rotation
	if (InputManager::Getinstance()->KeyState['d'] == DOWN)
	{
		Rotz -= RotSpd * deltaTime;
	}
	if (InputManager::Getinstance()->KeyState['a'] == DOWN)
	{
		Rotz += RotSpd * deltaTime;
	}
	//-----Y axis Rotation
	if (InputManager::Getinstance()->KeyState['x'] == DOWN)
	{
		Roty += RotSpd * deltaTime;
	}
	if (InputManager::Getinstance()->KeyState['z'] == DOWN)
	{
		Roty -= RotSpd * deltaTime;
	}
	//-----Foward Thrust
	if (InputManager::Getinstance()->KeyState[' '] == DOWN)
	{
		Velocity -= glm::vec3(AccSpd) * AppFoward;

	}
	//-----Strafe Thrust
	if (InputManager::Getinstance()->KeyState['q'] == DOWN)
	{
		Velocity -= glm::vec3(AccSpd) * AppLeft;

	}
	if (InputManager::Getinstance()->KeyState['e'] == DOWN)
	{
		Velocity -= glm::vec3(AccSpd) * AppRight;

	}
	//-----Change Camera (and Play Sound
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
	if (InputManager::Getinstance()->KeyState['t'] == DOWN)
	{
		GameManager::GetInstance()->SetLives(0);
	}


	if (Velocity.x > 0) Velocity.x -= Friction;
	if (Velocity.x < 0) Velocity.x += Friction;
	if (Velocity.y > 0) Velocity.y -= Friction;
	if (Velocity.y < 0) Velocity.y += Friction;
	if (Velocity.z > 0) Velocity.z -= Friction;
	if (Velocity.z < 0) Velocity.z += Friction;
}
