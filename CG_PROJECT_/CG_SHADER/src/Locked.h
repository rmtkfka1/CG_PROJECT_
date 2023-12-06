#pragma once
#include "Object.h"

class ExitDoor;

class Locked:public Object
{

	using Super = Object;

public:
	Locked(Model& model,int answer[4]);
	~Locked();

	void Init() override;
	void Update() override;
	void SpecialUpdate(ExitDoor* ptr);
	void Render(Shader& shader) override;
	bool LockedAndCollusion() { return _collusion && _locked; }

	void OnComponentBeginOverlap(Collider* collider, Collider* other) override;
	void OnComponentEndOverlap(Collider* collider, Collider* other) override;

	

public:

	float _speed = 120.0f;
	float _degree = 0;



	bool _collusion = false; //자물쇠충돌
	bool _locked = true;  //1번방자물쇠락
	bool sound_event = false;  
	
public:

	int _first_set[4] = { 0,0,0,0 }; //초기값
	int _answer[4] = { 0,0,0,0 };  //정답

};


