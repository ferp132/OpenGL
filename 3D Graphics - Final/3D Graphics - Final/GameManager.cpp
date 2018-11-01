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
	GetInstance()->Cam.Init(800, 800);

	//----Init Textures
	
	GetInstance()->CMap.Init(GetInstance()->Cam);

	////----- Shader Init
	//GetInstance()->ShadB.Init("Resources/Shaders/Basic.shader");
	//GetInstance()->ShadB.Bind();
	//GetInstance()->ShadB.setUniform1i("u_Texture", 0);						//Set Texture Uniform
	//GetInstance()->ShadB.Unbind();											//Stop using Shader

	//GetInstance()->ShadL.Init("Resources/Shaders/Lighting.shader");
	//GetInstance()->ShadL.Bind();
	//GetInstance()->ShadL.setUniform1i("u_Texture", 0);						//Set Texture Uniform
	//GetInstance()->ShadL.Unbind();											//Stop using Shader

	//----- Init Text Label
	GetInstance()->label.Init("Score: 0", "Resources/Fonts/arial.ttf", glm::vec2(50.0f, 30.0f), glm::vec3(0.5f, 0.8f, 1.0), 1.0f);


	//-----Object Init

	GetInstance()->Pyr.Init(0, -25, 0, 50, 50, 50, "Resources/Textures/AwesomeFace.png");
	GetInstance()->Cube.Init(0, 25, 0, 20, 20, 20, "Resources/Textures/AwesomeFace.png");

}

void GameManager::Render(void)
{
	GetInstance()->Ren.Clear();


	//Render Objects
	//GetInstance()->Background.Render();

	GetInstance()->CMap.Render();
	GetInstance()->Pyr.Render();
	GetInstance()->Cube.Render();
	
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

	//-----Update Camera
	GetInstance()->Cam.Update(GetInstance()->timeElapsed);
	GetInstance()->Cam.ProcessInput();

	//-----Update CubeMap
	GetInstance()->CMap.Update();


	glutPostRedisplay();

}
