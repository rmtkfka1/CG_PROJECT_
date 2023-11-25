#include "pch.h"
#include "Stage1.h"
#include "Player.h"
#include "Wall.h"
#include "BoxCollider.h"
#include "CollisionManager.h"
#include "Light2.h"
#include "Bottom.h"

Stage1::Stage1()
{
	

}

Stage1::~Stage1()
{


}

void Stage1::Init()
{

	shader = new Shader("res/shader/mvp_spotlight.vs", "res/shader/mvp_spotlight.fs");
	shader->Bind();

	///////////////////////////////////////////////////�� �ҷ����� 
	player_model = new Model("res/models/player.obj");
	wall_model = new Model("res/models/wall.obj");
	plane_model = new Model("res/models/plane.obj");

	///////////////////////////////////////////////////////////////////////////////////////////

	///������Ʈ ����////////////////////////////////////////////////////////////////////////////
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

	{
		bottom = new Bottom(*plane_model);
		BoxCollider* ptr = new BoxCollider;
		bottom->AddComponent(ptr);
		GET_SINGLE(CollisionManager)->AddCollider(ptr);
	}

	{
		Wall* wall = new Wall(*wall_model);

		BoxCollider* ptr = new BoxCollider;
		wall->AddComponent(ptr);
		GET_SINGLE(CollisionManager)->AddCollider(ptr);
		v_wall.push_back(wall);
	}


	///////////////////////////////////////////////////////////////////////////////////
	
	/////////�ؽ�ó �����/////////////////////////////////////////////////////////////
	texture = new Texture("res/textures/1.jpg");
	texture->Bind(0);

	////////////////////////�����۾�///////////////////////////////////////////////////
	light = new Light2();
	light->UseLight(*shader);

	light->SetLightPos(glm::vec3(0, 10.0f, 0.0f));


	shader->SetUniformMat4f("u_proj", matrix::GetInstance()->GetProjection());
	///////////////////////////////////////////////////////////////////////////////////

	bottom->PrintInfo();
	
}

void Stage1::Update()
{

	// �÷��̾� ��ġ ������Ʈ 
	player->Update(); 
	//�׿� ���� ī�޶� ��ġ ����
	CameraManager::GetInstance()->PosUpdate(player);
	CameraManager::GetInstance()->MouseUpdate(MouseManager::GetInstance()->GetMousePos().x, MouseManager::GetInstance()->GetMousePos().y);

	//�׿����� ���ο� ���Ʈ���� ����
	shader->SetUniformMat4f("u_view", CameraManager::GetInstance()->GetMatrix());

	bottom->Update();

	for (auto& ele : v_wall)
	{
		ele->Update();
	}

	GET_SINGLE(CollisionManager)->Update();


	



}



void Stage1::Render()
{

	
	player->Render(*shader, *player_model);
	

	shader->SetUniform1i("u_texture", 0);
	for (auto& ele : v_wall)
	{
		
		ele->Render(*shader, *wall_model);
	}
	shader->SetUniform1i("u_texture", 0);
	bottom->Render(*shader, *plane_model);


}
