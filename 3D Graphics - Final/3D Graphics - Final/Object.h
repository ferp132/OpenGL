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
	//-----Mesh
	Mesh * mesh;

	//-----Transform Variables

	glm::vec3 Position;
	glm::vec3 Scale;
	
	glm::mat4 Model;
	glm::mat4 Rot;

	//------Movement
	float MaxSpd = 0.02f;
	float AccSpd = 0.0005f;
	float Friction = 0.001f;

	//-----Rotation
	float Rotx;
	float Roty;
	float Rotz;



public:
	glm::vec3 Velocity;
	glm::vec3 upDir;

	glm::vec3 Foward;

	glm::quat QuatRotx;
	glm::quat QuatRoty;
	glm::quat QuatRotz;
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
	void SetPosition(glm::vec3 newPos) { Position = newPos; }
	void SetScale(glm::vec3 newScale) { Scale = newScale; }
	void SetMaxSpd(float newMaxSpd) { MaxSpd = newMaxSpd; };

	//-----Getters
	glm::vec3 GetPosition() { return Position; }
	glm::vec3 GetScale() { return Scale; }
	float GetMaxSpd() { return MaxSpd; };
};