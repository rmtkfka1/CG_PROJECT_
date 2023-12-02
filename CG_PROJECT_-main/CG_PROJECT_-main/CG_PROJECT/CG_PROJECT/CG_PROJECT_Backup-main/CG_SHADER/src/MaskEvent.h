#pragma once
#include "Object.h"
class Mask;
class Event :public Object
{

	using Super = Object;

public:
	Event(Model& model);
	~Event();

	void Init() override;
	void Update() override;
	void Render(Shader& shader) override;

	bool GetCollison(){ return mask_collison; }
private:

	void OnComponentBeginOverlap(Collider* collider, Collider* other) override;
	void OnComponentEndOverlap(Collider* collider, Collider* other) override;

public:
	bool mask_collison = false;
	bool room2_box_collison= false;
};

