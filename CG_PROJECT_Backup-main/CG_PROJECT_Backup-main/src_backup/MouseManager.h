#pragma once

class MouseManager
{


public:
	static MouseManager* GetInstance()
	{
		static MouseManager MM;
		return &MM;
	}

	void Init();


	vec2 GetMousePos() { return m_pos; }




private:

	static void MouseCallBack(int button ,int state , int x, int y);
	static void MousemoveCallBack(int x, int y);
	static void MousemoveCallBack2(int x, int y);


	 vec2 m_pos;
	 bool m_click;
	 vec2 m_diff;
	 vec2 m_beforePos;

	

};

