#include "pch.h"
#include "Core.h"

Core::Core()
{
	//init ���� ó����
}

Core::~Core()
{
}

void Core::Init(int argc, char** argv) //
{
	::glutInit(&argc, argv); // glut �ʱ�ȭ   GLUT�� openGL ȯ�� �ʱ�ȭ
	::glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGBA | GLUT_DEPTH | GLUT_BORDERLESS); // �÷���, ������ ���� �� �ʱ��� ��� ��带 �����Ѵ�.
	::glutInitWindowPosition(0, 0); // ������ ���� ���� (x,y)

	int screenWidth = glutGet(GLUT_SCREEN_WIDTH); // ������� ���� �ػ� ��������
	int screenHeight = glutGet(GLUT_SCREEN_HEIGHT); // ������� ���� �ػ� ��������

	::glutInitWindowSize(1920, 1080);  // ������ ũ�� ���� 
	::glutCreateWindow("THE NUN");

	//--- GLEW �ʱ�ȭ�ϱ�
	::glewExperimental = GL_TRUE;
	if (glewInit() != GLEW_OK) // glew �ʱ�ȭ
	{
		std::cerr << "glew �ʱ�ȭ ����" << std::endl;
		exit(EXIT_FAILURE);
	}
}

void Core::Render(void (*funcptr)(void))
{
	::glutDisplayFunc(funcptr);


}

void Core::Reshape(void(*funcptr)(int, int))
{
	::glutReshapeFunc(funcptr);
}

void Core::Keyboard(void (*funcptr)(unsigned char, int, int))
{
	glutKeyboardFunc(funcptr);
}

void Core::mousein(void(*funcptr)(int button, int state, int x, int y))
{
	glutMouseFunc(funcptr);
}

void Core::mouse_move(void(*funcptr)(int x, int y))
{
	glutMotionFunc(funcptr);
}

vec2 Core::convert(int x, int y, int WINDOW_WIDTH, int WINDOW_HEIGHT)
{
	int w = WINDOW_WIDTH;
	int h = WINDOW_HEIGHT;

	float ox = (float)(x - (float)w / 2.0) * (float)(1.0 / (float)(w / 2.0));
	float oy = -((float)(y - (float)h / 2.0) * (float)(1.0 / (float)(h / 2.0)));

	vec2 pos = { ox,oy };

	return pos;
}



