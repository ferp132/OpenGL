#include "Object.h"
#include "Mesh_Cube.h"
#include "Mesh_Pyramid.h"
#include "Mesh_Sphere.h"
#include "GameManager.h"
#include <glm/gtc/quaternion.hpp>
#include <glm/gtx/quaternion.hpp>


Object::Object()
{
}

Object::~Object()
{
}

void Object::Init(int MeshType, const std::string & TextureFP, const std::string & ShaderFP, glm::vec3 initPos, glm::vec3 initScale)
{
	switch (MeshType)
	{
	case CUBE:
	{
		mesh = new CubeMesh(TextureFP, ShaderFP);
		break;
	}
	case SPHERE:
	{
		mesh = new SphereMesh(TextureFP, ShaderFP);
		break;
	}
	case PYRAMID:
	{
		mesh = new PyramidMesh(TextureFP, ShaderFP);
		break;
	}
	}

	Position = initPos;
	Scale = initScale;
	Velocity = glm::vec3(0.0f, 0.0f, 0.0f);

	//-----Rotation
	Rotx = 0.0f;
	Roty = 0.0f;
	Rotz = 0.0f;
}

void Object::Update(float deltaTime)
{
	glm::mat4 ScaleMat = glm::scale(glm::mat4(), Scale);
	glm::mat4 Trans = glm::translate(glm::mat4(1.0f), Position + Scale * glm::vec3(0.5, 0.5, 0.5));
	//-----Rotation
	//x rotation
	glm::vec3 Axisx(1.0f, 0.0f, 0.0f);
	float x, y, z, w;

	x = Axisx.x * sin(Rotx / 2);
	y = Axisx.y * sin(Rotx / 2);
	z = Axisx.z * sin(Rotx / 2);
	w = cos(Rotx / 2);

	QuatRotx = glm::quat(w, x, y, z);

	//y rotation
	glm::vec3 Axisy(0.0f, 1.0f, 0.0f);
	x = Axisy.x * sin(Roty / 2);
	y = Axisy.y * sin(Roty / 2);
	z = Axisy.z * sin(Roty / 2);
	w = cos(Roty / 2);

	QuatRoty = glm::quat(w, x, y, z);

	//z rotation
	glm::vec3 Axisz(0.0f, 0.0f, 1.0f);
	x = Axisz.x * sin(Rotz / 2);
	y = Axisz.y * sin(Rotz / 2);
	z = Axisz.z * sin(Rotz / 2);
	w = cos(Rotz / 2);

	QuatRotz = glm::quat(w, x, y, z);
	
	//Add Rotation quats together
	Rot = glm::toMat4(QuatRotx * QuatRoty * QuatRotz);

	Model = Trans * Rot * ScaleMat;
}

void Object::Render()
{
	glm::mat4 MVP = GameManager::GetInstance()->GetCam()->GetPxV() * Model;
	glm::vec3 CamPos = GameManager::GetInstance()->GetCam()->getPosition();

	mesh->Render(MVP, Model, CamPos);
}
