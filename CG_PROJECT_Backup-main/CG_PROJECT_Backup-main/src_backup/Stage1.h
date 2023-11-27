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


	//���̴�
	Shader* shader;
	//�÷��̾� ��ü
	Player* player;
	//��
	Model* player_model;
	Model* floor_model;
	Model* front_wall_upper_model;
	Model* front_wall_left_model;
	Model* front_wall_right_model;
	Model* back_wall_model;
	Model* left_wall_model;
	Model* right_wall_model;
	// �� ���� ������
	//�ؽ���
	Texture* texture;

	//�������
	vector<Wall*> v_wall;
	vector<Model*> room_model;
	// �̰� ��������
	//���� ��ü �����
	Light2* light;
};

