#pragma once
#include "Mesh.h"
//-----glm for OpenGL Maths
#include "Dependencies\glm\glm.hpp"
#include "Dependencies\glm\gtc\matrix_transform.hpp"
#include "Dependencies\glm\gtc\type_ptr.hpp"
#include "Dependencies\glew\glew.h"

#include <string>

enum MeshType2D { QUAD };

class Object2D
{
protected:
	//-----Mesh
	Mesh * mesh;

	//-----Transform Variables

	glm::vec2 Position;
	glm::vec2 Scale;
	float Rotation;

	glm::mat4 Model;
public:

	//-----Con/Destructor
	Object2D();
	~Object2D();

	//-----Init
	void Init(int MeshType, glm::vec3 Colour, const std::string & ShaderFP, glm::vec2 initPos, glm::vec2 initScale, float init Rotation);

	//-----Update
	void Update(float deltaTime);

	//-----Render
	void Render();

	//-----Setters
	void SetPosition(glm::vec2 newPos) { Position = newPos; }
	void SetScale(glm::vec2 newScale) { Scale = newScale; }
	void SetRot(float newRot) { Rotation = newRot; }

	//-----Getters
	glm::vec2 GetPosition() { return Position; }
	glm::vec2 GetScale() { return Scale; }
	float GetRot() { return Rotation; }

};