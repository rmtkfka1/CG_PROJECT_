#pragma once
#include "Object.h"
class Model;
class Event;
class Mask :public Object
{

	using Super = Object;

public:
	Mask(Model& model);
	~Mask();


	void Init() override;
	void Update() override;
	void Render(Shader& shader) override;

	void MatrixUpdate(Event* ptr);

	void OnComponentBeginOverlap(Collider* collider, Collider* other) override;
	void OnComponentEndOverlap(Collider* collider, Collider* other) override;

public:

	bool play_sound = false;
	float speed = 200.0f;
	float delta = 0;
	bool realreal_end = false;
};