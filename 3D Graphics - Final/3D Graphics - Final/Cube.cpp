#include "Cube.h"
#include "GameManager.h"
Cube::Cube()
{
}

Cube::~Cube()
{
}

void Cube::Init(float InitxPos, float InityPos, float InitzPos, float InitHeight, float InitLength, float InitWidth, const std::string& InitTexFP)
{
}

void Cube::Render()
{

	//glEnable(GL_BLEND);
	//glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);

	//MVP calc
	UpdateModel();
	glm::mat4 MVP = GameManager::GetInstance()->GetCam()->GetPxV() * Model;
	glm::vec3 CameraPosition = GameManager::GetInstance()->GetCam()->getPosition();
	//Bind Shader
	Shad.Bind();
	Shad.setUniformMat4f("u_MVP", MVP);
	Shad.setUniformMat4f("model", Model);
	Shad.setUniform3f("camPos", CameraPosition.x, CameraPosition.y, CameraPosition.z);

	VAO.Bind();
	VBO.Bind();
	IBO.Bind();
	Shad.Bind();
	Tex.Bind(GL_TEXTURE_2D);

	GLCall(glDrawElements(GL_TRIANGLES, IBO.GetCount(), GL_UNSIGNED_INT, nullptr));

	VAO.Unbind();
	VBO.UnBind();
	IBO.UnBind();

}

void Cube::UpdateModel()
{
	glm::mat4 Scale = glm::scale(glm::mat4(), glm::vec3(Width, Height, Length));
	glm::mat4 Trans = glm::translate(glm::mat4(1.0f), glm::vec3(xPos + Width * 0.5, yPos + Height * 0.5, zPos + Length * 0.5));

	Model = Trans * Scale;

}

void Cube::ProcessInput(float deltaTime)
{

	if (InputManager::Getinstance()->MouseState[MOUSE_LEFT] == DOWN)
	{

	}

	if (InputManager::Getinstance()->KeyState['w'] == DOWN)
	{
		xPos += 2.0f;
	}
	if (InputManager::Getinstance()->KeyState['s'] == DOWN)
	{
		xPos -= 2.0f;
	}
	if (InputManager::Getinstance()->KeyState['d'] == DOWN)
	{
		zPos += 2.0f;
	}
	if (InputManager::Getinstance()->KeyState['a'] == DOWN)
	{
		zPos -= 2.0f;
	}
	if (InputManager::Getinstance()->KeyState['x'] == DOWN)
	{
		yPos += 2.0f;
	}
	if (InputManager::Getinstance()->KeyState['z'] == DOWN)
	{
		yPos -= 2.0f;
	}

	UpdateModel();
}
