#pragma once
/*
//-----glm for OpenGL Maths
#include "Dependencies\glm\glm.hpp"
#include "Dependencies\glm\gtc\matrix_transform.hpp"
#include "Dependencies\glm\gtc\type_ptr.hpp"


#include "Dependencies\glew\glew.h"
#include "Dependencies\freeglut\freeglut.h"
*/

#include "AudioSystem.h"
#include "TextLabel.h"

#include "Camera.h"
#include "CubeMap.h"
#include "Object.h"
#include "Player.h"
#include "Enemy.h"
#include "Button.h"

enum Scene {MENU, PLAY, PLAYAI, LOSS};

class GameManager
{
private:
	//-----Con/Destructors
	GameManager();
	~GameManager();

	//-----Self Reference (This is a singleton)
	static GameManager* Instance;

	//Current Scene
	int CurrSc;

	//-----Systems
	Camera		Cam;
	Renderer	Ren;
	AudioSystem AS;

	//-----Objects for Main Menu
	Object MenuOb;
	//Buttons
	Button Play;
	Button PlayAI;
	Button Exit;
	Button Return;
	

	//-----Objects;
	vector<Object>	ObVec;
	vector<Enemy>	EnVec;
	Player			player;

	//CubeMap
	CubeMap CMap;

	//-----Text
	TextLabel ScoreText;
	TextLabel LivesText;
	TextLabel VelocityText;
	TextLabel LossText;

	//-----Scoring
	int Lives;
	int Score;

	//-----Time
	float previousTimeStamp;
	float deltaTime;
	float timeElapsed;

public:
	static void Init();
	static void Render(void);
	static void Update();

	//-----Rendering
	void RenMenu();
	void RenPlay();
	void RenAI();
	void RenLoss();

	//-----Updating
	void UpdMenu();
	void UpdPlay();
	void UpdAI();
	void UpdLoss();

	//-----Instantiting
	void InstPlay();

	//-----Setters
	void SetScore(int newScore);
	void SetLives(int newLives);
	void SetVel();

	//-----Getters
	int GetScore() { return Score; }
	int GetLives() { return Lives; }
	CubeMap* GetSkyBox() { return &CMap; }
	Camera* GetCam() { return &Cam; }
	AudioSystem* GetAS() { return &AS; }
	static GameManager* GetInstance();
};