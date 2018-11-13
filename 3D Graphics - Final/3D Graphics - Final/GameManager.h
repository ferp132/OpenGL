#pragma once
/*
//-----glm for OpenGL Maths
#include "Dependencies\glm\glm.hpp"
#include "Dependencies\glm\gtc\matrix_transform.hpp"
#include "Dependencies\glm\gtc\type_ptr.hpp"


#include "Dependencies\glew\glew.h"
#include "Dependencies\freeglut\freeglut.h"
*/

//-----Networking
#include <Windows.h>
#include <cassert>
#include <thread>

#include "network.h"
#include "client.h"
#include "server.h"
#include "InputLineBuffer.h"

#include <functional>

//

#include "AudioSystem.h"
#include "TextLabel.h"

#include "Camera.h"
#include "CubeMap.h"
#include "Object.h"
#include "Player.h"
#include "Enemy.h"
#include "Button.h"
#include "Path.h"

// make sure the winsock lib is included...
#pragma comment(lib,"ws2_32.lib")

enum Scene {MENU, PLAY, PLAYAI, MULTI, LOSS };

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


	
	map<std::string, Button*> ButMap;

	//-----Objects;
	Object MenuOb;
	vector<Object>	ObVec;
	vector<Enemy>	EnVec;
	map<std::string, Player*> PlayerMap;

	//CubeMap
	CubeMap CMap;

	//-----Text
	TextLabel ScoreText;
	TextLabel LivesText;
	TextLabel VelocityText;
	TextLabel LossText;

	map<string, TextLabel*> NetText;		//Test for Multiplayer

	//-----Scoring
	int Lives;
	int Score;

	//-----Time
	float previousTimeStamp;
	float deltaTime;
	float timeElapsed;

	//-----Font
	const char* ftArial;

	//-----AI
	int EnMoveType;
	Path path;

	bool Con;
	bool Sep;
	bool avoid;

	//-----Networking

	char* _pcPacketData; //A local buffer to receive packet data info


	unsigned char _ucChoice;
	EEntityType _eNetworkEntityType;
	CInputLineBuffer* _InputBuffer;
	std::thread _ClientReceiveThread, _ServerReceiveThread;

	char _cIPAddress[MAX_ADDRESS_LENGTH]; // An array to hold the IP Address as a string
										  //ZeroMemory(&_cIPAddress, strlen(_cIPAddress));

	//A pointer to hold a client instance
	CClient* _pClient;
	//A pointer to hold a server instance
	CServer* _pServer;

	CNetwork& _rNetwork = CNetwork::GetInstance();

public:
	static void Init();
	static void Render(void);
	static void Update();

	//-----Rendering
	void RenMenu();
	void RenPlay();
	void RenAI();
	void RenMulti();
	void RenLoss();

	//-----Updating
	void UpdMenu();
	void UpdPlay();
	void UpdAI();
	void UpMulti();
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
	map<string, TextLabel*>* GetNetText() { return &NetText; }
	map< string, Button* > * GetButMap() { return &ButMap; }

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

	//-----Init Networking
	void InitNetwork();
	void UpdateNetWork();

	void InitButtons();
	void InitPlayer();
};