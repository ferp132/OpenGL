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
	//-----Set Current Scene to main menu
	GetInstance()->CurrSc = MENU;

	//-----Time Init
	GetInstance()->previousTimeStamp = (float)glutGet(GLUT_ELAPSED_TIME);
	GetInstance()->timeElapsed = 0;

	//-----Seed Random
	srand(time(NULL));

	//-----Init Audio
	GetInstance()->AS.Init();

	//-----Init Camera
	GetInstance()->Cam.Init(800, 800, (&GetInstance()->MenuOb));

	//----- Init Text Labels
	GetInstance()->LossText.Init("You Lose!!", "Resources/Fonts/arial.ttf", glm::vec2(50.0f, 400.0f), glm::vec3(0.1f, 1.0f, 0.2f), 3.0f);
	GetInstance()->ScoreText.Init(" ", "Resources/Fonts/arial.ttf", glm::vec2(50.0f, 30.0f), glm::vec3(0.5f, 0.8f, 1.0), 1.0f);
	GetInstance()->LivesText.Init(" ", "Resources/Fonts/arial.ttf", glm::vec2(550.0f, 30.0f), glm::vec3(0.5f, 0.8f, 1.0), 1.0f);
	GetInstance()->SetScore(0);
	GetInstance()->SetLives(3);
	GetInstance()->VelocityText.Init(" ", "Resources/Fonts/arial.ttf", glm::vec2(200.0f, 750.0f), glm::vec3(0.1f, 1.0f, 0.2f), 1.0f);

	//-----Objects Init
	//CubeMap
	GetInstance()->CMap.Init(GetInstance()->Cam);

	//Buttons
	GetInstance()->Play.Init	(glm::vec2(100.0f, 500.0f), glm::vec2(2.0f, 2.0f), "Play", "Resources/Fonts/arial.ttf",	glm::vec3(0.1f, 1.0f, 0.2f));
	GetInstance()->Play.SetActive(true);
	GetInstance()->PlayAI.Init	(glm::vec2(100.0f, 350.0f), glm::vec2(2.0f, 2.0f), "Play AI Scene", "Resources/Fonts/arial.ttf", glm::vec3(0.1f, 1.0f, 0.2f));
	GetInstance()->PlayAI.SetActive(true);
	GetInstance()->Exit.Init	(glm::vec2(100.0f, 200.0f), glm::vec2(2.0f, 2.0f), "Exit", "Resources/Fonts/arial.ttf", glm::vec3(0.1f, 1.0f, 0.2f));
	GetInstance()->Exit.SetActive(true);
	GetInstance()->Return.Init	(glm::vec2(200.0f, 200.0f), glm::vec2(1.0f, 1.0f), "Return To Menu", "Resources/Fonts/arial.ttf", glm::vec3(0.1f, 1.0f, 0.2f));
	GetInstance()->Return.SetActive(true);

	//Menu Object
	GetInstance()->MenuOb.Init(0, "Resources/Textures/AwesomeFace.png", "Resources/Shaders/Reflection.shader", glm::vec3(0.0f, 0.0f, 0.0f), glm::vec3(3.0f, 20.0f, 10.0f));
	GetInstance()->MenuOb.SetActive(true);
	GetInstance()->MenuOb.SetBaseFoward(glm::vec3(-1.0f, 0.0f, 0.0f));
	GetInstance()->MenuOb.SetBaseLeft(glm::vec3(-1.0f, 0.0f, 0.0f));
	GetInstance()->MenuOb.SetBaseRight(glm::vec3(1.0f, 0.0f, 0.0f));
	GetInstance()->MenuOb.SetBaseUp(glm::vec3(0.0f, 1.0f, 0.0f));
	GetInstance()->MenuOb.SetRotSpd(0.01f);

	//Player
	GetInstance()->player.Init(2, "Resources/Textures/AwesomeFace.png", "Resources/Shaders/BlinnPhong.shader", glm::vec3(0.0f, 0.0f, 0.0f), glm::vec3(1.0f, 7.5f, 1.0f));

	GetInstance()->player.SetBaseFoward(glm::vec3(0.0f, -1.0f, 0.0f));
	GetInstance()->player.SetBaseLeft(glm::vec3(-1.0f, 0.0f, 0.0f));
	GetInstance()->player.SetBaseRight(glm::vec3(1.0f, 0.0f, 0.0f));
	GetInstance()->player.SetBaseUp(glm::vec3(0.0f, 0.0f, 1.0f));
	GetInstance()->player.SetMaxSpd(20.0f);
	GetInstance()->player.SetAccSpd(1.0f);
	GetInstance()->player.SetFriction(0.25f);
	GetInstance()->player.SetRotSpd(1.0f);




}

void GameManager::Render(void)
{
	//-----ClearScreen
	GetInstance()->Ren.Clear();

	//-----Render CubeMap
	GetInstance()->CMap.Render();

	//-----Render Scene
	switch (GetInstance()->CurrSc)
	{
	case MENU:
	{
		GetInstance()->RenMenu();
		break;
	}
	case PLAY:
	{
		GetInstance()->RenPlay();
		break;
	}
	case PLAYAI:
	{
		GetInstance()->RenAI();
		break;
	}
	case LOSS:
	{
		GetInstance()->RenLoss();
		break;
	}
	}
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

	//-----Update Camera
	GetInstance()->Cam.Update(GetInstance()->timeElapsed);

	switch (GetInstance()->CurrSc)
	{
	case MENU:
	{
		GetInstance()->UpdMenu();
		break;
	}
	case PLAY:
	{
		GetInstance()->UpdPlay();
		break;
	}
	case PLAYAI:
	{
		GetInstance()->UpdAI();
		break;
	}
	case LOSS:
	{
		GetInstance()->UpdLoss();
		break;
	}
	}

	glutPostRedisplay();

}

void GameManager::RenMenu()
{
	//-----Render Object
	GetInstance()->MenuOb.Render();

	//-----Render Buttons
	GetInstance()->Play.Render();
	GetInstance()->PlayAI.Render();
	GetInstance()->Exit.Render();	
}

void GameManager::RenPlay()
{
	//-----Render Objects
	for (int i = 0; i < GetInstance()->ObVec.size(); i++)
	{
		GetInstance()->ObVec.at(i).Render();
	}
	//Enemies
	for (int i = 0; i < GetInstance()->EnVec.size(); i++)
	{
		GetInstance()->EnVec.at(i).Render();
	}
	//Player
	GetInstance()->player.Render();

	//-----Render Text
	GetInstance()->ScoreText.Render();
	GetInstance()->LivesText.Render();
	GetInstance()->VelocityText.Render();
}

void GameManager::RenAI()
{
	//TODO AI Scene
}

void GameManager::RenLoss()
{
	//-----Render Objects
	for (int i = 0; i < GetInstance()->ObVec.size(); i++)
	{
		GetInstance()->ObVec.at(i).Render();
	}
	//Enemies
	for (int i = 0; i < GetInstance()->EnVec.size(); i++)
	{
		GetInstance()->EnVec.at(i).Render();
	}
	//Player
	GetInstance()->player.Render();
	GetInstance()->LossText.Render();
	GetInstance()->Return.Render();
}

void GameManager::UpdMenu()
{
	GetInstance()->Play.Update();
	GetInstance()->PlayAI.Update();
	GetInstance()->Exit.Update();

	if (GetInstance()->Play.GetClicked())
	{
		CurrSc = PLAY;
		InstPlay();
		Cam.SetFollowing(&player);
		Cam.SetRotFollow(true);
		GetInstance()->SetLives(3);
		GetInstance()->Play.SetClicked(false);
	}
	if (GetInstance()->PlayAI.GetClicked()) CurrSc = PLAYAI;

	GetInstance()->MenuOb.RotateOnAxis(glm::vec3(0.0f, 1.0f, 0.0f));
	GetInstance()->MenuOb.Update(deltaTime);
}

void GameManager::UpdPlay()
{
	//-----Process Input
	GetInstance()->player.ProcessInput(deltaTime);

	//-----Update Objects
	for (int i = 0; i < GetInstance()->ObVec.size(); i++)
	{
		GetInstance()->ObVec.at(i).Update(GetInstance()->deltaTime);
	}
	//Enemies
	for (int i = 0; i < GetInstance()->EnVec.size(); i++)
	{
		GetInstance()->EnVec.at(i).Update(GetInstance()->deltaTime);
		GetInstance()->EnVec.at(i).MoveTo(GetInstance()->player.GetPosition());
	}
	//Player
	GetInstance()->player.Update(GetInstance()->deltaTime);
	//-----Update Text
	SetVel();

	if (GetInstance()->Lives == 0)
	{
		CurrSc = LOSS;
	}
}

void GameManager::UpdAI()
{
	//-----Process Input
	GetInstance()->player.ProcessInput(deltaTime);
}

void GameManager::UpdLoss()
{
	GetInstance()->Return.ProcessInput();
	if (GetInstance()->Return.GetClicked())
	{
		GetInstance()->CurrSc = MENU;
		GetInstance()->Cam.SetFollowing(&MenuOb);
		GetInstance()->Cam.SetRotFollow(false);

		GetInstance()->ObVec.clear();
		GetInstance()->EnVec.clear();
		GetInstance()->player.SetPosition(glm::vec3(0.0f));
	}
}

void GameManager::InstPlay()
{
	//Basic Objects
	Object* NewObject;
	for (int i = 0; i < 10; i++)
	{
		NewObject = new Object;
		GetInstance()->ObVec.push_back(*NewObject);
	}

	for (unsigned int i = 0; i < GetInstance()->ObVec.size(); i++)
	{
		GetInstance()->ObVec.at(i).Init((rand() % 3), "Resources/Textures/AwesomeFace.png",
			"Resources/Shaders/BlinnPhong.shader",
			glm::vec3(1000 - (rand() % 1000 + 1000), 1000 - (rand() % 1000 + 1000), 1000 - (rand() % 1000 + 1000)),
			glm::vec3((rand() % 250), (rand() % 250), (rand() % 250)));
	}

	//Enemies
	Enemy* newEn;
	for (int i = 0; i < 10; i++)
	{
		newEn = new Enemy;
		GetInstance()->EnVec.push_back(*newEn);
	}
	for (unsigned int i = 0; i < GetInstance()->EnVec.size(); i++)
	{
		GetInstance()->EnVec.at(i).Init(1, "Resources/Textures/AwesomeFace.png",
			"Resources/Shaders/BlinnPhong.shader",
			glm::vec3(100 - (rand() % 100 + 100), 100 - (rand() % 100 + 100), 100 - (rand() % 100 + 100)),
			glm::vec3(3.0f, 3.0f, 3.0f));
	}

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

void GameManager::SetVel()
{
	glm::vec3 Vel = GetInstance()->player.GetVelocity();
	float Velocity = abs(Vel.x + Vel.y + Vel.z);
	VelocityText.SetText("Velocity: " + to_string(Velocity));
}
