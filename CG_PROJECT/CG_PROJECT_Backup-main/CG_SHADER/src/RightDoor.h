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

	void MatrixUpdate();
	

	void OnComponentBeginOverlap(Collider* collider, Collider* other) override;
	void OnComponentEndOverlap(Collider* collider, Collider* other) override;

public:

	bool _collusion = false;
};

