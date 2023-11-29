#pragma once

class Model;
#include "Object.h"
class Wall :public Object
{

	using Super = Object;

public:
	Wall(Model& model);
	~Wall();

	void Init() override;
	void Update() override;
	void Render(Shader& shader) override;

	void OnComponentBeginOverlap(Collider* collider, Collider* other) override;
	void OnComponentEndOverlap(Collider* collider, Collider* other) override;

public:

	bool _collusion = false;

};