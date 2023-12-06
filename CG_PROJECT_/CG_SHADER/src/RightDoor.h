#pragma once

#include "Object.h"

class RightDoor:public Object
{
	using Super = Object;

public:
	RightDoor(Model& model);
	~RightDoor();

	void Init() override;
	void Update() override;
	void Render(Shader& shader) override;


	void OnComponentBeginOverlap(Collider* collider, Collider* other) override;
	void OnComponentEndOverlap(Collider* collider, Collider* other) override;

public:

	float _speed = 120.0f;
	float _degree = 0;
	bool _collusion = false;
	bool _test = false;

	std::chrono::steady_clock::time_point start_time; // 시작 시간 저장 변수

};

