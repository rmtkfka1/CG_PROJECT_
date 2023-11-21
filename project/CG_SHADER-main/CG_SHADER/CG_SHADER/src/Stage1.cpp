#include "pch.h"
#include "Stage1.h"
#include "Player.h"
#include "Wall.h"
#include "BoxCollider.h"
#include "CollisionManager.h"


Stage1::Stage1()
{
	

}

Stage1::~Stage1()
{


}

void Stage1::Init()
{

	shader = new Shader("res/shader/mvp.vs", "res/shader/mvp.fs");
	shader->Bind();

	///////////////////////////////////////////////////모델 불러오기 밑에 생성전에 먼저해줘야됨
	player_model = new Model("res/models/player.obj");
	wall_model = new Model("res/models/wall.obj");
	///////////////////////////////////////////////////////////////////////////////////////////

	{
		player = new Player(*player_model);
		BoxCollider* ptr = new BoxCollider;
		player->AddComponent(ptr);
		GET_SINGLE(CollisionManager)->AddCollider(ptr);

	}

	{
		Wall* wall = new Wall(*wall_model);
		BoxCollider* ptr = new BoxCollider;
		wall->AddComponent(ptr);
		GET_SINGLE(CollisionManager)->AddCollider(ptr);
		v_wall.push_back(wall);
	}



	texture = new Texture("res/textures/box.jpg");
	texture->Bind(0);
	shader->SetUniform1i("u_texture", 0);



	shader->SetUniformMat4f("u_proj", matrix::GetInstance()->GetProjection());


}

void Stage1::Update()
{

	CameraManager::GetInstance()->KeyUpdate();
	CameraManager::GetInstance()->MouseUpdate(MouseManager::GetInstance()->GetMousePos().x, MouseManager::GetInstance()->GetMousePos().y);
	shader->SetUniformMat4f("u_view", CameraManager::GetInstance()->GetMatrix());

	player->Update();

	for (auto& ele : v_wall)
	{
		ele->Update();
	}

	GET_SINGLE(CollisionManager)->Update();

	// 업데이트 순서 변경됨

}

void Stage1::Render()
{

	
	player->Render(*shader, *player_model, matrix::GetInstance()->GetTranslation(player->GetCenter_x(), player->GetCenter_y(), player->GetCenter_z()));
	
	for (auto& ele : v_wall)
	{
		ele->Render(*shader, *wall_model,matrix::GetInstance()->GetSimple());
	}

}
