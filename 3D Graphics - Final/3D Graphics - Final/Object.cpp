#include "Object.h"
#include "Mesh_Cube.h"
#include "Mesh_Pyramid.h"
#include "Mesh_Sphere.h"
#include "GameManager.h"

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
}

void Object::Update(float deltaTime)
{
	glm::mat4 ScaleMat = glm::scale(glm::mat4(), Scale);
	glm::mat4 Trans = glm::translate(glm::mat4(1.0f), Position + Scale * glm::vec3(0.5, 0.5, 0.5));

	Model = Trans * ScaleMat;
}

void Object::Render()
{
	glm::mat4 MVP = GameManager::GetInstance()->GetCam()->GetPxV() * Model;
	glm::vec3 CamPos = GameManager::GetInstance()->GetCam()->getPosition();

	mesh->Render(MVP, Model, CamPos);
}
