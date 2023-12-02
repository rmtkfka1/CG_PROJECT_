#pragma once


class TextManager
{

public:

	static TextManager* GetInstance()
	{
		static TextManager mg;
		return &mg;
	}

	void Init();
	void Render(float x, float y,const char* text);

private:
	GLuint _base;
	HDC _hdc;
	int _size=90;

};

