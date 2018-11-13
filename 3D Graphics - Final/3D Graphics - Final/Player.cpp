#include "Player.h"
#include "InputManager.h"
#include "GameManager.h"
#include "Mesh_Pyramid.h"

Player::Player()
{
	mesh		= new PyramidMesh("Resources/Textures/AwesomeFace.png", "Resources/Shaders/BlinnPhong.shader");
	Position	= glm::vec3(0.0f, 0.0f, 0.0f);
	Scale = glm::vec3(1.0f, 7.5f, 1.0f);
	Velocity	= glm::vec3(0.0f, 0.0f, 0.0f);

	//-----Rotation
	Rotx = 0.0f;
	Roty = 0.0f;
	Rotz = 0.0f;

	BaseFoward = glm::vec3(0.0f, 1.0f, 0.0f);
	BaseLeft = glm::vec3(-1.0f, 0.0f, 0.0f);
	BaseRight = glm::vec3(1.0f, 0.0f, 0.0f);
	BaseUpDir = glm::vec3(0.0f, 0.0f, 1.0f);
	RotSpd = 0.5f;
	MaxSpd = 20.0f;
	AccSpd = 1.0f;
	Friction = 0.2f;
}

Player::~Player()
{
}

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
		Acceleration -= glm::vec3(AccSpd) * AppFoward;

	}
	//-----Strafe Thrust
	if (InputManager::Getinstance()->KeyState['q'] == DOWN)
	{
		Acceleration -= glm::vec3(AccSpd) * AppLeft;

	}
	if (InputManager::Getinstance()->KeyState['e'] == DOWN)
	{
		Acceleration -= glm::vec3(AccSpd) * AppRight;

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
