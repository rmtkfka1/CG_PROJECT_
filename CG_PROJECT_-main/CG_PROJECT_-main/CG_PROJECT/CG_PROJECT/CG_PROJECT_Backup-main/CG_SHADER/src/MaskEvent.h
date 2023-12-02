#pragma once
#include "Object.h"
class Mask;
class MaskEvent :public Object
{

	using Super = Object;

public:
	MaskEvent(Model& model);
	~MaskEvent();

	void Init() override;
	void Update() override;
	void Render(Shader& shader) override;

	bool GetCollison(){ return _collison; }
private:

	void OnComponentBeginOverlap(Collider* collider, Collider* other) override;
	void OnComponentEndOverlap(Collider* collider, Collider* other) override;

	bool _collison = false;

};

