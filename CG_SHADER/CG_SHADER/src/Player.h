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
	void UpdatePos(); //ī�޶� ��ġ���°� �ڱ��Ʈ���� ����
	void Render(Shader& shader, Model& model) override;
	void KeyUpdate();

	void OnComponentBeginOverlap(Collider* collider, Collider* other) override;
	void OnComponentEndOverlap(Collider* collider, Collider* other) override;

private:
	float _speed=20.0f;
	

};