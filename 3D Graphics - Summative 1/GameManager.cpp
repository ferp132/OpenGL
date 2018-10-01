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



	//----Init Texture
	GetInstance()->Tex.Init("Resources/Textures/AwesomeFace.png");


	//----- Shader Init
	GetInstance()->Shad.Init("Resources/Shaders/Basic.shader");
	GetInstance()->Shad.Bind();
	GetInstance()->Shad.setUniform1i("u_Texture", 0);						//Set Texture Uniform
	GetInstance()->Shad.Unbind();											//Stop using Shader

	//----- Init Text Label
	GetInstance()->label.Init("Yeet", "Resources/Fonts/arial.ttf", glm::vec2(100.0f, 700.0f), glm::vec3(1.0, 1.0, 1.0), 1.0f);


	//-----Object Init
	GetInstance()->ob.Init(0, 0, 300, 300, "Resources/Textures/Rayman.jpg");

	GetInstance()->ob2.Init(0, 0, 200, 200, "Resources/Textures/Rayman.jpg");

	GetInstance()->ob3.Init(0, 0, 300, 300, "Resources/Textures/Rayman.jpg");

}

void GameManager::Render(void)
{
	GetInstance()->Ren.Clear();



	//Render Objects
	GetInstance()->ob3.Render();
	GetInstance()->ob.Render();
	GetInstance()->ob2.Render();
	
	//REnder TExt
	GetInstance()->label.Render();

	glutSwapBuffers();
}

void GameManager::Update()
{
	//Uodate Audio System
	GetInstance()->AS.GetID()->update();

	glutPostRedisplay();

}
