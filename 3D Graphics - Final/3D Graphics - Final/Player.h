#pragma once
#include "Object.h"

class Player : public Object
{
private:
	
	bool PlayingFX = 0;

public:

	Player();
	~Player();

	void ProcessInput(float deltaTime);
};