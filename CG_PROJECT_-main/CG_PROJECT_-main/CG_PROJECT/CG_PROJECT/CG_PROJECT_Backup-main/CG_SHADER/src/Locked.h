#pragma once
#include "Object.h"

class Locked:public Object
{

	using Super = Object;

public:
	Locked(Model& model);
	~Locked();

	void Init() override;
	void Update() override;
	void Render(Shader& shader) override;
	bool LockedAndCollusion() { return _collusion && locked2; }

	void OnComponentBeginOverlap(Collider* collider, Collider* other) override;
	void OnComponentEndOverlap(Collider* collider, Collider* other) override;


public:

	float _speed = 120.0f;
	float _degree = 0;
	bool _collusion = false;
	bool locked2 = true;
	
public:



	int num2[4] = { 0,0,0,0 }; //2번방 정답
	


};

