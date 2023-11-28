#pragma once

#include "Scene.h"


class Player;
class Model;
class Billboard;
class Texture;
class Shader;
class Wall;
class Light2;
class Object;

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
	Shader* spot_shader;
	Shader* point_shader;
	//플레이어 객체
	Player* player;
	//빌보드(테스트)
	Billboard* billboard;

	//모델
	Model* player_model;
	Model* flash;
	Model* b_plane;

	// pair로 Object와 Model을 묶어버림
	vector<pair<Object*, Model*>> room1;

	// pair로 Object와 Model을 묶어버림
	vector<pair<Object*, Model*>> corridor1;

	// pair로 Object와 Model을 묶어버림
	vector<pair<Object*, Model*>> room2;

	// pair로 Object와 Model을 묶어버림
	vector<pair<Object*, Model*>> corridor2;

	// pair로 Object와 Model을 묶어버림
	vector<pair<Object*, Model*>> room3;

	//텍스쳐
	Texture* texture;
	Texture* flash_texture;
	Texture* billboard_texture;
	Texture* light_texture;

	//벽만들기
	vector<Wall*> v_wall;
	//vector<Model*> room_model;

	//조명 객체 만들기
	Light2* light;

	// 손전등 회전행렬
	glm::mat4 flash_matrix;

};

