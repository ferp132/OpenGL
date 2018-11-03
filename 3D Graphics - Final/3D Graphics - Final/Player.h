#pragma once
#include "Object.h"

class Player : public Object
{
private:
	
	bool PlayingFX = 0;
	glm::vec3 Dir;

public:
	void ProcessInput();
	

};