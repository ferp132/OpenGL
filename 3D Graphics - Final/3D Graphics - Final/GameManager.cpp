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
	//-----Time Init
	GetInstance()->previousTimeStamp = (float)glutGet(GLUT_ELAPSED_TIME);
	GetInstance()->timeElapsed = 0;


	//-----Init Audio
	GetInstance()->AS.Init();
	GetInstance()->fxThump = GetInstance()->AS.CreateSound("Resources/Sounds/Thump.wav", GetInstance()->fxThump);
	GetInstance()->trackBackground = GetInstance()->AS.CreateSound("Resources/Sounds/Background.mp3", GetInstance()->trackBackground);
	GetInstance()->AS.PlaySound(GetInstance()->trackBackground);															//Play Background Track


	//-----Init Camera
	GetInstance()->Cam.Init(800, 800, (&GetInstance()->cube));


	//----Init Textures
	GetInstance()->CMap.Init(GetInstance()->Cam);


	//----- Init Text Label
	GetInstance()->label.Init("Score: 0", "Resources/Fonts/arial.ttf", glm::vec2(50.0f, 30.0f), glm::vec3(0.5f, 0.8f, 1.0), 1.0f);


	//-----Object Init

	GetInstance()->Pyr.Init(0, -25, 0, 5, 5, 5, "Resources/Textures/AwesomeFace.png");
	GetInstance()->cube.Init(0, 25, 0, 2, 2, 2, "Resources/Textures/AwesomeFace.png");
	GetInstance()->Sphr.Init(0, 0, 0, 5, 5, 5, "Resources/Textures/AwesomeFace.png");
	GetInstance()->Platform.Init(0, -10, -500, 10, 1000, 1000, "Resources/Textures/AwesomeFace.png");
}

void GameManager::Render(void)
{
	GetInstance()->Ren.Clear();


	//Render Objects
	GetInstance()->CMap.Render();
	GetInstance()->Pyr.Render();
	GetInstance()->cube.Render();
	GetInstance()->Sphr.Render();
	GetInstance()->Platform.Render();
	
	
	//Render Text
	GetInstance()->label.Render();

	glutSwapBuffers();
}

void GameManager::Update()
{
	//-----Update Time
	float currentTime = (float)glutGet(GLUT_ELAPSED_TIME);
	GetInstance()->deltaTime = (currentTime - GetInstance()->previousTimeStamp) * 0.001f;
	GetInstance()->previousTimeStamp = currentTime;
	GetInstance()->timeElapsed += GetInstance()->deltaTime;

	//-----Update Audio System
	GetInstance()->AS.GetID()->update();

	//-----Update CubeMap
	GetInstance()->CMap.Update();

	//ProcessInput
	GetInstance()->cube.ProcessInput(GetInstance()->deltaTime);
	GetInstance()->Cam.ProcessInput();

	//-----Update Camera
	GetInstance()->Cam.Update(GetInstance()->timeElapsed);

	glutPostRedisplay();

}
