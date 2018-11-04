#include "2DObject.h"
#include "Mesh_Quad.h"

Object2D::Object2D()
{
}

Object2D::~Object2D()
{
}

void Object2D::Init(int MeshType, glm::vec3 Colour, const std::string & ShaderFP, glm::vec2 initPos, glm::vec2 initScale, float init Rotation)
{
	switch (MeshType)
	{
	case QUAD:
	{
		mesh = new QuadMesh(Colour, ShaderFP);
		break;
	}

	}
}

void Object2D::Update(float deltaTime)
{
}

void Object2D::Render()
{
}
