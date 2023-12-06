#pragma once

#include "Object.h"
class Model;

class Player :public Object
{

	using Super = Object;

public:
	Player(Model& model);
	~Player();


	void Init() override;
	void Update() override;
	void Render(Shader& shader) override;

	void MatrixUpdate();
	void KeyUpdate();

	void DrawGage();
	
	void OnComponentBeginOverlap(Collider* collider, Collider* other) override;
	void OnComponentEndOverlap(Collider* collider, Collider* other) override;

public:
	
	float speed_gage = -0.67f;

	bool _run = false;
	bool _collusion = false;

};