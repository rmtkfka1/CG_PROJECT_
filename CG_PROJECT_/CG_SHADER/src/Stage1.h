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
class Cat;
class Spherequiz;
class ENDING;

class Stage1 : public Scene
{
public:
	Stage1();
	virtual ~Stage1();

	virtual void Init() override;
	virtual void Update() override;
	virtual void Render() override;


	
	void Object_Render();
	void Object_Render2();
	void Texture_Render();

private:
	void MakeRoom1_QUIZ();
	void MakeRoom2_QUIZ();
	void MakeRoom3_QUIZ();
	void MakeRoom4_QUIZ();
	void MakeTexture();


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
	Shader* shader2; //������
	
	
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
	Locked* exitdoor_rocked;
	Cat* cat;
	Event* computer;

	//��1���� ��ġ
	Wall* quizbox;
	Event* quizbox_event;

	Wall* Lockedbox;
	Wall* Lockedtable;
	Locked* Lockedkey;
	Model* answerbox;

	////////////////////

	//��2���� ��ġ
	Wall*   Lockedbox2;
	Wall*   Lockedtable2;
	Locked* Lockedkey2;
	Wall*  answerbox2;
	Model* render_box;
	Model* render_box2;
	Model* render_box3;
	Model* ending_box;
	Model* fish;
	Model* starfish;
	Model* balls;
	Model* mapping_quiz;

	Wall* box1;
	Wall* box2;
	Wall* box3;
	Wall* box4;

	Wall* wall1;
	Wall* wall2;
	

	////////////////
	//��3���� ��ġ
	Wall* Lockedbox3;
	Wall* Lockedtable3;
	Locked* Lockedkey3;
	Wall* answerbox3;
	Spherequiz* sphere_quiz;

	//��4���� ��ġ
	Wall* Lockedbox4;
	Wall* Lockedtable4;
	Locked* Lockedkey4;
	Wall* answerbox4;
	Wall* prof;
	Event* room4_event;


	//��������
	Wall* computer_table;
	ENDING* end;




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
	Texture* answer1_texture; //1
	Texture* answer2_texture; //2
	Texture* answer3_texture; //1
	Texture* answer4_texture; //5
	Texture* room2_puzzle;
	Texture* fish_texture;
	Texture* box_texture;
	Texture* starfish_texture;
	Texture* zz_texture;
	Texture* room4_puzzle;
	Texture* snape_texture;
	Texture* cat_texture;
	Texture* computer_texture;
	Texture* sphere_texture;
	Texture* die_texture;
	Texture* end_texture;
	Texture* mapping_texture;
	//���� ��ü �����
	Light2* light;


	/// <summary>
	/// ////
	/// </summary>

};

