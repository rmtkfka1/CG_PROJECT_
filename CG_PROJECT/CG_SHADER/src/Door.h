#pragma once

class Model;
#include "Object.h"

enum class DoorStatus
{
	LOCKED,		// 잠겨있다
	UNLOCKED,	// 잠겨있지 않다
	OPENED,		// 열려있다
	OPENING,	// 열리는 중이다
	CLOSED,		// 닫혀있다
	CLOSING		// 닫히는 중이다
};

class DOOR :public Object
{

	using Super = Object;

public:
	DOOR(Model& model);
	~DOOR();

	void Init() override;
	void Update() override;
	void Render(Shader& shader) override;

	void OnComponentBeginOverlap(Collider* collider, Collider* other) override;
	void OnComponentEndOverlap(Collider* collider, Collider* other) override;

public:
	bool _collusion = false;

	DoorStatus _status = DoorStatus::LOCKED;

	float _degree = 0.0f;
	float _open_speed = 180.0f;
	glm::mat4 _door_matrix = glm::mat4(1.0f);
};