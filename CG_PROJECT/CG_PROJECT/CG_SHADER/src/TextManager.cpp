#include "pch.h"
#include "TextManager.h"

void TextManager::Init()
{

	_hdc = wglGetCurrentDC();

	HFONT font; // <1>
	_base = glGenLists(96); // <2>
	font = CreateFont(-70, // <3-1>
		0,
		0,
		0,
		FW_BOLD, // <3-2>
		FALSE, // <3-3>
		FALSE, // <3-4>
		FALSE, // <3-5>
		ANSI_CHARSET, // <3-6>
		OUT_TT_PRECIS,
		CLIP_DEFAULT_PRECIS,
		ANTIALIASED_QUALITY,
		FF_DONTCARE | DEFAULT_PITCH,
		LPCWSTR("Courier New")); // <3-6>

	SelectObject(_hdc, font); // <4>
	wglUseFontBitmaps(_hdc, 32, 96, _base); // <5>



}

void TextManager::Render(float x, float y, const char* text)
{

	glColor3f(1.0f, 1.0f, 1.0f); // Èò»ö
	glRasterPos2f(x, y);       //<2>
	glPushAttrib(GL_LIST_BIT); //<1>
	glListBase(_base - 32); //<2>
	glCallLists(strlen(text), GL_UNSIGNED_BYTE, text); //<3>
	glPopAttrib(); //<4>
}
