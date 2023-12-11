#pragma once
#include "Object.h"
class Mask;
class Event :public Object
{

	using Super = Object;

public:
	Event(Model& model,string type);
	~Event();

	void Init() override;
	void Update() override;
	void Render(Shader& shader) override;

	bool GetCollison(){ return _collison_onetime; }
private:

	void OnComponentBeginOverlap(Collider* collider, Collider* other) override;
	void OnComponentEndOverlap(Collider* collider, Collider* other) override;

public:


	bool _collison_onetime = false;
	bool _collison_everytime= false;
	string _type;
	bool scare_sound1;
};

