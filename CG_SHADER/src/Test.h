#pragma once



#include "Object.h"

class Test:public Object
{

	using Super = Object;

public:
	Test(Model& model);
	~Test();

	void Init() override;
	void Update() override;
	void Render(Shader& shader, Model& model, glm::mat4 matrix) override;

	void OnComponentBeginOverlap(Collider* collider, Collider* other) override;
	void OnComponentEndOverlap(Collider* collider, Collider* other) override;

public:

	bool _collusion = false;

};

