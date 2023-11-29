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

private:

	int screenWidth = glutGet(GLUT_SCREEN_WIDTH); // 모니터의 가로 해상도 가져오기
	int screenHeight = glutGet(GLUT_SCREEN_HEIGHT); // 모니터의 세로 해상도 가져오기


	//쉐이더
	Shader* shader;
	//플레이어 객체
	Player* player;
	Flash* flash;
	//빌보드(테스트)
	Billboard* billboard;

	//모델
	Model* player_model;
	Model* flash_model;
	Model* flash_fake;
	Model* b_plane;


	// pair로 Object와 Model을 묶어버림
	vector<Object*> room1;

	// pair로 Object와 Model을 묶어버림
	vector<Object*> corridor1;

	// pair로 Object와 Model을 묶어버림
	vector<Object*> room2;

	// pair로 Object와 Model을 묶어버림
	vector<Object*> corridor2;

	// pair로 Object와 Model을 묶어버림
	vector<Object*> room3;


	//텍스쳐
	Texture* texture;
	Texture* billboard_texture;
	Texture* light_texture;
	Texture* table_texture;
	Texture* flash_fake_texture;

	//조명 객체 만들기
	Light_test* light_test;
	Light2* light;




};

