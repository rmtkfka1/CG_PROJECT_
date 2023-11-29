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
	player_model = new Model("res/models/stage1/player.obj");
	flash_model = new Model("res/models/stage1/flash.obj");
	b_plane = new Model("res/models/billboard_plane/billboard_plane.obj");
	flash_fake = new Model("res/models/flash.obj");

	///오브젝트 생성////////////////////////////////////////////////////////////////////////////
	{
		player = new Player(*flash_model);
		BoxCollider* ptr = new BoxCollider;
		player->AddComponent(ptr);
		GET_SINGLE(CollisionManager)->AddCollider(ptr);
	}

	{
		flash = new Flash(*flash_model);
	}

	{
		billboard = new Billboard(*b_plane);
		BoxCollider* ptr = new BoxCollider;
		billboard->AddComponent(ptr);
		billboard->SetSize(5.0f, 5.0f);
	}

	
	MakeRoom();


	/////////텍스처 만들기/////////////////////////////////////////////////////////////
	texture = new Texture("res/textures/block.jpg");
	billboard_texture = new Texture("res/textures/billboard_test.png");
	light_texture = new Texture("res/textures/light.jpg");
	table_texture = new Texture("res/textures/table.png");
	flash_fake_texture = new Texture("res/textures/flash_fake.jpg");

	texture->Bind(0);
	flash_fake_texture->Bind(1);
	billboard_texture->Bind(2);
	light_texture->Bind(3);
	table_texture->Bind(4);

	////////////////////////조명작업///////////////////////////////////////////////////
	light = new Light2();
	light->UseSpotLight(*shader);



	///////////////////////////////////////////////////////////////////////////////////



}


void Stage1::Update()
{

	CameraManager::GetInstance()->KeyUpdate();
	CameraManager::GetInstance()->MouseUpdate(MouseManager::GetInstance()->GetMousePos().x, MouseManager::GetInstance()->GetMousePos().y);

	player->Update();
	flash->MatrixUpdate(player);

	for (auto& ele : v_wall)
	{
		ele->Update();
	}


	GET_SINGLE(CollisionManager)->Update();


	shader->SetUniform3f("u_viewpos", CameraManager::GetInstance()->m_cameraPos.x, CameraManager::GetInstance()->m_cameraPos.y, CameraManager::GetInstance()->m_cameraPos.z);
	shader->SetUniformMat4f("u_view", CameraManager::GetInstance()->GetMatrix());

	light->Spot_light.position = CameraManager::GetInstance()->m_cameraPos;
	light->Spot_light.direction = CameraManager::GetInstance()->m_cameraFront;
	light->UseSpotLight(*shader);

	billboard->Update();

}

void Stage1::Render()
{

	Object_Render();
	

	Texture_Render();

	cout << CameraManager::GetInstance()->m_cameraPos.x << " " << -CameraManager::GetInstance()->m_cameraPos.z << " " << CameraManager::GetInstance()->m_cameraPos.y << endl;

}

void Stage1::Object_Render()
{


	glViewport(0, 0, screenWidth, screenHeight);

	shader->SetUniform1i("u_texture", 0);

	player->Render(*shader, *player_model, matrix::GetInstance()->GetTranslation(player->GetCenter_x(), player->GetCenter_y(), player->GetCenter_z()));

	//light->UseSpotLight(*spot_shader);

	for (int i = 0; i < room1.size(); i++)
	{
		room1[i].first->Render(*shader, *room1[i].second, matrix::GetInstance()->GetSimple());
	}

	for (int i = 0; i < corridor1.size(); i++)
	{
		corridor1[i].first->Render(*shader, *corridor1[i].second, matrix::GetInstance()->GetSimple());
	}

	for (int i = 0; i < room2.size(); i++)
	{
		room2[i].first->Render(*shader, *room2[i].second, matrix::GetInstance()->GetSimple());
	}

	for (int i = 0; i < corridor2.size(); i++)
	{
		corridor2[i].first->Render(*shader, *corridor2[i].second, matrix::GetInstance()->GetSimple());
	}

	for (int i = 0; i < room3.size(); i++)
	{
		room3[i].first->Render(*shader, *room3[i].second, matrix::GetInstance()->GetSimple());
	}

	shader->SetUniform1i("u_texture", flash_fake_texture->GetSlot());

	flash->Render(*shader, *flash_model, glm::mat4(1.0f));

	shader->SetUniform1i("u_texture", 2);
	billboard->Render(*shader, *b_plane, GET_SINGLE(matrix)->GetSimple());


	shader->SetUniformMat4f("u_model", glm::mat4(1.0f));


	//{
	//	//테이블 그리기
	//	shader->SetUniform1i("u_texture", table_texture->GetSlot());
	//	table->RenderModel(*shader);
	//}


	{
		shader->SetUniform1i("u_texture", flash_fake_texture->GetSlot());
		flash_fake->RenderModel(*shader);
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

	MakeCorridor2();

	MakeRoom3();
}

void Stage1::MakeRoom3()
{
	Model* room3_floor_model = new Model("res/models/stage3/floor.obj");
	Model* room3_front_wall_upper_model = new Model("res/models/stage3/front_wall_upper.obj");
	Model* room3_front_wall_left_model = new Model("res/models/stage3/front_wall_left.obj");
	Model* room3_front_wall_right_model = new Model("res/models/stage3/front_wall_right.obj");
	Model* room3_back_wall_upper_model = new Model("res/models/stage3/back_wall_upper.obj");
	Model* room3_back_wall_left_model = new Model("res/models/stage3/back_wall_left.obj");
	Model* room3_back_wall_right_model = new Model("res/models/stage3/back_wall_right.obj");
	Model* room3_left_wall_model = new Model("res/models/stage3/left_wall.obj");
	Model* room3_right_wall_model = new Model("res/models/stage3/right_wall.obj");
	Model* room3_ceiling_model = new Model("res/models/stage3/ceiling.obj");

	// 바닥
	Wall* floor = new Wall(*room3_floor_model);
	BoxCollider* ptr = new BoxCollider;
	floor->AddComponent(ptr);
	//	GET_SINGLE(CollisionManager)->AddCollider(ptr);
	v_wall.push_back(floor);
	room3.push_back(pair<Object*, Model*>(floor, room3_floor_model));

	////////////////////////////////////////////////////////////////////////////////////////////////////

	Wall* front_wall_upper = new Wall(*room3_front_wall_upper_model);
	BoxCollider* ptr2 = new BoxCollider;
	front_wall_upper->AddComponent(ptr2);
	GET_SINGLE(CollisionManager)->AddCollider(ptr2);
	v_wall.push_back(front_wall_upper);
	room3.push_back(pair<Object*, Model*>(front_wall_upper, room3_front_wall_upper_model));

	Wall* front_wall_left = new Wall(*room3_front_wall_left_model);
	BoxCollider* ptr3 = new BoxCollider;
	front_wall_left->AddComponent(ptr3);
	GET_SINGLE(CollisionManager)->AddCollider(ptr3);
	v_wall.push_back(front_wall_left);
	room3.push_back(pair<Object*, Model*>(front_wall_left, room3_front_wall_left_model));

	Wall* front_wall_right = new Wall(*room3_front_wall_right_model);
	BoxCollider* ptr4 = new BoxCollider;
	front_wall_right->AddComponent(ptr4);
	GET_SINGLE(CollisionManager)->AddCollider(ptr4);
	v_wall.push_back(front_wall_right);
	room3.push_back(pair<Object*, Model*>(front_wall_right, room3_front_wall_right_model));

	////////////////////////////////////////////////////////////////////////////////////////////////////

	Wall* back_wall_upper = new Wall(*room3_back_wall_upper_model);
	BoxCollider* ptr5 = new BoxCollider;
	back_wall_upper->AddComponent(ptr5);
	GET_SINGLE(CollisionManager)->AddCollider(ptr5);
	v_wall.push_back(back_wall_upper);
	room3.push_back(pair<Object*, Model*>(back_wall_upper, room3_back_wall_upper_model));

	Wall* back_wall_left = new Wall(*room3_back_wall_left_model);
	BoxCollider* ptr6 = new BoxCollider;
	back_wall_left->AddComponent(ptr6);
	GET_SINGLE(CollisionManager)->AddCollider(ptr6);
	v_wall.push_back(back_wall_left);
	room3.push_back(pair<Object*, Model*>(back_wall_left, room3_back_wall_left_model));

	Wall* back_wall_right = new Wall(*room3_back_wall_right_model);
	BoxCollider* ptr7 = new BoxCollider;
	back_wall_right->AddComponent(ptr7);
	GET_SINGLE(CollisionManager)->AddCollider(ptr7);
	v_wall.push_back(back_wall_right);
	room3.push_back(pair<Object*, Model*>(back_wall_right, room3_back_wall_right_model));

	////////////////////////////////////////////////////////////////////////////////////////////////////

	Wall* left_wall = new Wall(*room3_left_wall_model);
	BoxCollider* ptr8 = new BoxCollider;
	left_wall->AddComponent(ptr8);
	GET_SINGLE(CollisionManager)->AddCollider(ptr8);
	v_wall.push_back(left_wall);
	room3.push_back(pair<Object*, Model*>(left_wall, room3_left_wall_model));

	Wall* right_wall = new Wall(*room3_right_wall_model);
	BoxCollider* ptr9 = new BoxCollider;
	right_wall->AddComponent(ptr9);
	GET_SINGLE(CollisionManager)->AddCollider(ptr9);
	v_wall.push_back(right_wall);
	room3.push_back(pair<Object*, Model*>(right_wall, room3_right_wall_model));

	Wall* ceiling = new Wall(*room3_ceiling_model);
	BoxCollider* ptr10 = new BoxCollider;
	right_wall->AddComponent(ptr10);
	GET_SINGLE(CollisionManager)->AddCollider(ptr10);
	v_wall.push_back(ceiling);
	room3.push_back(pair<Object*, Model*>(right_wall, room3_ceiling_model));
}

void Stage1::MakeCorridor2()
{

	Model* corridor2_floor_model1 = new Model("res/models/corridor2/corridor_floor_1.obj");
	Model* corridor2_floor_model2 = new Model("res/models/corridor2/corridor_floor_2.obj");
	Model* corridor2_left_wall_model1 = new Model("res/models/corridor2/corridor_left_1.obj");
	Model* corridor2_left_wall_model2 = new Model("res/models/corridor2/corridor_left_2.obj");
	Model* corridor2_right_wall_model1 = new Model("res/models/corridor2/corridor_right_1.obj");
	Model* corridor2_right_wall_model2 = new Model("res/models/corridor2/corridor_right_2.obj");


	Wall* floor1 = new Wall(*corridor2_floor_model1);
	BoxCollider* ptr = new BoxCollider;
	floor1->AddComponent(ptr);
	//	GET_SINGLE(CollisionManager)->AddCollider(ptr);
	v_wall.push_back(floor1);
	corridor2.push_back(pair<Object*, Model*>(floor1, corridor2_floor_model1));

	Wall* floor2 = new Wall(*corridor2_floor_model2);
	BoxCollider* ptr2 = new BoxCollider;
	floor2->AddComponent(ptr2);
	//	GET_SINGLE(CollisionManager)->AddCollider(ptr);
	v_wall.push_back(floor2);
	corridor2.push_back(pair<Object*, Model*>(floor2, corridor2_floor_model2));

	////////////////////////////////////////////////////////////////////////////////////////////////////

	Wall* left_wall1 = new Wall(*corridor2_left_wall_model1);
	BoxCollider* ptr3 = new BoxCollider;
	left_wall1->AddComponent(ptr3);
	GET_SINGLE(CollisionManager)->AddCollider(ptr3);
	v_wall.push_back(left_wall1);
	corridor2.push_back(pair<Object*, Model*>(left_wall1, corridor2_left_wall_model1));

	Wall* left_wall2 = new Wall(*corridor2_left_wall_model2);
	BoxCollider* ptr4 = new BoxCollider;
	left_wall2->AddComponent(ptr4);
	GET_SINGLE(CollisionManager)->AddCollider(ptr4);
	v_wall.push_back(left_wall2);
	corridor2.push_back(pair<Object*, Model*>(left_wall2, corridor2_left_wall_model2));

	////////////////////////////////////////////////////////////////////////////////////////////////////

	Wall* right_wall1 = new Wall(*corridor2_right_wall_model1);
	BoxCollider* ptr5 = new BoxCollider;
	right_wall1->AddComponent(ptr5);
	GET_SINGLE(CollisionManager)->AddCollider(ptr5);
	v_wall.push_back(right_wall1);
	corridor2.push_back(pair<Object*, Model*>(right_wall1, corridor2_right_wall_model1));

	Wall* right_wall2 = new Wall(*corridor2_right_wall_model2);
	BoxCollider* ptr6 = new BoxCollider;
	right_wall2->AddComponent(ptr6);
	GET_SINGLE(CollisionManager)->AddCollider(ptr6);
	v_wall.push_back(right_wall2);
	corridor2.push_back(pair<Object*, Model*>(right_wall2, corridor2_right_wall_model2));
}

void Stage1::MakeRoom2()
{

	Model* room2_floor_model = new Model("res/models/stage2/floor.obj");
	Model* room2_ceiling_model = new Model("res/models/stage2/ceiling.obj");
	Model* room2_front_wall_upper_model = new Model("res/models/stage2/front_wall_upper.obj");
	Model* room2_front_wall_left_model = new Model("res/models/stage2/front_wall_left.obj");
	Model* room2_front_wall_right_model = new Model("res/models/stage2/front_wall_right.obj");
	Model* room2_back_wall_upper_model = new Model("res/models/stage2/back_wall_upper.obj");
	Model* room2_back_wall_left_model = new Model("res/models/stage2/back_wall_left.obj");
	Model* room2_back_wall_right_model = new Model("res/models/stage2/back_wall_right.obj");
	Model* room2_left_wall_model = new Model("res/models/stage2/left_wall.obj");
	Model* room2_right_wall_model = new Model("res/models/stage2/right_wall.obj");


	// 바닥
	Wall* floor = new Wall(*room2_floor_model);
	BoxCollider* ptr = new BoxCollider;
	floor->AddComponent(ptr);
	//	GET_SINGLE(CollisionManager)->AddCollider(ptr);
	v_wall.push_back(floor);
	room2.push_back(pair<Object*, Model*>(floor, room2_floor_model));


	Wall* front_wall_upper = new Wall(*room2_front_wall_upper_model);
	BoxCollider* ptr2 = new BoxCollider;
	front_wall_upper->AddComponent(ptr2);
	GET_SINGLE(CollisionManager)->AddCollider(ptr2);
	v_wall.push_back(front_wall_upper);
	room2.push_back(pair<Object*, Model*>(front_wall_upper, room2_front_wall_upper_model));

	Wall* front_wall_left = new Wall(*room2_front_wall_left_model);
	BoxCollider* ptr3 = new BoxCollider;
	front_wall_left->AddComponent(ptr3);
	GET_SINGLE(CollisionManager)->AddCollider(ptr3);
	v_wall.push_back(front_wall_left);
	room2.push_back(pair<Object*, Model*>(front_wall_left, room2_front_wall_left_model));

	Wall* front_wall_right = new Wall(*room2_front_wall_right_model);
	BoxCollider* ptr4 = new BoxCollider;
	front_wall_right->AddComponent(ptr4);
	GET_SINGLE(CollisionManager)->AddCollider(ptr4);
	v_wall.push_back(front_wall_right);
	room2.push_back(pair<Object*, Model*>(front_wall_right, room2_front_wall_right_model));

	////////////////////////////////////////////////////////////////////////////////////////////////////

	Wall* back_wall_upper = new Wall(*room2_back_wall_upper_model);
	BoxCollider* ptr5 = new BoxCollider;
	back_wall_upper->AddComponent(ptr5);
	GET_SINGLE(CollisionManager)->AddCollider(ptr5);
	v_wall.push_back(back_wall_upper);
	room2.push_back(pair<Object*, Model*>(back_wall_upper, room2_back_wall_upper_model));

	Wall* back_wall_left = new Wall(*room2_back_wall_left_model);
	BoxCollider* ptr6 = new BoxCollider;
	back_wall_left->AddComponent(ptr6);
	GET_SINGLE(CollisionManager)->AddCollider(ptr6);
	v_wall.push_back(back_wall_left);
	room2.push_back(pair<Object*, Model*>(back_wall_left, room2_back_wall_left_model));

	Wall* back_wall_right = new Wall(*room2_back_wall_right_model);
	BoxCollider* ptr7 = new BoxCollider;
	back_wall_right->AddComponent(ptr7);
	GET_SINGLE(CollisionManager)->AddCollider(ptr7);
	v_wall.push_back(back_wall_right);
	room2.push_back(pair<Object*, Model*>(back_wall_right, room2_back_wall_right_model));

	////////////////////////////////////////////////////////////////////////////////////////////////////

	Wall* left_wall = new Wall(*room2_left_wall_model);
	BoxCollider* ptr8 = new BoxCollider;
	left_wall->AddComponent(ptr8);
	GET_SINGLE(CollisionManager)->AddCollider(ptr8);
	v_wall.push_back(left_wall);
	room2.push_back(pair<Object*, Model*>(left_wall, room2_left_wall_model));

	Wall* right_wall = new Wall(*room2_right_wall_model);
	BoxCollider* ptr9 = new BoxCollider;
	right_wall->AddComponent(ptr9);
	GET_SINGLE(CollisionManager)->AddCollider(ptr9);
	v_wall.push_back(right_wall);
	room2.push_back(pair<Object*, Model*>(right_wall, room2_right_wall_model));

	////////////////////////////////////////////////////////////////////////////////////////////////////
	// 천장
	Wall* celing = new Wall(*room2_ceiling_model);
	BoxCollider* ptr10 = new BoxCollider;
	right_wall->AddComponent(ptr10);
	GET_SINGLE(CollisionManager)->AddCollider(ptr10);
	v_wall.push_back(celing);
	room1.push_back(pair<Object*, Model*>(right_wall, room2_ceiling_model));
}

void Stage1::MakeCorridor()
{
	Model* corridor_floor_model = new Model("res/models/corridor1/corridor_floor.obj");
	Model* corridor_left_wall_model = new Model("res/models/corridor1/corridor_left.obj");
	Model* corridor_right_wall_model = new Model("res/models/corridor1/corridor_right.obj");
	Model* table_model = new Model("res/models/test.obj");

	Wall* floor = new Wall(*corridor_floor_model);
	BoxCollider* ptr = new BoxCollider;
	floor->AddComponent(ptr);
	//	GET_SINGLE(CollisionManager)->AddCollider(ptr);
	v_wall.push_back(floor);
	corridor1.push_back(pair<Object*, Model*>(floor, corridor_floor_model));


	Wall* left_wall = new Wall(*corridor_left_wall_model);
	BoxCollider* ptr2 = new BoxCollider;
	left_wall->AddComponent(ptr2);
	GET_SINGLE(CollisionManager)->AddCollider(ptr2);
	v_wall.push_back(left_wall);
	corridor1.push_back(pair<Object*, Model*>(left_wall, corridor_left_wall_model));

	Wall* right_wall = new Wall(*corridor_right_wall_model);
	BoxCollider* ptr3 = new BoxCollider;
	right_wall->AddComponent(ptr3);
	GET_SINGLE(CollisionManager)->AddCollider(ptr3);
	v_wall.push_back(right_wall);
	corridor1.push_back(pair<Object*, Model*>(right_wall, corridor_right_wall_model));

	Wall* table = new Wall(*table_model);
	BoxCollider* ptr4 = new BoxCollider;
	table->AddComponent(ptr4);
	GET_SINGLE(CollisionManager)->AddCollider(ptr4);
	v_wall.push_back(table);
	corridor1.push_back(pair<Object*, Model*>(right_wall, table_model));


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


	Wall* floor = new Wall(*floor_model);
	BoxCollider* ptr = new BoxCollider;
	floor->AddComponent(ptr);
	//	GET_SINGLE(CollisionManager)->AddCollider(ptr);
	v_wall.push_back(floor);
	room1.push_back(pair<Object*, Model*>(floor, floor_model));

	// 순서대로 앞, 뒤, 왼쪽, 오른쪽
	// 앞벽은 문 통과를 위해 3가지 파트로 나뉨
	Wall* front_wall_upper = new Wall(*front_wall_upper_model);
	BoxCollider* ptr2 = new BoxCollider;
	front_wall_upper->AddComponent(ptr2);
	GET_SINGLE(CollisionManager)->AddCollider(ptr2);
	v_wall.push_back(front_wall_upper);
	room1.push_back(pair<Object*, Model*>(front_wall_upper, front_wall_upper_model));

	Wall* front_wall_left = new Wall(*front_wall_left_model);
	BoxCollider* ptr3 = new BoxCollider;
	front_wall_left->AddComponent(ptr3);
	GET_SINGLE(CollisionManager)->AddCollider(ptr3);
	v_wall.push_back(front_wall_left);
	room1.push_back(pair<Object*, Model*>(front_wall_left, front_wall_left_model));

	Wall* front_wall_right = new Wall(*front_wall_right_model);
	BoxCollider* ptr4 = new BoxCollider;
	front_wall_right->AddComponent(ptr4);
	GET_SINGLE(CollisionManager)->AddCollider(ptr4);
	v_wall.push_back(front_wall_right);
	room1.push_back(pair<Object*, Model*>(front_wall_right, front_wall_right_model));

	Wall* back_wall = new Wall(*back_wall_model);
	BoxCollider* ptr5 = new BoxCollider;
	back_wall->AddComponent(ptr5);
	GET_SINGLE(CollisionManager)->AddCollider(ptr5);
	v_wall.push_back(back_wall);
	room1.push_back(pair<Object*, Model*>(back_wall, back_wall_model));

	Wall* left_wall = new Wall(*left_wall_model);
	BoxCollider* ptr6 = new BoxCollider;
	left_wall->AddComponent(ptr6);
	GET_SINGLE(CollisionManager)->AddCollider(ptr6);
	v_wall.push_back(left_wall);
	room1.push_back(pair<Object*, Model*>(left_wall, left_wall_model));

	Wall* right_wall = new Wall(*right_wall_model);
	BoxCollider* ptr7 = new BoxCollider;
	right_wall->AddComponent(ptr7);
	GET_SINGLE(CollisionManager)->AddCollider(ptr7);
	v_wall.push_back(right_wall);
	room1.push_back(pair<Object*, Model*>(right_wall, right_wall_model));

	Wall* celing = new Wall(*ceiling_model);
	BoxCollider* ptr8 = new BoxCollider;
	right_wall->AddComponent(ptr8);
	GET_SINGLE(CollisionManager)->AddCollider(ptr8);
	v_wall.push_back(celing);
	room1.push_back(pair<Object*, Model*>(right_wall, ceiling_model));


}
