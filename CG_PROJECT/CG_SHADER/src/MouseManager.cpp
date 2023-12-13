#include "pch.h"
#include "MouseManager.h"
#include <chrono>



void MouseManager::Init()
{
	

	glutPassiveMotionFunc(MousemoveCallBack2);
	
}

void MouseManager::MouseCallBack(int button, int state, int x, int y)
{


	if (button == GLUT_LEFT_BUTTON && state == GLUT_DOWN)
	{


	}

	if (button == GLUT_LEFT_BUTTON && state == GLUT_DOWN)
	{


	}

	if (button == GLUT_RIGHT_BUTTON && state == GLUT_DOWN)
	{
	
	

	}

	if (button == GLUT_RIGHT_BUTTON && state == GLUT_UP)
	{
	

	}
}

void MouseManager::MousemoveCallBack(int x, int y)
{



}

void MouseManager::MousemoveCallBack2(int x, int y)
{


	MouseManager::GetInstance()->m_pos.x = x;
	MouseManager::GetInstance()->m_pos.y = y;

	

	

	
	

}




