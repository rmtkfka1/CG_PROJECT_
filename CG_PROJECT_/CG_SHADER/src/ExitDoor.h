#pragma once

#include "Object.h"
class ExitDoor: public Object
{
	using Super = Object;

public:
	ExitDoor(Model& model);
	~ExitDoor();

	void Init() override;
	void Update() override;
	void Render(Shader& shader) override;
	bool LockedAndCollusion() { return _collusion && locked ; }

	void OnComponentBeginOverlap(Collider* collider, Collider* other) override;
	void OnComponentEndOverlap(Collider* collider, Collider* other) override;

public:

	float _speed = 120.0f;
	float _degree = 0;
	bool _collusion = false;
	bool locked = true;






};


