#include "pch.h"
#include "Stage1.h"
#include "Player.h"
#include "Wall.h"
#include "Billboard.h"
#include "BoxCollider.h"
#include "CollisionManager.h"
#include "Light2.h"
#include "Light.h"
#include "Flash.h"
#include "FakeFlash.h"
#include "Ghost.h"
#include "LeftDoor.h"



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

	shader->SetUniformMat4f("u_proj", matrix::GetInstance()->GetProjection());


	///////////////////////////////////////////////////모델 불러오기 





	{
		//고스트 생성

		Model* ghost_body = new Model("res/models/ghost/ghost_body.obj");
		Model* ghost_left_arm = new Model("res/models/ghost/ghost_left_arm_test.obj");
		Model* ghost_right_arm = new Model("res/models/ghost/ghost_right_arm_test.obj");

		ghost = new Ghost(*ghost_body, *ghost_left_arm, *ghost_right_arm);
		ghost->Init();
		ghost->SetPosition(-25.0f, -25.0f);
	

	}

	{
		//탁자생성
		Model* table_model = new Model("res/models/table.obj");
		table = new Wall(*table_model);
		BoxCollider* ptr = new BoxCollider;
		table->AddComponent(ptr);
		GET_SINGLE(CollisionManager)->AddCollider(ptr);
	}

	//탁자위에 놓인 플래쉬
	{
		Model* flash_fake_m = new Model("res/models/flash.obj");
		fake_flash = new FakeFlash(*flash_fake_m);
		BoxCollider* ptr = new BoxCollider;
		fake_flash->AddComponent(ptr);
		GET_SINGLE(CollisionManager)->AddCollider(ptr);

	}

	///오브젝트 생성////////////////////////////////////////////////////////////////////////////
	{
		Model* player_model = new Model("res/models/stage1/player.obj");
		player = new Player(*player_model);
		BoxCollider* ptr = new BoxCollider;
		player->AddComponent(ptr);
		GET_SINGLE(CollisionManager)->AddCollider(ptr);
	}

	{
		Model* flash_model = new Model("res/models/stage1/flash.obj");
		flash = new Flash(*flash_model);
	}

	{
		Model* b_plane = new Model("res/models/billboard_plane/billboard_plane.obj");
		billboard = new Billboard(*b_plane);
		BoxCollider* ptr = new BoxCollider;
		billboard->AddComponent(ptr);
		billboard->SetSize(5.0f, 5.0f);
	}

	{
		Model* temp = new Model("res/models/corridor1/door_left.obj");
		Corridor_left_door = new LeftDoor(*temp);
		BoxCollider* ptr = new BoxCollider;
		Corridor_left_door->AddComponent(ptr);
		GET_SINGLE(CollisionManager)->AddCollider(ptr);
	}

	
	MakeRoom();


	/////////텍스처 만들기/////////////////////////////////////////////////////////////
	texture = new Texture("res/textures/block.jpg");
	billboard_texture = new Texture("res/textures/billboard_test.png");
	light_texture = new Texture("res/textures/light.jpg");
	table_texture = new Texture("res/textures/table.png");
	flash_fake_texture = new Texture("res/textures/flash_fake.jpg");
	ghost_texture = new Texture("res/textures/SM_text.png");

	texture->Bind(0);
	flash_fake_texture->Bind(1);
	billboard_texture->Bind(2);
	light_texture->Bind(3);
	table_texture->Bind(4);
	ghost_texture->Bind(5);

	////////////////////////조명작업///////////////////////////////////////////////////
	light = new Light2();
	light->UseSpotLight(*shader);


	///////////////////////////////////////////////////////////////////////////////////
	ObjectInit();


	


}


void Stage1::Update()
{


	CameraManager::GetInstance()->KeyUpdate();
	CameraManager::GetInstance()->MouseUpdate(MouseManager::GetInstance()->GetMousePos().x, MouseManager::GetInstance()->GetMousePos().y);

	player->Update();

	flash->MatrixUpdate(player);
	Corridor_left_door->Update();
	Corridor_left_door->MatrixUpdate(player);

	fake_flash->Update();
	fake_flash->UpdateFlash(light, flash);
	
	table->Update();



	GET_SINGLE(CollisionManager)->Update();

	for (int i = 0; i < room1.size(); i++)
	{
		room1[i]->Update();
	}

	for (int i = 0; i < corridor1.size(); i++)
	{
		corridor1[i]->Update();
	}

	for (int i = 0; i < room2.size(); i++)
	{
		room2[i]->Update();
	}
	
	for (int i = 0; i < room3.size(); i++)
	{
		room3[i]->Update();
	}

	for (int i = 0; i < room4.size(); i++)
	{
		room4[i]->Update();
	}

	for (int i = 0; i < room5.size(); i++)
	{
		room5[i]->Update();
	}
	
	for (int i = 0; i < room6.size(); i++)
	{
		room6[i]->Update();
	}


	shader->SetUniform3f("u_viewpos", CameraManager::GetInstance()->m_cameraPos.x, CameraManager::GetInstance()->m_cameraPos.y, CameraManager::GetInstance()->m_cameraPos.z);
	shader->SetUniformMat4f("u_view", CameraManager::GetInstance()->GetMatrix());

	light->Spot_light.position = CameraManager::GetInstance()->m_cameraPos;
	light->Spot_light.direction = CameraManager::GetInstance()->m_cameraFront;
	light->UseSpotLight(*shader);

	ghost->UpdatePlayerLocation(player->GetCenter());
	ghost->Update();
	billboard->Update();



}

void Stage1::Render()
{

	Object_Render();
	

	Texture_Render();


	

}

void Stage1::Object_Render()
{


	glViewport(0, 0, screenWidth, screenHeight);


	{
		shader->SetUniform1i("u_texture", 0);
		player->Render(*shader);
	}


	light->UseSpotLight(*shader);

	for (int i = 0; i < room1.size(); i++)
	{
		room1[i]->Render(*shader);
	}

	for (int i = 0; i < corridor1.size(); i++)
	{
		corridor1[i]->Render(*shader);
	}

	for (int i = 0; i < room2.size(); i++)
	{
		room2[i]->Render(*shader);
	}
	
	for (int i = 0; i < room3.size(); i++)
	{
		room3[i]->Render(*shader);
	}
	
	for (int i = 0; i < room4.size(); i++)
	{
		room4[i]->Render(*shader);
	}
	
	for (int i = 0; i < room5.size(); i++)
	{
		room5[i]->Render(*shader);
	}
	
	for (int i = 0; i < room6.size(); i++)
	{
		room6[i]->Render(*shader);
	}



	{
		shader->SetUniform1i("u_texture", flash_fake_texture->GetSlot());
		fake_flash->Render(*shader);
	}

	{
		shader->SetUniform1i("u_texture", 2);
		billboard->Render(*shader);
	}

	{
		shader->SetUniform1i("u_texture", table_texture->GetSlot());
		table->Render(*shader);
	}

	{
		shader->SetUniform1i("u_texture", ghost_texture->GetSlot());
		ghost->Render(*shader);
	}

	{
		shader->SetUniform1i("u_texture", flash_fake_texture->GetSlot());
		flash->Render(*shader);
	}

	{
		shader->SetUniform1i("u_texture", flash_fake_texture->GetSlot());
		Corridor_left_door->Render(*shader);
	}

}

void Stage1::Texture_Render()
{

	glViewport(0, 0, screenWidth, 300);


}

void Stage1::MakeRoom()
{
	MakeRoom1();

	MakeCorridor();

	MakeRoom2();

	MakeRoom3();
	
	MakeRoom4();

	MakeRoom5();
	
	MakeRoom6();


}

void Stage1::MakeRoom6()
{
	Model* model_front = new Model("res/models/room4/front.obj");
	Model* model_back = new Model("res/models/room4/back.obj");
	Model* model_left = new Model("res/models/room4/left.obj");
	Model* model_right = new Model("res/models/room4/right.obj");

	{
		Wall* front = new Wall(*model_front);
		BoxCollider* ptr = new BoxCollider;
		front->AddComponent(ptr);
		GET_SINGLE(CollisionManager)->AddCollider(ptr);
		room6.push_back(front);
	}

	{
		Wall* back = new Wall(*model_back);
		BoxCollider* ptr = new BoxCollider;
		back->AddComponent(ptr);
		GET_SINGLE(CollisionManager)->AddCollider(ptr);
		room6.push_back(back);
	}

	{
		Wall* left = new Wall(*model_left);
		BoxCollider* ptr = new BoxCollider;
		left->AddComponent(ptr);
		GET_SINGLE(CollisionManager)->AddCollider(ptr);
		room6.push_back(left);
	}

	{
		Wall* right = new Wall(*model_right);
		BoxCollider* ptr = new BoxCollider;
		right->AddComponent(ptr);
		GET_SINGLE(CollisionManager)->AddCollider(ptr);
		room6.push_back(right);
	}
}

void Stage1::MakeRoom5()
{
	Model* model_front = new Model("res/models/room3/front.obj");
	Model* model_back = new Model("res/models/room3/back.obj");
	Model* model_left = new Model("res/models/room3/left.obj");
	Model* model_right = new Model("res/models/room3/right.obj");

	{
		Wall* front = new Wall(*model_front);
		BoxCollider* ptr = new BoxCollider;
		front->AddComponent(ptr);
		GET_SINGLE(CollisionManager)->AddCollider(ptr);
		room5.push_back(front);
	}

	{
		Wall* back = new Wall(*model_back);
		BoxCollider* ptr = new BoxCollider;
		back->AddComponent(ptr);
		GET_SINGLE(CollisionManager)->AddCollider(ptr);
		room5.push_back(back);
	}

	{
		Wall* left = new Wall(*model_left);
		BoxCollider* ptr = new BoxCollider;
		left->AddComponent(ptr);
		GET_SINGLE(CollisionManager)->AddCollider(ptr);
		room5.push_back(left);
	}

	{
		Wall* right = new Wall(*model_right);
		BoxCollider* ptr = new BoxCollider;
		right->AddComponent(ptr);
		GET_SINGLE(CollisionManager)->AddCollider(ptr);
		room5.push_back(right);
	}
}

void Stage1::MakeRoom4()
{
	Model* model_front = new Model("res/models/room2/front.obj");
	Model* model_back = new Model("res/models/room2/back.obj");
	Model* model_left = new Model("res/models/room2/left.obj");
	Model* model_right = new Model("res/models/room2/right.obj");

	{
		Wall* front = new Wall(*model_front);
		BoxCollider* ptr = new BoxCollider;
		front->AddComponent(ptr);
		GET_SINGLE(CollisionManager)->AddCollider(ptr);
		room4.push_back(front);
	}

	{
		Wall* back = new Wall(*model_back);
		BoxCollider* ptr = new BoxCollider;
		back->AddComponent(ptr);
		GET_SINGLE(CollisionManager)->AddCollider(ptr);
		room4.push_back(back);
	}

	{
		Wall* left = new Wall(*model_left);
		BoxCollider* ptr = new BoxCollider;
		left->AddComponent(ptr);
		GET_SINGLE(CollisionManager)->AddCollider(ptr);
		room4.push_back(left);
	}

	{
		Wall* right = new Wall(*model_right);
		BoxCollider* ptr = new BoxCollider;
		right->AddComponent(ptr);
		GET_SINGLE(CollisionManager)->AddCollider(ptr);
		room4.push_back(right);
	}
}

void Stage1::MakeRoom3()
{
	Model* model_front = new Model("res/models/room1/front.obj");
	Model* model_back = new Model("res/models/room1/back.obj");
	Model* model_left = new Model("res/models/room1/left.obj");
	Model* model_right = new Model("res/models/room1/right.obj");

	{
		Wall* front = new Wall(*model_front);
		BoxCollider* ptr = new BoxCollider;
		front->AddComponent(ptr);
		GET_SINGLE(CollisionManager)->AddCollider(ptr);
		room3.push_back(front);
	}
	
	{
		Wall* back = new Wall(*model_back);
		BoxCollider* ptr = new BoxCollider;
		back->AddComponent(ptr);
		GET_SINGLE(CollisionManager)->AddCollider(ptr);
		room3.push_back(back);
	}
	
	{
		Wall* left = new Wall(*model_left);
		BoxCollider* ptr = new BoxCollider;
		left->AddComponent(ptr);
		GET_SINGLE(CollisionManager)->AddCollider(ptr);
		room3.push_back(left);
	}
	
	{
		Wall* right = new Wall(*model_right);
		BoxCollider* ptr = new BoxCollider;
		right->AddComponent(ptr);
		GET_SINGLE(CollisionManager)->AddCollider(ptr);
		room3.push_back(right);
	}

}

void Stage1::MakeRoom2()
{

	Model* room2_floor_model = new Model("res/models/stage2/floor.obj");
	Model* room2_ceiling_model = new Model("res/models/stage2/ceiling.obj");
	Model* room2_front_wall_upper_model = new Model("res/models/stage2/front1.obj");
	Model* room2_front_wall_left_model = new Model("res/models/stage2/front2.obj");
	Model* room2_front_wall_right_model = new Model("res/models/stage2/front3.obj");
	Model* room2_back_wall_upper_model = new Model("res/models/stage2/back1.obj");
	Model* room2_back_wall_left_model = new Model("res/models/stage2/back2.obj");
	Model* room2_back_wall_right_model = new Model("res/models/stage2/back3.obj");
	Model* room2_left_wall_model = new Model("res/models/stage2/left.obj");
	Model* room2_right_wall_model = new Model("res/models/stage2/right.obj");


	// 바닥
	Wall* floor = new Wall(*room2_floor_model);
	BoxCollider* ptr = new BoxCollider;
	floor->AddComponent(ptr);
	//	GET_SINGLE(CollisionManager)->AddCollider(ptr);
	room2.push_back(floor);

	Wall* front_wall_upper = new Wall(*room2_front_wall_upper_model);
	BoxCollider* ptr2 = new BoxCollider;
	front_wall_upper->AddComponent(ptr2);
	GET_SINGLE(CollisionManager)->AddCollider(ptr2);
	room2.push_back(front_wall_upper);

	Wall* front_wall_left = new Wall(*room2_front_wall_left_model);
	BoxCollider* ptr3 = new BoxCollider;
	front_wall_left->AddComponent(ptr3);
	GET_SINGLE(CollisionManager)->AddCollider(ptr3);
	room2.push_back(front_wall_left);


	Wall* front_wall_right = new Wall(*room2_front_wall_right_model);
	BoxCollider* ptr4 = new BoxCollider;
	front_wall_right->AddComponent(ptr4);
	GET_SINGLE(CollisionManager)->AddCollider(ptr4);
	room2.push_back(front_wall_right);

	////////////////////////////////////////////////////////////////////////////////////////////////////

	Wall* back_wall_upper = new Wall(*room2_back_wall_upper_model);
	BoxCollider* ptr5 = new BoxCollider;
	back_wall_upper->AddComponent(ptr5);
	GET_SINGLE(CollisionManager)->AddCollider(ptr5);
	room2.push_back(back_wall_upper);

	Wall* back_wall_left = new Wall(*room2_back_wall_left_model);
	BoxCollider* ptr6 = new BoxCollider;
	back_wall_left->AddComponent(ptr6);
	GET_SINGLE(CollisionManager)->AddCollider(ptr6);
	room2.push_back(back_wall_left);

	Wall* back_wall_right = new Wall(*room2_back_wall_right_model);
	BoxCollider* ptr7 = new BoxCollider;
	back_wall_right->AddComponent(ptr7);
	GET_SINGLE(CollisionManager)->AddCollider(ptr7);
	room2.push_back(back_wall_right);

	////////////////////////////////////////////////////////////////////////////////////////////////////

	Wall* left_wall = new Wall(*room2_left_wall_model);
	BoxCollider* ptr8 = new BoxCollider;
	left_wall->AddComponent(ptr8);
	GET_SINGLE(CollisionManager)->AddCollider(ptr8);
	room2.push_back(left_wall);

	Wall* right_wall = new Wall(*room2_right_wall_model);
	BoxCollider* ptr9 = new BoxCollider;
	right_wall->AddComponent(ptr9);
	GET_SINGLE(CollisionManager)->AddCollider(ptr9);
	room2.push_back(right_wall);

	////////////////////////////////////////////////////////////////////////////////////////////////////
	// 천장
	Wall* celing = new Wall(*room2_ceiling_model);
	BoxCollider* ptr10 = new BoxCollider;
	right_wall->AddComponent(ptr10);
	GET_SINGLE(CollisionManager)->AddCollider(ptr10);
	room2.push_back(celing);
}

void Stage1::MakeCorridor()
{
	Model* corridor_floor_model = new Model("res/models/corridor1/corridor_floor.obj");
	Model* corridor_ceiling_model = new Model("res/models/corridor1/corridor_ceiling.obj");
	Model* corridor_left_wall_model = new Model("res/models/corridor1/corridor_left.obj");
	Model* corridor_right_wall_model = new Model("res/models/corridor1/corridor_right.obj");


	Wall* floor = new Wall(*corridor_floor_model);
	BoxCollider* ptr = new BoxCollider;
	floor->AddComponent(ptr);
	//	GET_SINGLE(CollisionManager)->AddCollider(ptr);
	corridor1.push_back(floor);
	
	Wall* ceiling = new Wall(*corridor_ceiling_model);
	BoxCollider* ptr2 = new BoxCollider;
	ceiling->AddComponent(ptr2);
	GET_SINGLE(CollisionManager)->AddCollider(ptr2);
	corridor1.push_back(ceiling);


	Wall* left_wall = new Wall(*corridor_left_wall_model);
	BoxCollider* ptr3 = new BoxCollider;
	left_wall->AddComponent(ptr3);
	GET_SINGLE(CollisionManager)->AddCollider(ptr3);
	corridor1.push_back(left_wall);

	Wall* right_wall = new Wall(*corridor_right_wall_model);
	BoxCollider* ptr4 = new BoxCollider;
	right_wall->AddComponent(ptr4);
	GET_SINGLE(CollisionManager)->AddCollider(ptr4);
	corridor1.push_back(right_wall);




}

void Stage1::MakeRoom1()
{

	Model* floor_model = new Model("res/models/stage1/floor.obj");
	Model* ceiling_model = new Model("res/models/stage1/ceiling.obj");
	Model* front_wall_upper_model = new Model("res/models/stage1/front1.obj");
	Model* front_wall_left_model = new Model("res/models/stage1/front2.obj");
	Model* front_wall_right_model = new Model("res/models/stage1/front3.obj");
	Model* back_wall_model = new Model("res/models/stage1/back.obj");
	Model* left_wall_model = new Model("res/models/stage1/left.obj");
	Model* right_wall_model = new Model("res/models/stage1/right.obj");
	Model* door_model = new Model("res/models/simpledoor.obj");

	Wall* floor = new Wall(*floor_model);
	BoxCollider* ptr = new BoxCollider;
	floor->AddComponent(ptr);
	room1.push_back(floor);

	// 순서대로 앞, 뒤, 왼쪽, 오른쪽
	// 앞벽은 문 통과를 위해 3가지 파트로 나뉨
	Wall* front_wall_upper = new Wall(*front_wall_upper_model);
	BoxCollider* ptr2 = new BoxCollider;
	front_wall_upper->AddComponent(ptr2);
	GET_SINGLE(CollisionManager)->AddCollider(ptr2);
	room1.push_back(front_wall_upper);

	Wall* front_wall_left = new Wall(*front_wall_left_model);
	BoxCollider* ptr3 = new BoxCollider;
	front_wall_left->AddComponent(ptr3);
	GET_SINGLE(CollisionManager)->AddCollider(ptr3);
	room1.push_back(front_wall_left);

	Wall* front_wall_right = new Wall(*front_wall_right_model);
	BoxCollider* ptr4 = new BoxCollider;
	front_wall_right->AddComponent(ptr4);
	GET_SINGLE(CollisionManager)->AddCollider(ptr4);
	room1.push_back(front_wall_right);

	Wall* back_wall = new Wall(*back_wall_model);
	BoxCollider* ptr5 = new BoxCollider;
	back_wall->AddComponent(ptr5);
	GET_SINGLE(CollisionManager)->AddCollider(ptr5);
	room1.push_back(back_wall);



	Wall* left_wall = new Wall(*left_wall_model);
	BoxCollider* ptr6 = new BoxCollider;
	left_wall->AddComponent(ptr6);
	GET_SINGLE(CollisionManager)->AddCollider(ptr6);
	room1.push_back(left_wall);

	Wall* right_wall = new Wall(*right_wall_model);
	BoxCollider* ptr7 = new BoxCollider;
	right_wall->AddComponent(ptr7);
	GET_SINGLE(CollisionManager)->AddCollider(ptr7);
	room1.push_back(right_wall);

	Wall* celing = new Wall(*ceiling_model);
	BoxCollider* ptr8 = new BoxCollider;
	right_wall->AddComponent(ptr8);
	GET_SINGLE(CollisionManager)->AddCollider(ptr8);
	room1.push_back(celing);

}

void Stage1::ObjectInit()
{
	fake_flash->Init();

}
