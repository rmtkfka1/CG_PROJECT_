#include "pch.h"
#include "Core.h"

Core::Core()
{
	//init 에서 처리함
}

Core::~Core()
{
}

void Core::Init(int argc, char** argv) //
{
	::glutInit(&argc, argv); // glut 초기화   GLUT와 openGL 환경 초기화
	::glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGBA | GLUT_DEPTH | GLUT_BORDERLESS); // 컬러모델, 윈도우 버퍼 등 초기의 출력 모드를 결정한다.
	::glutInitWindowPosition(0, 0); // 윈도우 시작 지점 (x,y)

	int screenWidth = glutGet(GLUT_SCREEN_WIDTH); // 모니터의 가로 해상도 가져오기
	int screenHeight = glutGet(GLUT_SCREEN_HEIGHT); // 모니터의 세로 해상도 가져오기

	::glutInitWindowSize(1920, 1080);  // 윈도우 크기 조정 
	::glutCreateWindow("THE NUN");

	//--- GLEW 초기화하기
	::glewExperimental = GL_TRUE;
	if (glewInit() != GLEW_OK) // glew 초기화
	{
		std::cerr << "glew 초기화 실패" << std::endl;
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




