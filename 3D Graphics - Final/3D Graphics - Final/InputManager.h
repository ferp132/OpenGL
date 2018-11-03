#pragma once



enum InputState
{
	UP,
	DOWN,
	UP_FIRST,
	DOWN_FIRST,
};
enum InputMouse
{
	MOUSE_LEFT,
	MOUSE_MIDDLE,
	MOUSE_RIGHT,
};



class InputManager
{
public:
	static InputManager* Getinstance();

	static void Init();

	static void KeyboardDown(unsigned char key, int x, int y);
	static void KeyboardUp(unsigned char key, int x, int y);
	static void MouseClick(int button, int state, int x, int y);
	static void MousePassiveMove(int x, int y);
	static void MouseMove(int x, int y);
	static void ProcessInput();

	InputState KeyState[255];
	InputState MouseState[3];
private:
	InputManager();
	~InputManager();

	static InputManager* Instance;


};