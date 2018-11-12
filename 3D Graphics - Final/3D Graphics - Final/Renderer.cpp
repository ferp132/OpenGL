#include "Renderer.h"
#include "VertexArray.h"
#include "IndexBuffer.h"
#include "Shader.h"

#include <iostream>

using namespace std;

void GLClearError()
{
	while (glGetError() != GL_NO_ERROR);
}

bool GLLogCall(const char* function, const char* file, int line)
{
	while (GLenum error = glGetError())
	{
		cout << "[OpenGL Error] (" << error << "): " << function << " " << file << ":" << line << endl;
		return false;
	}
	return true;
}

void Renderer::Clear()
{
	GLCall(glClear(GL_DEPTH_BUFFER_BIT | GL_COLOR_BUFFER_BIT));
	GLCall(glClearColor(1.0, 0.0, 0.0, 1.0));
}

void Renderer::rDraw(const VertexArray& va, const IndexBuffer& ib, const Shader& shader) const
{
	shader.Bind();
	va.Bind();
	ib.Bind();
	GLCall(glDrawElements(GL_TRIANGLES, ib.GetCount(), GL_UNSIGNED_INT, nullptr));
}

//
//void Renderer::RenMenu()
//{
//	//-----Render Object
//	MenuOb.Render();
//
//	//-----Render Buttons
//	Play.Render();
//	PlayAI.Render();
//	Exit.Render();
//
//	//Networking Buttons
//	Client.Render();
//	Server.Render();
//}
//
//void Renderer::RenPlay()
//{
//	//-----Render Objects
//	for (unsigned int i = 0; i < ObVec.size(); i++)
//	{
//		ObVec.at(i).Render();
//	}
//	//Enemies
//	for (unsigned int i = 0; i < EnVec.size(); i++)
//	{
//		EnVec.at(i).Render();
//	}
//	//Player
//	player.Render();
//
//	//-----Render Text
//	ScoreText.Render();
//	LivesText.Render();
//	VelocityText.Render();
//
//
//}
//
//void Renderer::RenAI()
//{
//	//-----Render Objects
//	for (unsigned int i = 0; i < ObVec.size(); i++)
//	{
//		ObVec.at(i).Render();
//	}
//	//Enemies
//	for (unsigned int i = 0; i < EnVec.size(); i++)
//	{
//		EnVec.at(i).Render();
//	}
//	//Player
//	player.Render();
//
//	//-----Menu Buttons Render
//	Seek.Render();
//	Arrive.Render();
//	Wander.Render();
//	Follow.Render();
//	Queue.Render();
//
//	Contain.Render();
//	Seperate.Render();
//	Avoid.Render();
//
//	Done.Render();
//}
//
//void Renderer::RenLoss()
//{
//	//-----Render Objects
//	for (unsigned int i = 0; i < ObVec.size(); i++)
//	{
//		ObVec.at(i).Render();
//	}
//	//Enemies
//	for (unsigned int i = 0; i < EnVec.size(); i++)
//	{
//		EnVec.at(i).Render();
//	}
//	//Player
//	player.Render();
//	LossText.Render();
//	Return.Render();
//}
