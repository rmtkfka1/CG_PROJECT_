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


	//���̴�
	Shader* shader;
	Shader* text_shader;
	//�÷��̾� ��ü
	Player* player;
	Test* test;
	//��
	Model* player_model;
	Model* wall_model;
	Model* test_model;
	Model* ptr;


	//�ؽ���


	Texture* texture;
	Texture* texture2;
	Texture* texture3;


	//�������
	vector<Wall*> v_wall;

	//���� ��ü �����
	Light2* light;
};

