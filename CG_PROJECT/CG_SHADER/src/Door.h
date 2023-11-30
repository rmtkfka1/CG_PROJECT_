#pragma once

class Model;
#include "Object.h"

enum class DoorStatus
{
	LOCKED,		// ����ִ�
	UNLOCKED,	// ������� �ʴ�
	OPENED,		// �����ִ�
	OPENING,	// ������ ���̴�
	CLOSED,		// �����ִ�
	CLOSING		// ������ ���̴�
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