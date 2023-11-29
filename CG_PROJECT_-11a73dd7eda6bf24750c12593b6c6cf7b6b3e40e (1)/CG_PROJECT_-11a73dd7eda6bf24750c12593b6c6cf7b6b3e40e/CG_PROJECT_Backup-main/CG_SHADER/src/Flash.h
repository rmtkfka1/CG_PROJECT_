#pragma once

#include "Object.h"

class Model;
class Player;

class Flash :public Object
{

	using Super = Object;

public:
	Flash(Model& model);
	~Flash();

	void Init() override;
	void Update() override;
	void MatrixUpdate(Player *player);
	void Render(Shader& shader) override;
	void SetLighton() { lighton != lighton; }

private:

	bool lighton = false;

};