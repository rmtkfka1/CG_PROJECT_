#pragma once

#include "Scene.h"


class Player;
class Model;
class Texture;
class Shader;
class Wall;
class Test;
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
	Shader* text_shader;
	//플레이어 객체
	Player* player;
	Test* test;
	//모델
	Model* player_model;
	Model* wall_model;
	Model* test_model;
	Model* ptr;


	//텍스쳐


	Texture* texture;
	Texture* texture2;
	Texture* texture3;


	//벽만들기
	vector<Wall*> v_wall;

	//조명 객체 만들기
	Light2* light;
};

