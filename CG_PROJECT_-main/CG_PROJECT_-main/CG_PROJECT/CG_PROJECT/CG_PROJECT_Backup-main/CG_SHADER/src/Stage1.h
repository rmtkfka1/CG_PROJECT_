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

	int screenWidth = glutGet(GLUT_SCREEN_WIDTH); // 모니터의 가로 해상도 가져오기
	int screenHeight = glutGet(GLUT_SCREEN_HEIGHT); // 모니터의 세로 해상도 가져오기


	//쉐이더
	Shader* shader;
	
	
	//각기 다른 텍스쳐를 적용해줘야 되는 애들//
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

	//방1퀴즈 배치
	Wall* quizbox;
	Wall* Lockedbox;
	Wall* Lockedtable;
	Locked* Lockedkey;
	Event* quizbox_event;
	Model* answerbox;
	////////////////////

	//방2퀴즈 배치
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



	//텍스쳐
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
	//조명 객체 만들기
	Light2* light;



	float xx;
};

