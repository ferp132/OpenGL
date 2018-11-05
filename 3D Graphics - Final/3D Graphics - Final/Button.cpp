#include "Button.h"
#include "InputManager.h"
#include "GameManager.h"

Button::Button()
{
	
}

Button::~Button()
{
}

void Button::Init(glm::vec2 initPosition, glm::vec2 initScale, std::string initText, std::string initFont, glm::vec3 initTextColour)
{
	textlab.Init(initText, initFont, initPosition, initTextColour, initScale.x);
	Position = initPosition;
	Scale = initScale;
	Clicked = false;
	Active = false;
}

void Button::Update()
{
	ProcessInput();
}

void Button::ProcessInput()
{
	int Mousex = InputManager::Getinstance()->GetMouseX();
	int Mousey = InputManager::Getinstance()->GetMouseY();
	glm::vec2 TextSize = textlab.GetTextSize();

	if (InputManager::Getinstance()->MouseState[MOUSE_LEFT] == DOWN)
	{
		if (Mousex > Position.x && Mousex < Position.x + TextSize.x
			&& Mousey < 800 - Position.y && Mousey > 800 - Position.y - TextSize.y)
		{
			Clicked = true;
		}
	}
}

void Button::Render()
{
	textlab.Render();
}

void Button::SetActive(bool newActive)
{
	Active = newActive;
	textlab.SetActive(newActive);
	Clicked = false;
}
