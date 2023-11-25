#pragma once

#include "Scene.h"


class Player;
class Model;
class Texture;
class Shader;
class Wall;
class Light2;


class Stage1 : public Scene
{
public:
	Stage1();
	virtual ~Stage1();

	virtual void Init() override;
	virtual void Update() override;
	virtual void Render() override;

public:


	//쉐이더
	Shader* shader;
	//플레이어 객체
	Player* player;
	//모델
	Model* player_model;
	Model* wall_model;
	//텍스쳐
	Texture* texture;

	//벽만들기
	vector<Wall*> v_wall;

	//조명 객체 만들기
	Light2* light;
};

