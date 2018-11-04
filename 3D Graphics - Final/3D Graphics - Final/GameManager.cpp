#include "GameManager.h"
#include <stdlib.h>     /* srand, rand */
#include <time.h>       /* time */

GameManager* GameManager::Instance = NULL;

GameManager::GameManager()
{

}

GameManager::~GameManager()
{

}

void GameManager::SetScore(int newScore)
{
	Score = newScore;
	ScoreText.SetText("Score: " + to_string(Score));
}

void GameManager::SetLives(int newLives)
{
	Lives = newLives;
	LivesText.SetText("Lives: " + to_string(Lives));
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
	//-----Seed Random
	srand(time(NULL));


	//-----Init Audio
	GetInstance()->AS.Init();

	//-----Init Camera
	GetInstance()->Cam.Init(800, 800, (&GetInstance()->player));


	//----Init Textures
	GetInstance()->CMap.Init(GetInstance()->Cam);


	//----- Init Text Label
	
	GetInstance()->ScoreText.Init(" ", "Resources/Fonts/arial.ttf", glm::vec2(50.0f, 30.0f), glm::vec3(0.5f, 0.8f, 1.0), 1.0f);
	GetInstance()->LivesText.Init(" ", "Resources/Fonts/arial.ttf", glm::vec2(550.0f, 30.0f), glm::vec3(0.5f, 0.8f, 1.0), 1.0f);
	GetInstance()->SetScore(0);
	GetInstance()->SetLives(3);

	//-----Object Init
	Object* NewObject;
	for (int i = 0; i < 3; i++)
	{
		NewObject = new Object;
		GetInstance()->ObVector.push_back(*NewObject);
	}

	for (unsigned int i = 0; i < GetInstance()->ObVector.size(); i++)
	{
		GetInstance()->ObVector.at(i).Init(i, "Resources/Textures/AwesomeFace.png",
			"Resources/Shaders/BlinnPhong.shader",
			glm::vec3(20.0f + 10.0f * i, 0.0f, 0.0f),
			glm::vec3(1.0f, 1.0f, 1.0f));
	}

	//-----Enemy Init
	Enemy* newEn;
	for (int i = 0; i < 10; i++)
	{
		newEn = new Enemy;
		GetInstance()->EnemyVector.push_back(*newEn);
	}
	for (unsigned int i = 0; i < GetInstance()->EnemyVector.size(); i++)
	{
		GetInstance()->EnemyVector.at(i).Init(1, "Resources/Textures/AwesomeFace.png",
			"Resources/Shaders/BlinnPhong.shader",
			glm::vec3(100 - (rand() % 100 + 100), 100 - (rand() % 100 + 100), 100 - (rand() % 100 + 100)),
			glm::vec3(1.0f, 1.0f, 1.0f));
	}

	//-----Player Init
	GetInstance()->player.Init(2, "Resources/Textures/AwesomeFace.png",
		"Resources/Shaders/BlinnPhong.shader",
		glm::vec3(0.0f, 0.0f, 0.0f),
		glm::vec3(1.0f, 1.0f, 1.0f));

	GetInstance()->player.SetBaseFoward(glm::vec3(0.0f, 1.0f, 0.0f));
	GetInstance()->player.SetBaseLeft(glm::vec3(1.0f, 0.0f, 0.0f));
	GetInstance()->player.SetBaseRight(glm::vec3(-1.0f, 0.0f, 0.0f));
	GetInstance()->player.SetBaseUp(glm::vec3(0.0f, 0.0f, 1.0f));
	GetInstance()->player.SetMaxSpd(0.2f);
	GetInstance()->player.SetAccSpd(0.01f);
	GetInstance()->player.SetFriction(0.0025f);
	GetInstance()->player.SetRotSpd(0.1f);
}

void GameManager::Render(void)
{
	GetInstance()->Ren.Clear();
	//Render Objects
	GetInstance()->CMap.Render();
	for (int i = 0; i < GetInstance()->ObVector.size(); i++)
	{
		GetInstance()->ObVector.at(i).Render();
	}
	for (int i = 0; i < GetInstance()->EnemyVector.size(); i++)
	{
		GetInstance()->EnemyVector.at(i).Render();
	}
	GetInstance()->player.Render();

	//Render Text
	GetInstance()->ScoreText.Render();
	GetInstance()->LivesText.Render();

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
	GetInstance()->Cam.ProcessInput();
	GetInstance()->player.ProcessInput();

	//-----Update Camera
	GetInstance()->Cam.Update(GetInstance()->timeElapsed);

	//-----Update Objects
	for (int i = 0; i < GetInstance()->ObVector.size(); i++)
	{
		GetInstance()->ObVector.at(i).Update(GetInstance()->deltaTime);
	}
	for (int i = 0; i < GetInstance()->EnemyVector.size(); i++)
	{
		GetInstance()->EnemyVector.at(i).Update(GetInstance()->deltaTime);
		GetInstance()->EnemyVector.at(i).MoveTo(GetInstance()->player.GetPosition());
	}
	GetInstance()->player.Update(GetInstance()->deltaTime);
	
	

	glutPostRedisplay();

}
