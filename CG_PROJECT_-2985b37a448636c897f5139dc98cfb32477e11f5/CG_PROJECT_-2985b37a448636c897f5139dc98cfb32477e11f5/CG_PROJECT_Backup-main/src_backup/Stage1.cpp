#include "pch.h"
#include "Stage1.h"
#include "Player.h"
#include "Wall.h"
#include "BoxCollider.h"
#include "CollisionManager.h"
#include "Light2.h"


Stage1::Stage1()
{
	

}

Stage1::~Stage1()
{


}

void Stage1::Init()
{

	shader = new Shader("res/shader/simple.vs", "res/shader/simple.fs");
	shader->Bind();

	///////////////////////////////////////////////////모델 불러오기 
	player_model = new Model("res/models/player.obj");
	floor_model = new Model("res/models/floor.obj");

	front_wall_upper_model = new Model("res/models/front_wall_upper.obj");
	front_wall_left_model = new Model("res/models/front_wall_left.obj");
	front_wall_right_model = new Model("res/models/front_wall_right.obj");
	back_wall_model = new Model("res/models/back_wall.obj");
	left_wall_model = new Model("res/models/left_wall.obj");
	right_wall_model = new Model("res/models/right_wall.obj");

	///////////////////////////////////////////////////////////////////////////////////////////

	///오브젝트 생성////////////////////////////////////////////////////////////////////////////
	{
		player = new Player(*player_model);
		BoxCollider* ptr = new BoxCollider;
		player->AddComponent(ptr);
		GET_SINGLE(CollisionManager)->AddCollider(ptr);

	}

	/////////첫번째 방 만들기//////////////////////////////////////////////////////////
	{
		// 바닥
		Wall* floor = new Wall(*floor_model);
		BoxCollider* ptr = new BoxCollider;
		floor->AddComponent(ptr);
		//	GET_SINGLE(CollisionManager)->AddCollider(ptr);
		v_wall.push_back(floor);
		room_model.push_back(floor_model);

		// 순서대로 앞, 뒤, 왼쪽, 오른쪽
		// 앞벽은 문 통과를 위해 3가지 파트로 나뉨
		Wall* front_wall_upper = new Wall(*front_wall_upper_model);
		BoxCollider* ptr2 = new BoxCollider;
		front_wall_upper->AddComponent(ptr2);
		GET_SINGLE(CollisionManager)->AddCollider(ptr2);
		v_wall.push_back(front_wall_upper);
		room_model.push_back(front_wall_upper_model);

		Wall* front_wall_left = new Wall(*front_wall_left_model);
		BoxCollider* ptr3 = new BoxCollider;
		front_wall_left->AddComponent(ptr3);
		GET_SINGLE(CollisionManager)->AddCollider(ptr3);
		v_wall.push_back(front_wall_left);
		room_model.push_back(front_wall_left_model);

		Wall* front_wall_right = new Wall(*front_wall_right_model);
		BoxCollider* ptr4 = new BoxCollider;
		front_wall_right->AddComponent(ptr4);
		GET_SINGLE(CollisionManager)->AddCollider(ptr4);
		v_wall.push_back(front_wall_right);
		room_model.push_back(front_wall_right_model);

		Wall* back_wall = new Wall(*back_wall_model);
		BoxCollider* ptr5 = new BoxCollider;
		back_wall->AddComponent(ptr5);
		GET_SINGLE(CollisionManager)->AddCollider(ptr5);
		v_wall.push_back(back_wall);
		room_model.push_back(back_wall_model);
		
		Wall* left_wall = new Wall(*left_wall_model);
		BoxCollider* ptr6 = new BoxCollider;
		left_wall->AddComponent(ptr6);
		GET_SINGLE(CollisionManager)->AddCollider(ptr6);
		v_wall.push_back(left_wall);
		room_model.push_back(left_wall_model);
		
		Wall* right_wall = new Wall(*right_wall_model);
		BoxCollider* ptr7 = new BoxCollider;
		right_wall->AddComponent(ptr7);
		GET_SINGLE(CollisionManager)->AddCollider(ptr7);
		v_wall.push_back(right_wall);
		room_model.push_back(right_wall_model);


	}
	///////////////////////////////////////////////////////////////////////////////////
	
	/////////텍스처 만들기/////////////////////////////////////////////////////////////
	texture = new Texture("res/textures/1.jpg");
	texture->Bind(0);

	////////////////////////조명작업///////////////////////////////////////////////////
	light = new Light2();
	light->UseLight(*shader);

	light->SetLightPos(glm::vec3(0, 10.0f, 0.0f));


	shader->SetUniformMat4f("u_proj", matrix::GetInstance()->GetProjection());
	///////////////////////////////////////////////////////////////////////////////////

	v_wall[0]->PrintInfo();

}

void Stage1::Update()
{

	CameraManager::GetInstance()->KeyUpdate();
	CameraManager::GetInstance()->MouseUpdate(MouseManager::GetInstance()->GetMousePos().x, MouseManager::GetInstance()->GetMousePos().y);

	player->Update();


	for (auto& ele : v_wall)
	{
		ele->Update();
	}

	if (KeyManager::GetInstance()->Getbutton(KeyType::SpaceBar))
	{
		light->_light.cutoff[1] += 1.0f;
		cout << "cutoff1" << endl;
		cout << light->_light.cutoff[1] << endl;
	}

	if (KeyManager::GetInstance()->Getbutton(KeyType::R))
	{
		light->_light.cutoff[0] -= 1.0f;
		cout << "cutoff0" << endl;
		cout << light->_light.cutoff[0] << endl;
	}
	

	GET_SINGLE(CollisionManager)->Update();

	shader->SetUniform3f("u_viewpos", CameraManager::GetInstance()->m_cameraPos.x, CameraManager::GetInstance()->m_cameraPos.y, CameraManager::GetInstance()->m_cameraPos.z);
	shader->SetUniformMat4f("u_view", CameraManager::GetInstance()->GetMatrix());

	light->_light.position = CameraManager::GetInstance()->m_cameraPos;
	light->_light.direction = CameraManager::GetInstance()->m_cameraFront;
	light->UseLight(*shader);


}

void Stage1::Render()
{


	player->Render(*shader, *player_model, matrix::GetInstance()->GetTranslation(player->GetCenter_x(), player->GetCenter_y(), player->GetCenter_z()));


	shader->SetUniform1i("u_texture", 0);
	//	for (auto& ele : v_wall)
	//	{
	//		ele->Render(*shader, *floor_model,matrix::GetInstance()->GetSimple());
	//		
	//	}
	

	for (int i = 0; i < v_wall.size(); i++)
	{
		v_wall.at(i)->Render(*shader, *room_model[i], matrix::GetInstance()->GetSimple());
	}

}
