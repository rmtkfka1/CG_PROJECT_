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

	void Render(const char* text);





private:

	GLuint _base;
	HDC _hdc;





};

