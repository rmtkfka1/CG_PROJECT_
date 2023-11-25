#pragma once

#include "Object.h"
class Model;
#include "Object.h"
class Bottom :public Object
{

	using Super = Object;

public:

	Bottom(Model& model);
	~Bottom();

	void Init() override;
	void Update() override;
	void Render(Shader& shader, Model& model) override;

	void OnComponentBeginOverlap(Collider* collider, Collider* other) override;
	void OnComponentEndOverlap(Collider* collider, Collider* other) override;

public:



};