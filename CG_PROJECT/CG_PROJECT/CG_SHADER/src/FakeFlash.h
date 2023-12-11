#pragma once

#include "object.h"

class Model;
class Player;
class Light2;
class Flash;
class FakeFlash :public Object
{

	using Super = Object;

public:
	FakeFlash(Model& model);
	~FakeFlash();

	void Init() override;
	void Update() override;
	void UpdateFlash(Light2 *light, Flash* flash);
	void Render(Shader& shader) override;
	bool GetCollsionState() { return collision; }
	bool GetDrawTrue() { return draw; }
	
	void OnComponentBeginOverlap(Collider* collider, Collider* other) override;
	void OnComponentEndOverlap(Collider* collider, Collider* other) override;
public :
	bool draw=true;
	bool collision = false;
	bool spotoff = true;

};