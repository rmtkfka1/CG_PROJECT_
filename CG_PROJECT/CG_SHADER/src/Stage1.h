#pragma once

#include "Scene.h"


class Player;
class Model;
class Billboard;
class Texture;
class Shader;
class Wall;
class Light2;
class Light_test;
class Object;
class Flash;
class FakeFlash;
class Ghost;

class Stage1 : public Scene
{
public:
	Stage1();
	virtual ~Stage1();

	virtual void Init() override;
	virtual void Update() override;
	virtual void Render() override;


	
	void Object_Render();
	void Texture_Render();

private:
	void MakeRoom();
	void MakeRoom3();
	void MakeCorridor2();
	void MakeRoom2();
	void MakeCorridor();
	void MakeRoom1();
	void ObjectInit();

private:

	int screenWidth = glutGet(GLUT_SCREEN_WIDTH); // ������� ���� �ػ� ��������
	int screenHeight = glutGet(GLUT_SCREEN_HEIGHT); // ������� ���� �ػ� ��������


	//���̴�
	Shader* shader;
	
	
	//���� �ٸ� �ؽ��ĸ� ��������� �Ǵ� �ֵ�//
	Player* player;
	Flash* flash;
	FakeFlash* fake_flash;
	Billboard* billboard;
	Wall* table;
	Ghost* ghost;
	////////////////////

	
	// pair�� Object�� Model�� �������
	vector<Object*> room1;

	// pair�� Object�� Model�� �������
	vector<Wall*> corridor1;

	// pair�� Object�� Model�� �������
	vector<Wall*> room2;

	// pair�� Object�� Model�� �������
	vector<Wall*> corridor2;

	// pair�� Object�� Model�� �������
	vector<Wall*> room3;


	//�ؽ���
	Texture* texture;
	Texture* billboard_texture;
	Texture* light_texture;
	Texture* table_texture;
	Texture* flash_fake_texture;
	Texture* ghost_texture;
	Texture* door_texture;

	//���� ��ü �����
	Light2* light;




};

