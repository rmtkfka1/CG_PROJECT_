#pragma once

class Core
{
public:

	static Core* GetInstance()
	{
		static Core mg;
		return &mg;
	}


private:
	Core();
	~Core();

public:

	void Init(int argc, char** argv);// argc,argv,윈도우x,윈도우y
	void Render(void (*funcptr)(void));// 그리기 
	void Reshape(void (*funcptr)(int, int));
	void Keyboard(void (*funcptr)(unsigned char, int, int)); //키입력 
	void mousein(void (*funcptr)(int button, int state, int x, int y)); //마우스입력
	void mouse_move(void (*funcptr)(int x, int y));


	vec2 convert(int x, int y, int WINDOW_WIDTH, int WINDOW_HEIGHT);




};
