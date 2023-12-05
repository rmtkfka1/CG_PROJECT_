#pragma once
#include "Scene.h"

class stage2: public Scene
{

public:
	stage2();
	virtual ~stage2();

	virtual void Init() override;
	virtual void Update() override;
	virtual void Render() override;
private:
	Shader* shader;

};

