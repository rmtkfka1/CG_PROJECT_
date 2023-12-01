#pragma once
#include "Object.h"

class FakeFlash;
class DeadBody :public Object
{

	using Super = Object;

public:
	DeadBody(Model& model);
	~DeadBody();

	void Init() override;
	void Update() override;
	
	void SpecialRender(Shader& shader, FakeFlash* ptr);


private:

	




};

