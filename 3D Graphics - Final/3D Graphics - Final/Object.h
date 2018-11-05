#pragma once
#include "Mesh.h"
//-----glm for OpenGL Maths
#include "Dependencies\glm\glm.hpp"
#include "Dependencies\glm\gtc\matrix_transform.hpp"
#include "Dependencies\glm\gtc\type_ptr.hpp"
#include "Dependencies\glew\glew.h"

#include <string>

enum MeshType { CUBE, SPHERE, PYRAMID };

class Object
{
protected:
	//Active
	bool Active;

	//-----Mesh
	Mesh * mesh;

	//-----Transform Variables

	glm::vec3 Position;
	glm::vec3 Center;
	glm::vec3 Scale;
	glm::mat4 Model;
	
	

	//------Movement
	float MaxSpd;
	float AccSpd;
	float RotSpd;
	float Friction;
	glm::vec3 Velocity;
	glm::vec3 Acceleration;

	//-----Thrust Directions
	//Base
	glm::vec3 BaseFoward;
	glm::vec3 BaseLeft;
	glm::vec3 BaseRight;

	//Applied
	glm::vec3 AppFoward;
	glm::vec3 AppLeft;
	glm::vec3 AppRight;

	//-----Rotation
	float Rotx;
	float Roty;
	float Rotz;

	glm::quat QuatRotx;
	glm::quat QuatRoty;
	glm::quat QuatRotz;
	glm::quat QuatRot;

	glm::mat4 RotMatrix;

	//Up
	glm::vec3 AppUpDir;
	glm::vec3 BaseUpDir;
public:

	//-----Con/Destructor
	Object();
	~Object();

	//-----Init
	void Init(	int MeshType, const std::string& TextureFP, const std::string & ShaderFP, glm::vec3 initPos, glm::vec3 initScale);

	//-----Update
	void Update(float deltaTime);

	//-----Render
	void Render();

	//-----Setters
	void SetActive(bool newActive) { Active = newActive; }

	void SetPosition(glm::vec3 newPos) { Position = newPos; }
	void SetScale(glm::vec3 newScale) { Scale = newScale; }

	//Thrust Setters
	void SetBaseFoward(glm::vec3 newBaseFow) { BaseFoward = newBaseFow; }
	void SetBaseRight(glm::vec3 newBaseRig) { BaseRight = newBaseRig; }
	void SetBaseLeft(glm::vec3 newBaseLef) { BaseLeft = newBaseLef; }

	//Rotation Setters
	void SetBaseUp(glm::vec3 newBaseUp) { BaseUpDir = newBaseUp; }

	//Movement Setters
	void SetMaxSpd(float newMax) { MaxSpd = newMax; }
	void SetAccSpd(float newAcc) { AccSpd = newAcc; }
	void SetFriction(float newFric) { Friction = newFric; }
	void SetRotSpd(float newRotSpd) { RotSpd = newRotSpd; }

	//-----Getters
	bool GetActive() { return Active; }

	glm::vec3 GetPosition() { return Position; }
	glm::vec3 GetCenter() { return Center; }
	glm::vec3 GetScale() { return Scale; }
	glm::vec3 GetVelocity() { return Velocity; }

	//Movement Getters
	float GetMaxSpd() { return MaxSpd; }
	float GetAccSpd() { return AccSpd; }
	float GetFriction() { return Friction; }

	//Rotation Getters
	glm::quat GetRotQuat() { return QuatRot; }
	glm::vec3 GetUpDir() { return AppUpDir; }

	//Thrust Getters
	glm::vec3 GetBaseFoward()		{ return BaseFoward; }
	glm::vec3 GetBaseRight()		{ return BaseRight; }
	glm::vec3 GetBaseLeft()			{ return BaseLeft; }

	glm::vec3 GetAppFoward()	{ return AppFoward; }
	glm::vec3 GetAppRight()		{ return AppRight; }
	glm::vec3 GetAppLeft()		{ return AppLeft; }

	//Movement Func
	void RotateOnAxis(glm::vec3 Axis);

	//Functional
	float map(float Value, float in_min, float in_max, float out_min, float out_max);

};