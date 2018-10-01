#include "Dependencies\glew\glew.h"
#include "Dependencies\freeglut\freeglut.h"

#include "InputManager.h"
#include "GameManager.h"


//glm::mat4 Projection = glm::ortho(0.0f, 800.0f, 0.0f, 800.0f, -1.0f, 1.0f);
//glm::mat4 View = glm::translate(glm::mat4(1.0f), glm::vec3(0, 0, -1));

//glm::vec3 MoveVec = glm::vec3(0, 0, 0);
//glm::mat4 Model = glm::translate(glm::mat4(1.0f), MoveVec);

//glm::vec3 ScaleVec = glm::vec3(1.0, 1.0, 1.0);
//glm::mat4 ScaleMatrix = glm::scale(glm::mat4(), ScaleVec);



int main(int argc, char **argv) {

	glutInit(&argc, argv);
	glutInitDisplayMode(GLUT_DEPTH | GLUT_DOUBLE | GLUT_RGBA);
	glutInitWindowPosition(200, 50);
	glutInitWindowSize(800, 800);
	glutCreateWindow("Graphics Assignment 2");
	glClearColor(1.0, 0.0, 0.0, 1.0); //clear red
	glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);

	glewInit();
	GameManager::Init();
	//register callbacks
	glutDisplayFunc(GameManager::Render);
	glutIdleFunc(GameManager::Update);
	glutKeyboardFunc(InputManager::KeyboardDown);
	glutKeyboardUpFunc(InputManager::KeyboardUp);
	glutMouseFunc(InputManager::MouseClick);
	glutMotionFunc(InputManager::MouseMove);
	glutPassiveMotionFunc(InputManager::MousePassiveMove);
	glutMainLoop();						//Ensure this is the last glut line called
	return 0;
}


//void Update()
//{
	//Update game information.
	//GLfloat currentTime = (GLfloat)glutGet(GLUT_ELAPSED_TIME);	//Get Current time
	//	currentTime = currentTime / 1000;					// Convert millisecond to seconds
//}






