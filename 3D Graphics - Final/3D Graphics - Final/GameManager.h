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



class GameManager
{
private:
	GameManager();
	~GameManager();

	static GameManager* Instance;

	Camera Cam;
	Renderer Ren;
	AudioSystem AS;

	//Temp
	Texture Tex;
	Button but1;
	Button but2;

	//CubeMap
	CubeMap CMap;

	//Objects;
	vector<Object> ObVector;
	vector<Enemy> EnemyVector;
	Player player;
	Enemy enemy;

	//-----Text
	TextLabel ScoreText;
	TextLabel LivesText;

	//-----Scoring
	int Lives;
	int Score;




	//time
	float previousTimeStamp;
	float deltaTime;
	float timeElapsed;

public:
	//-----Setters
	void SetScore(int newScore);
	void SetLives(int newLives);

	//-----Getters
	int GetScore() { return Score; }
	int GetLives() { return Lives; }
	Camera* GetCam() { return &Cam; }
	AudioSystem* GetAS() { return &AS; }
	static GameManager* GetInstance();

	static void Init();

	static void Render(void);

	static void Update();

};