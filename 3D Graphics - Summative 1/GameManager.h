#pragma once
#include "InputManager.h"
#include "Camera.h"
#include "Renderer.h"
#include "AudioSystem.h"

#include <map>
#include <vector>

#include "Object.h"
#include "ControlledObject.h"
#include "TextLabel.h"
#include "Texture.h"
#include "Shader.h"

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
	Shader Shad;
	Texture Tex;

	Object Background;
	ControlledObject Player;

	FMOD::Sound* fxThump;
	FMOD::Sound* trackBackground;

public:

	Camera* GetCam() { return &Cam; }

	static GameManager* GetInstance();

	static void Init();

	static void Render(void);

	static void Update();


};