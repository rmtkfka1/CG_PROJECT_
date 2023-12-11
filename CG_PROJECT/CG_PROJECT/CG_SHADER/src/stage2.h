#pragma once
#include "Scene.h"

class shader;
class Texture;
class Model;

class stage2: public Scene
{

public:
	stage2();
	virtual ~stage2();

	virtual void Init() override;
	virtual void Update() override;
	virtual void Render() override;


private:
	Model* model;
	Shader* shader;
	Texture* texture;

	bool start = false;
	bool onetime = false;
	std::chrono::steady_clock::time_point start_time; // 시작 시간 저장 변수
};

