#pragma once
#include "enum.h"

class KeyManager
{
	DECLARE_SINGLE(KeyManager);

public:
	void Init();

	void Update();

	//누르고있을때
	bool Getbutton(KeyType key) { return GetState(key) == KeyState::PRESS; }

	//맨처음 눌렀을때
	bool GetbuttonDown(KeyType key) { return GetState(key) == KeyState::DOWN; }

	//맨처음 눌렀다가 땔대
	bool GetbuttonUp(KeyType key) { return GetState(key) == KeyState::UP; }

	vector<KeyState>& Getstate() { return _states; } //직접가져와서 사용하기
private:
	KeyState GetState(KeyType key) { return _states[static_cast<uint8>(key)]; }
	vector<KeyState> _states;



};
