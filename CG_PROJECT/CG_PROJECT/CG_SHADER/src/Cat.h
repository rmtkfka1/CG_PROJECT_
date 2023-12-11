#pragma once
#pragma once

#include "Object.h"
class Model;

class Cat :public Object
{

	using Super = Object;

public:
	Cat(Model& model);
	~Cat();


	void Init() override;
	void Update() override;
	void Render(Shader& shader) override;

	void OnComponentBeginOverlap(Collider* collider, Collider* other) override;
	void OnComponentEndOverlap(Collider* collider, Collider* other) override;

public:

	float speed_gage = -0.67f;

	bool _run = false;
	bool _collusion = false;

};
