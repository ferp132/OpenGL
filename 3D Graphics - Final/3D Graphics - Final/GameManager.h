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
#include "Path.h"

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

	//Buttons for AI
	Button Seek;
	Button Arrive;
	Button Wander;
	Button Follow;
	Button Queue;

	Button Contain;
	Button Seperate;
	Button Avoid;

	Button Done;

	

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

	//-----AI
	int EnMoveType;
	Path path;

	bool Con;
	bool Sep;
	bool avoid;

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

	//-----Instantiating
	void InstPlay();
	void InstAI();

	//-----Setters
	void SetScore(int newScore);
	void SetLives(int newLives);
	void SetVel();

	//-----Getters
	int GetScore() { return Score; }
	int GetLives() { return Lives; }
	std::vector<Enemy>* GetEnVec() { return &EnVec; }
	std::vector<Object>* GetObVec() { return &ObVec; }

	CubeMap* GetSkyBox() { return &CMap; }
	Camera* GetCam() { return &Cam; }
	AudioSystem* GetAS() { return &AS; }


	static GameManager* GetInstance();

	//AI


	bool GetAvoid() { return avoid; }
	bool GetSep() { return Sep; }
	bool GetCon() { return Con; }

	void SetContain(bool newBool) { Con = newBool; }
	void SetSep(bool newBool) { Sep = newBool; }
	void Setavoid(bool newBool) { avoid = newBool; }
};