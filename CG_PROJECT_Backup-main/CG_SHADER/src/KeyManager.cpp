#include "pch.h"
#include "KeyManager.h"
#include "enum.h"


void KeyManager::Init()
{
	_states.resize(KEY_TYPE_COUNT, KeyState::NONE);
}

void KeyManager::Update()
{
	BYTE asciiKeys[KEY_TYPE_COUNT] = {};
	if (GetKeyboardState(asciiKeys) == false)
		return;

	for (uint32 key = 0; key < KEY_TYPE_COUNT; key++)
	{
		if (asciiKeys[key] & 0x80)
		{
			KeyState& state = _states[key];

			if (state == KeyState::PRESS || state == KeyState::DOWN)
				state = KeyState::PRESS;
			else
				state = KeyState::DOWN;
		}

		//Å°º¸µå¶«
		else
		{
			KeyState& state = _states[key];

			if (state == KeyState::PRESS || state == KeyState::DOWN)
				state = KeyState::UP;
			else
				state = KeyState::UP;
		}
	}


}
