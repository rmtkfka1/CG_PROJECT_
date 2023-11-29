#pragma once
#include "pch.h"

enum class SHAPE
{
	dot = 0,
	rectangle,
	triangle,
};

enum class DIR
{
	UP_RIGHT,
	UP_LEFT,
	DOWN_RIGHT,
	DOWN_LEFT,
	LEFT,
	RIGHT,
	UP,
	DOWN,
};

enum class ColliderType
{
	Box,
	Sphere,
};


enum class KeyType
{
	LeftMouse = VK_LBUTTON,
	RightMouse = VK_RBUTTON,
	SpaceBar = VK_SPACE,
	ESC = VK_ESCAPE,

	A = 'A',
	B = 'B',
	C = 'C',
	D = 'D',
	E = 'E',
	F = 'F',
	G = 'G',
	H = 'H',
	I = 'I',
	J = 'J',
	K = 'K',
	L = 'L',
	M = 'M',
	N = 'N',
	O = 'O',
	P = 'P',
	Q = 'Q',
	R = 'R',
	S = 'S',
	T = 'T',
	U = 'U',
	V = 'V',
	W = 'W',
	X = 'X',
	Y = 'Y',
	Z = 'Z',
	ONE='1',
	TWO='2',
	THREE='3',
	FOUR='4',
	FIVE='5',
	SIX='6',
	SEVEN='7',
	EIGHT='8',
	NINE='9',
	Up = VK_UP,
	Down = VK_DOWN,
	Left = VK_LEFT,
	Right = VK_RIGHT,

	Plus='+',
	Minus='-',
	a='a',


};

enum class KeyState
{
	NONE,//아무것도 아닌상태
	PRESS, //누르고있는상태
	DOWN, //한번눌림
	UP, //키보드 자판땜
	END
};

enum
{
	KEY_TYPE_COUNT = static_cast<int32>(UINT8_MAX) + 1,
	KEY_STATE_COUNT = static_cast<int32>(KeyState::END)
};
