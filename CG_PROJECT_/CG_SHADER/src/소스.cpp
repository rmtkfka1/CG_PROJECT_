#include "pch.h"
#include "SceneManager.h"
#include "TextManager.h"
#include "SoundManager.h"



void draw()
{
		glClearColor(0, 0, 0, 1.0f);
		glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

	
		
		SceneManager::GetInstance()->Render();
		glutSwapBuffers();

};

int main(int argc, char** argv)
{
	_CrtSetDbgFlag(_CRTDBG_ALLOC_MEM_DF | _CRTDBG_LEAK_CHECK_DF); //memory leak check

	Core::GetInstance()->Init(argc, argv);
	Core::GetInstance()->Render(draw);

	KeyManager::GetInstance()->Init();
	TimeManager::GetInstance()->Init();
	MouseManager::GetInstance()->Init();
	TextManager::GetInstance()->Init();
	SoundManager::GetInstance()->Init();



	glEnable(GL_DEPTH_TEST);
	glEnable(GL_CULL_FACE);
	glutSetCursor(GLUT_CURSOR_NONE); // 마우스 커서 숨기기


	SceneManager::GetInstance()->ChangeScene(SceneType::Stage1);

	while (1)
	{
	
		KeyManager::GetInstance()->Update();
		TimeManager::GetInstance()->Update();
		SceneManager::GetInstance()->Update();

		glutPostRedisplay();
		glutMainLoopEvent();
	}

}
