#pragma once
#include "InputManager.h"
#include "Camera.h"
#include "Renderer.h"
#include "AudioSystem.h"

#include <map>
#include <vector>

#include "Object.h"
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



	//Temp
	TextLabel label;
	Shader Shad;
	Texture Tex;

	Object ob;
	Object ob2;
	Object ob3;

	FMOD::Sound* fxThump;
	FMOD::Sound* trackBackground;

public:

	static GameManager* GetInstance();

	static void Init();

	static void Render(void);

	static void Update();


};