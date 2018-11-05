#pragma once
#ifndef __CAMERA_H__
#define __CAMERA_H__
#include "Object.h"


class Camera
{
public:
	Camera();
	~Camera();

	void Init(float InitWinWidth, float InitWinHeight, Object* Player);
	void Update(float deltaTime);
	void ProcessInput();

	glm::vec3 getPosition() { return CamPos; };
	glm::mat4 GetViewMatrix();
	glm::mat4 GetProjMatrix();
	glm::mat4 GetPxV();
	bool getPosType() { return PosType; }
	void setPosType(bool newPosType) { PosType = newPosType; }
	void SetFollowing(Object* newFollowing) { Following = newFollowing; }
	void SetRotFollow(bool newFollowing) { RotbyFollowing = true; }
private:
	glm::vec3 CamPos	 = glm::vec3(0.0f,  0.0f,  3.0f);
	glm::vec3 CamLookDir = glm::vec3(0.0f,  0.0f, -1.0f);
	glm::vec3 CamUpDir	 = glm::vec3(0.0f,  1.0f,  0.0f);

	Object* Following;

	float Rotation = 0;

	float WinWidth;
	float WinHeight;

	bool PosType;
	bool RotbyFollowing;
};

#endif // ! __CAMERA_H__
