#pragma once
#include "Object.h"

class Enemy : public Object
{
private:


public:
	void MoveTo(glm::vec3 toPosition);

};