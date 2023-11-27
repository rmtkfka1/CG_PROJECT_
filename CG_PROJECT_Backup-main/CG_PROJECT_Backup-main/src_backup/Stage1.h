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
	Model* floor_model;
	Model* front_wall_upper_model;
	Model* front_wall_left_model;
	Model* front_wall_right_model;
	Model* back_wall_model;
	Model* left_wall_model;
	Model* right_wall_model;
	// 다 별도 벽모델이
	//텍스쳐
	Texture* texture;

	//벽만들기
	vector<Wall*> v_wall;
	vector<Model*> room_model;
	// 이걸 만들었어용
	//조명 객체 만들기
	Light2* light;
};

