#include "GameManager.h"

GameManager* GameManager::Instance = NULL;

GameManager::GameManager()
{

}

GameManager::~GameManager()
{

}

GameManager * GameManager::GetInstance()
{
	if (Instance == NULL)
	{
		Instance = new GameManager();
	}

	return Instance;
}

void GameManager::Init()
{


	//-----Init Audio
	GetInstance()->AS.Init();
	GetInstance()->fxThump = GetInstance()->AS.CreateSound("Resources/Sounds/Thump.wav", GetInstance()->fxThump);
	GetInstance()->trackBackground = GetInstance()->AS.CreateSound("Resources/Sounds/Background.mp3", GetInstance()->trackBackground);
	GetInstance()->AS.PlaySound(GetInstance()->trackBackground);															//Play Background Track

	//-----Init Camera
	GetInstance()->Cam.Init(800, 800);

	//----Init Textures
	


	//----- Shader Init
	GetInstance()->Shad.Init("Resources/Shaders/Basic.shader");
	GetInstance()->Shad.Bind();
	GetInstance()->Shad.setUniform1i("u_Texture", 0);						//Set Texture Uniform
	GetInstance()->Shad.Unbind();											//Stop using Shader

	//----- Init Text Label
	GetInstance()->label.Init("Score: 0", "Resources/Fonts/arial.ttf", glm::vec2(50.0f, 30.0f), glm::vec3(0.5f, 0.8f, 1.0), 1.0f);


	//-----Object Init
	GetInstance()->Player.Init(0, 0, 100, 100, "Resources/Textures/spaceship.png");
	GetInstance()->Background.Init(0, 0, 800, 800, "Resources/Textures/SpaceBackground.png");



}

void GameManager::Render(void)
{
	GetInstance()->Ren.Clear();


	//Render Objects
	GetInstance()->Background.Render();

	
	GetInstance()->Player.Render();
	
	//Render Text
	GetInstance()->label.Render();

	glutSwapBuffers();
}

void GameManager::Update()
{
	//Uodate Audio System
	GetInstance()->AS.GetID()->update();
	GetInstance()->Player.ProcessInput();


	glutPostRedisplay();

}
