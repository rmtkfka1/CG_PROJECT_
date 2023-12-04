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
class LeftDoor;
class RightDoor;
class DeadBody;
class Event;
class Mask;
class ExitDoor;
class Locked;

class Stage1 : public Scene
{
public:
	Stage1();
	virtual ~Stage1();

	virtual void Init() override;
	void MakeRoom2_QUIZ();
	void MakeRoom1_QUIZ();
	void MakeTexture();
	virtual void Update() override;
	virtual void Render() override;


	
	void Object_Render();
	void Texture_Render();

private:

	void MakeRoom();

	void MakeEndRoom();
	void MakeLastRoom();
	void MakeLastCorridor();

	void MakeRoom6();
	void MakeRoom5();
	void MakeRoom4();
	void MakeRoom3();


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
	LeftDoor* Corridor_left_door;
	RightDoor* Corridor_right_door;
	DeadBody* deadbody;
	Event* mask_event;
	Mask* mask;
	ExitDoor* exitdoor;
	Model* exitdoor2;

	//��1���� ��ġ
	Wall* quizbox;
	Wall* Lockedbox;
	Wall* Lockedtable;
	Locked* Lockedkey;
	Event* quizbox_event;
	Model* answerbox;
	////////////////////

	//��2���� ��ġ
	Wall*   quizbox2;
	Wall*   Lockedbox2;
	Wall*   Lockedtable2;
	Locked* Lockedkey2;
	Wall*  answerbox2;


	////////////////


	vector<Object*> room1;

	vector<Object*> corridor1;

	vector<Object*> room2;

	vector<Object*> room3;
	
	vector<Object*> room4;
	
	vector<Object*> room5;
	
	vector<Object*> room6;
	
	vector<Object*> last_corridor;
	
	vector<Object*> last_room;
	
	vector<Object*> end_room;



	//�ؽ���
	Texture* texture;
	Texture* billboard_texture;
	Texture* light_texture;
	Texture* table_texture;
	Texture* flash_fake_texture;
	Texture* ghost_texture;
	Texture* door_texture;
	Texture* deadbody_texture;
	Texture* mask_texture;
	Texture* exitdoor_texture;
	Texture* quizbox_texture;
	Texture* lockedbox_texture;
	Texture* answer1_texture;
	//���� ��ü �����
	Light2* light;



	float xx;
};

