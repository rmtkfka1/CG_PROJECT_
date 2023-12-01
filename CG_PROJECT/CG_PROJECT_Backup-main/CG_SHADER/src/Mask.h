#pragma once
#include "Object.h"
class Model;
class MaskEvent;
class Mask :public Object
{

	using Super = Object;

public:
	Mask(Model& model);
	~Mask();


	void Init() override;
	void Update() override;
	void Render(Shader& shader) override;

	void MatrixUpdate(MaskEvent* ptr);

	void OnComponentBeginOverlap(Collider* collider, Collider* other) override;
	void OnComponentEndOverlap(Collider* collider, Collider* other) override;

public:
	float speed = 200.0f;
	float delta = 0;
};