#pragma once

#include "Object.h"

class Model;

class Player :public Object
{

	using Super = Object;

public:
	Player(Model &model);
	~Player();


	void Init() override;
	void Update() override;
	void Render(Shader& shader, Model& model, glm::mat4 matrix) override;
	void KeyUpdate();

	void OnComponentBeginOverlap(Collider* collider, Collider* other) override;
	void OnComponentEndOverlap(Collider* collider, Collider* other) override;

public:
	
	bool _collusion = false;

};