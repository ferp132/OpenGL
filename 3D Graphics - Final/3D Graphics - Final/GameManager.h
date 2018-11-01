#pragma once
#include "InputManager.h"
#include "Camera.h"
#include "Renderer.h"
#include "AudioSystem.h"
#include "Object.h"
#include "ControlledObject.h"
#include "TextLabel.h"
#include "Texture.h"
#include "Shader.h"
#include "Pyramid.h"
#include "Cube.h"
#include "CubeMap.h"

#include <map>
#include <vector>



class GameManager
{
private:
	GameManager();
	~GameManager();

	static GameManager* Instance;

	Camera Cam;
	Renderer Ren;
	AudioSystem AS;

	std::vector<Object*> ObjectVector;

	const std::string BackgroundTex = "Resources/Textures/SpaceBackground.png";
	const std::string AwesomeDTex =   "Resources/Textures/AwesomeFace.png";

	//Temp
	TextLabel label;
	//Shader ShadB;
	//Shader ShadL;
	Texture Tex;

	//CubeMap
	CubeMap CMap;

	//Object Background;
	Pyramid Pyr;
	Cube Cube;



	//Sounds
	FMOD::Sound* fxThump;
	FMOD::Sound* trackBackground;

	//time
	float previousTimeStamp;
	float deltaTime;
	float timeElapsed;

public:

	Camera* GetCam() { return &Cam; }

	static GameManager* GetInstance();

	static void Init();

	static void Render(void);

	static void Update();

};