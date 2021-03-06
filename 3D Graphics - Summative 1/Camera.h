#pragma once
#ifndef __CAMERA_H__
#define __CAMERA_H__

//glm for OpenGL Maths
#include "Dependencies\glm\glm.hpp"
#include "Dependencies\glm\gtc\matrix_transform.hpp"
#include "Dependencies\glm\gtc\type_ptr.hpp"

class Camera
{
public:
	Camera();
	~Camera();

	void Init(float InitWinWidth, float InitWinHeight);

	glm::mat4 GetViewMatrix();
	glm::mat4 GetProjMatrix();
	glm::mat4 GetPxV();
private:
	glm::vec3 CamPos	 = glm::vec3(0.0f,  0.0f,  3.0f);
	glm::vec3 CamLookDir = glm::vec3(0.0f,  0.0f, -1.0f);
	glm::vec3 CamUpDir	 = glm::vec3(0.0f,  1.0f,  0.0f);

	float WinWidth;
	float WinHeight;
};

#endif // ! __CAMERA_H__
