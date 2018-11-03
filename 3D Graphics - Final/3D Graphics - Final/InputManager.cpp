#include "InputManager.h"
#include "Dependencies\freeglut\freeglut.h"
#include <iostream>
using namespace std;

InputManager* InputManager::Instance = NULL;

InputManager::InputManager()
{
}

InputManager::~InputManager()
{
}

InputManager* InputManager::Getinstance()
{
	if (Instance == NULL)
	{
		Instance = new InputManager();
	}

	return Instance;
		
}

void InputManager::Init()
{

}

void InputManager::KeyboardDown(unsigned char key, int x, int y)
{
	
	Getinstance()->KeyState[key] = DOWN;
}

void InputManager::KeyboardUp(unsigned char key, int x, int y)
{
	Getinstance()->KeyState[key] = UP;
}

void InputManager::MouseClick(int button, int state, int x, int y)
{
	if (button >= 3)
		return;

	Getinstance()->MouseState[button] = (state == GLUT_DOWN) ? DOWN : UP;
}

void InputManager::MousePassiveMove(int x, int y)
{
	cout << "Passive x: " << x << " | y: " << y << endl;
}

void InputManager::MouseMove(int x, int y)
{
	cout << "Clicked x: " << x << " | y: " << y << endl;
}

void InputManager::ProcessInput()
{

}
