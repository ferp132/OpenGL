#pragma once
#include "TextLabel.h"
#include "Dependencies\glew\glew.h"
#include "Dependencies\glm\glm.hpp"
#include "Dependencies\glm\gtc\matrix_transform.hpp"
#include "Dependencies\glm\gtc\type_ptr.hpp"

class Button
{
private:
	TextLabel textlab;

	glm::vec2 Position;
	glm::vec2 Scale;

	bool Clicked;
	bool Active;

public:
	Button();
	~Button();

	void Init(glm::vec2 initPosition, glm::vec2 initScale, std::string initText, std::string initFont, glm::vec3 initTextColour);
	void Update();
	void ProcessInput();
	void Render();

	//-----Getters
	bool GetClicked() { return Clicked; }
	bool GetActive() { return Active; }

	//-----Setters
	void SetActive(bool newActive);
	void SetClicked(bool newClicked) { Clicked = newClicked; }
	void SetColor(glm::vec3 newColor) { textlab.SetColor(newColor); }
};