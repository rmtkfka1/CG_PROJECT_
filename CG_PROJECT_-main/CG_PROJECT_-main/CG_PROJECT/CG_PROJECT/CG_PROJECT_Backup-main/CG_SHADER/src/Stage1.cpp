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
#include "RightDoor.h"
#include "TextManager.h"
#include "DeadBody.h"
#include "MaskEvent.h"
#include "Mask.h"
#include "ExitDoor.h"
#include "Locked.h"

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




	///////////////////////////////////////////////////모델 불러오기 





	{

		Model* model = new Model("res/models/exitdoor.obj");
		exitdoor = new ExitDoor(*model);
		BoxCollider* ptr = new BoxCollider;
		exitdoor->AddComponent(ptr);
		GET_SINGLE(CollisionManager)->AddCollider(ptr);

		exitdoor2 = new Model("res/models/exitdoor2.obj");

	}


	{
		//고스트 생성
		Model* ghost_body = new Model("res/models/ghost/ghost_body.obj");
		Model* ghost_left_arm = new Model("res/models/ghost/ghost_left_arm.obj");
		Model* ghost_right_arm = new Model("res/models/ghost/ghost_right_arm.obj");

		ghost = new Ghost(*ghost_body, *ghost_left_arm, *ghost_right_arm);
		ghost->Init();
		ghost->SetPosition(0.0f, -800.0f);

		ghost_body->PrintInfo();
	

	}

	{
		//탁자생성
		Model* table_model = new Model("res/models/table.obj");
		table = new Wall(*table_model);
		BoxCollider* ptr = new BoxCollider;
		table->AddComponent(ptr);
		GET_SINGLE(CollisionManager)->AddCollider(ptr);

	}
	{

		Model* table_model = new Model("res/models/lockedtable.obj");
		Lockedtable = new Wall(*table_model);
		BoxCollider* ptr = new BoxCollider;
		Lockedtable->AddComponent(ptr);
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
		Model* door_left = new Model("res/models/corridor1/door_left.obj");
		Corridor_left_door = new LeftDoor(*door_left);
		BoxCollider* ptr = new BoxCollider;
		Corridor_left_door->AddComponent(ptr);
		GET_SINGLE(CollisionManager)->AddCollider(ptr);
	}

	{
		Model* door_right = new Model("res/models/corridor1/door_right.obj");
		Corridor_right_door = new RightDoor(*door_right);
		BoxCollider* ptr = new BoxCollider;
		Corridor_right_door->AddComponent(ptr);
		GET_SINGLE(CollisionManager)->AddCollider(ptr);
	}

	//시체
	{
		Model *dead_body = new Model("res/models/deadbody.obj");
		deadbody = new DeadBody(*dead_body);
		BoxCollider* ptr = new BoxCollider;
		deadbody->AddComponent(ptr);
		GET_SINGLE(CollisionManager)->AddCollider(ptr);
	}


	//마스크
	{
		
		Model* mask_model = new Model("res/models/mask.obj");
		mask = new Mask(*mask_model);
		BoxCollider* ptr = new BoxCollider;
		mask->AddComponent(ptr);
		GET_SINGLE(CollisionManager)->AddCollider(ptr);
	}

	//마스크이벤트발생
	{
		Model* mask__event = new Model("res/models/deadbody_event.obj");
		mask_event = new Event(*mask__event);
		BoxCollider* ptr = new BoxCollider;
		mask_event->AddComponent(ptr);
		GET_SINGLE(CollisionManager)->AddCollider(ptr);
	}


	//방1 퀴즈 생성
	{
		//퀴즈박스1
		Model* box = new Model("res/models/room2_event/box.obj");
		quizbox = new Wall(*box);
		BoxCollider* ptr = new BoxCollider;
		quizbox->AddComponent(ptr);
		GET_SINGLE(CollisionManager)->AddCollider(ptr);
	}

	{
		Model* lockedbox = new Model("res/models/lockedbox.obj");
		Lockedbox = new Wall(*lockedbox);
		BoxCollider* ptr = new BoxCollider;
		Lockedbox->AddComponent(ptr);
		GET_SINGLE(CollisionManager)->AddCollider(ptr);
	}

	{
		Model* locked_key = new Model("res/models/lockedkey.obj");
		Lockedkey = new Locked(*locked_key);
		BoxCollider* ptr = new BoxCollider;
		Lockedkey->AddComponent(ptr);
		GET_SINGLE(CollisionManager)->AddCollider(ptr);


	}
	{
		Model* temp = new Model("res/models/room2_event/fake_box.obj");
		quizbox_event = new Event(*temp);
		BoxCollider* ptr = new BoxCollider;
		quizbox_event->AddComponent(ptr);
		GET_SINGLE(CollisionManager)->AddCollider(ptr);

	}
	{

		//정답 
		shader->SetUniformMat4f("u_model", glm::mat4(1.0f));
		answerbox = new Model("res/models/room2_event/answer_box.obj");
		

	}

/////////////	
	MakeRoom();


	/////////텍스처 만들기/////////////////////////////////////////////////////////////
	texture = new Texture("res/textures/block.jpg");
	billboard_texture = new Texture("res/textures/billboard_test.png");
	light_texture = new Texture("res/textures/light.jpg");
	table_texture = new Texture("res/textures/table.png");
	flash_fake_texture = new Texture("res/textures/door.jpg");
	ghost_texture = new Texture("res/textures/SM_text.png");
	deadbody_texture = new Texture("res/textures/deadbody.jpg");
	mask_texture = new Texture("res/textures/mask.jpg");
	exitdoor_texture = new Texture("res/textures/exitdoor.png");
	quizbox_texture = new Texture("res/textures/1.jpg");
	lockedbox_texture = new Texture("res/textures/lockedbox.jpeg");
	answer1_texture = new Texture("res/textures/answer1.png");


	texture->Bind(0);
	flash_fake_texture->Bind(1);
	billboard_texture->Bind(2);
	light_texture->Bind(3);
	table_texture->Bind(4);
	ghost_texture->Bind(5);
	deadbody_texture->Bind(6);
	mask_texture->Bind(7);
	exitdoor_texture->Bind(8);
	quizbox_texture->Bind(9);
	lockedbox_texture->Bind(10);
	answer1_texture->Bind(11);
	////////////////////////조명작업///////////////////////////////////////////////////
	light = new Light2();



	///////////////////////////////////////////////////////////////////////////////////
	ObjectInit();





}


void Stage1::Update()
{


	

	CameraManager::GetInstance()->KeyUpdate();
	CameraManager::GetInstance()->MouseUpdate(MouseManager::GetInstance()->GetMousePos().x, MouseManager::GetInstance()->GetMousePos().y);

	player->Update();
	GET_SINGLE(CollisionManager)->Update();

	fake_flash->Update();
	fake_flash->UpdateFlash(light, flash);
	quizbox_event->Update();

	Corridor_left_door->Update();
	Corridor_right_door->Update();

	table->Update();
	Lockedtable->Update();
	Lockedkey->Update();



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

	exitdoor->Update();
	quizbox->Update();

	flash->MatrixUpdate(player);

	light->Spot_light.position = CameraManager::GetInstance()->m_cameraPos;
	light->Spot_light.direction = CameraManager::GetInstance()->m_cameraFront;
	light->UseSpotLight(*shader,*ghost);


	ghost->UpdatePlayerLocation(player->GetCenter());
	ghost->Update();
	billboard->Update();
	mask_event->Update();
	mask->MatrixUpdate(mask_event);
	mask->Update();
	deadbody->Update();
	

	cout << CameraManager::GetInstance()->m_cameraPos.x << "  " << CameraManager::GetInstance()->m_cameraPos.y << "  " << CameraManager::GetInstance()->m_cameraPos.z << endl;
	
}

void Stage1::Render()
{



	shader->Bind();
	Object_Render();


	shader->Unbind();
	Texture_Render();


	

}

void Stage1::Object_Render()
{

	light->UseSpotLight(*shader, *ghost);


	shader->SetUniform1i("u_texture", 0);
	player->Render(*shader);


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
		Lockedtable->Render(*shader);
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
		Corridor_right_door->Render(*shader);
	}

	{
		shader->SetUniformMat4f("u_model", glm::mat4(1.0f));
		shader->SetUniform1i("u_texture", deadbody_texture->GetSlot());
		deadbody->SpecialRender(*shader, fake_flash);
	}


	{
		shader->SetUniformMat4f("u_model", glm::mat4(1.0f));
		shader->SetUniform1i("u_texture", mask_texture->GetSlot());
		mask->Render(*shader);
	}

	{
		shader->SetUniform1i("u_texture", exitdoor_texture->GetSlot());
		exitdoor->Render(*shader);
		shader->SetUniformMat4f("u_model", glm::mat4(1.0f));
		exitdoor2->RenderModel(*shader);
	}

	{
		shader->SetUniform1i("u_texture", quizbox_texture->GetSlot());
		quizbox->Render(*shader);
	}

	{

		shader->SetUniform1i("u_texture", lockedbox_texture->GetSlot());
		Lockedbox->Render(*shader);
		Lockedkey->Render(*shader);

	}

	{
		shader->SetUniform1i("u_texture", answer1_texture->GetSlot());
		shader->SetUniformMat4f("u_model", glm::mat4(1.0f));
		answerbox->RenderModel(*shader);
	}




	shader->SetUniformMat4f("u_proj", matrix::GetInstance()->GetProjection());
	shader->SetUniform3f("u_viewpos", CameraManager::GetInstance()->m_cameraPos.x, CameraManager::GetInstance()->m_cameraPos.y, CameraManager::GetInstance()->m_cameraPos.z);
	shader->SetUniformMat4f("u_view", CameraManager::GetInstance()->GetMatrix());

}


void Stage1::Texture_Render()
{

	if (fake_flash->GetCollsionState() == true)
	{
		TextManager::GetInstance()->Render(-0.2f, -0.5f, "Press F to Equid");
		TextManager::GetInstance()->Render(-0.2f, -0.6f, "Press R to Turnon / Turnoff");
	}

	if (exitdoor->LockedAndCollusion() == true)
	{
		TextManager::GetInstance()->Render(-0.4f, 0.0f, "THIS DOOR IS LOCKED");
		TextManager::GetInstance()->Render(-0.4f, -0.1f, "TO OPEN THE DOOR NEDD A PASSWORD");
	}

	if (quizbox_event->room2_box_collison == true)
	{
		TextManager::GetInstance()->Render(0.0f, 0.0f, " RGBA !?");
	}


	if (Lockedkey->_collusion == true)
	{


		TextManager::GetInstance()->Render(-0.1f, 0.1f,"Press 1,2,3,4");


		string strValue = std::to_string(Lockedkey->num2[0]);
		strValue += std::to_string(Lockedkey->num2[1]);
		strValue += std::to_string(Lockedkey->num2[2]);
		strValue += std::to_string(Lockedkey->num2[3]);

		TextManager::GetInstance()->Render(0.0f,0.0f, strValue.c_str());
	}


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
	Model* model_front1 = new Model("res/models/room4/front1.obj");
	Model* model_front2 = new Model("res/models/room4/front2.obj");
	Model* model_front3 = new Model("res/models/room4/front3.obj");
	Model* model_back1 = new Model("res/models/room4/back1.obj");
	Model* model_back2 = new Model("res/models/room4/back2.obj");
	Model* model_back3 = new Model("res/models/room4/back3.obj");
	Model* model_left = new Model("res/models/room4/left.obj");
	Model* model_right = new Model("res/models/room4/right.obj");

	{
		Wall* front = new Wall(*model_front1);
		BoxCollider* ptr = new BoxCollider;
		front->AddComponent(ptr);
		GET_SINGLE(CollisionManager)->AddCollider(ptr);
		room6.push_back(front);
	}
	
	{
		Wall* front = new Wall(*model_front2);
		BoxCollider* ptr = new BoxCollider;
		front->AddComponent(ptr);
		GET_SINGLE(CollisionManager)->AddCollider(ptr);
		room6.push_back(front);
	}
	
	{
		Wall* front = new Wall(*model_front3);
		BoxCollider* ptr = new BoxCollider;
		front->AddComponent(ptr);
		GET_SINGLE(CollisionManager)->AddCollider(ptr);
		room6.push_back(front);
	}

	{
		Wall* back = new Wall(*model_back1);
		BoxCollider* ptr = new BoxCollider;
		back->AddComponent(ptr);
		GET_SINGLE(CollisionManager)->AddCollider(ptr);
		room6.push_back(back);
	}
	
	{
		Wall* back = new Wall(*model_back2);
		BoxCollider* ptr = new BoxCollider;
		back->AddComponent(ptr);
		GET_SINGLE(CollisionManager)->AddCollider(ptr);
		room6.push_back(back);
	}
	
	{
		Wall* back = new Wall(*model_back3);
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
	Model* model_left1 = new Model("res/models/room3/left1.obj");
	Model* model_left2 = new Model("res/models/room3/left2.obj");
	Model* model_left3 = new Model("res/models/room3/left3.obj");
	Model* model_right1 = new Model("res/models/room3/right1.obj");
	Model* model_right2 = new Model("res/models/room3/right2.obj");
	Model* model_right3 = new Model("res/models/room3/right3.obj");

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
		Wall* left = new Wall(*model_left1);
		BoxCollider* ptr = new BoxCollider;
		left->AddComponent(ptr);
		GET_SINGLE(CollisionManager)->AddCollider(ptr);
		room5.push_back(left);
	}
	
	{
		Wall* left = new Wall(*model_left2);
		BoxCollider* ptr = new BoxCollider;
		left->AddComponent(ptr);
		GET_SINGLE(CollisionManager)->AddCollider(ptr);
		room5.push_back(left);
	}
	
	{
		Wall* left = new Wall(*model_left3);
		BoxCollider* ptr = new BoxCollider;
		left->AddComponent(ptr);
		GET_SINGLE(CollisionManager)->AddCollider(ptr);
		room5.push_back(left);
	}

	{
		Wall* right = new Wall(*model_right1);
		BoxCollider* ptr = new BoxCollider;
		right->AddComponent(ptr);
		GET_SINGLE(CollisionManager)->AddCollider(ptr);
		room5.push_back(right);
	}
	
	{
		Wall* right = new Wall(*model_right2);
		BoxCollider* ptr = new BoxCollider;
		right->AddComponent(ptr);
		GET_SINGLE(CollisionManager)->AddCollider(ptr);
		room5.push_back(right);
	}
	
	{
		Wall* right = new Wall(*model_right3);
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
	Model* model_left1 = new Model("res/models/room2/left1.obj");
	Model* model_left2 = new Model("res/models/room2/left2.obj");
	Model* model_left3 = new Model("res/models/room2/left3.obj");
	Model* model_right1 = new Model("res/models/room2/right1.obj");
	Model* model_right2 = new Model("res/models/room2/right2.obj");
	Model* model_right3 = new Model("res/models/room2/right3.obj");

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
		Wall* left = new Wall(*model_left1);
		BoxCollider* ptr = new BoxCollider;
		left->AddComponent(ptr);
		GET_SINGLE(CollisionManager)->AddCollider(ptr);
		room4.push_back(left);
	}
	
	{
		Wall* left = new Wall(*model_left2);
		BoxCollider* ptr = new BoxCollider;
		left->AddComponent(ptr);
		GET_SINGLE(CollisionManager)->AddCollider(ptr);
		room4.push_back(left);
	}
	
	{
		Wall* left = new Wall(*model_left3);
		BoxCollider* ptr = new BoxCollider;
		left->AddComponent(ptr);
		GET_SINGLE(CollisionManager)->AddCollider(ptr);
		room4.push_back(left);
	}

	{
		Wall* right = new Wall(*model_right1);
		BoxCollider* ptr = new BoxCollider;
		right->AddComponent(ptr);
		GET_SINGLE(CollisionManager)->AddCollider(ptr);
		room4.push_back(right);
	}
	
	{
		Wall* right = new Wall(*model_right2);
		BoxCollider* ptr = new BoxCollider;
		right->AddComponent(ptr);
		GET_SINGLE(CollisionManager)->AddCollider(ptr);
		room4.push_back(right);
	}
	
	{
		Wall* right = new Wall(*model_right3);
		BoxCollider* ptr = new BoxCollider;
		right->AddComponent(ptr);
		GET_SINGLE(CollisionManager)->AddCollider(ptr);
		room4.push_back(right);
	}

}

void Stage1::MakeRoom3()
{
	Model* model_front1 = new Model("res/models/room1/front1.obj");
	Model* model_front2 = new Model("res/models/room1/front2.obj");
	Model* model_front3 = new Model("res/models/room1/front3.obj");
	Model* model_back1 = new Model("res/models/room1/back1.obj");
	Model* model_back2 = new Model("res/models/room1/back2.obj");
	Model* model_back3 = new Model("res/models/room1/back3.obj");
	Model* model_left = new Model("res/models/room1/left.obj");
	Model* model_right = new Model("res/models/room1/right.obj");

	{
		Wall* front = new Wall(*model_front1);
		BoxCollider* ptr = new BoxCollider;
		front->AddComponent(ptr);
		GET_SINGLE(CollisionManager)->AddCollider(ptr);
		room3.push_back(front);
	}

	{
		Wall* front = new Wall(*model_front2);
		BoxCollider* ptr = new BoxCollider;
		front->AddComponent(ptr);
		GET_SINGLE(CollisionManager)->AddCollider(ptr);
		room3.push_back(front);
	}

	{
		Wall* front = new Wall(*model_front3);
		BoxCollider* ptr = new BoxCollider;
		front->AddComponent(ptr);
		GET_SINGLE(CollisionManager)->AddCollider(ptr);
		room3.push_back(front);
	}
	
	{
		Wall* back = new Wall(*model_back1);
		BoxCollider* ptr = new BoxCollider;
		back->AddComponent(ptr);
		GET_SINGLE(CollisionManager)->AddCollider(ptr);
		room3.push_back(back);
	}
	
	{
		Wall* back = new Wall(*model_back2);
		BoxCollider* ptr = new BoxCollider;
		back->AddComponent(ptr);
		GET_SINGLE(CollisionManager)->AddCollider(ptr);
		room3.push_back(back);
	}
	
	{
		Wall* back = new Wall(*model_back3);
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

	Model* m_floor = new Model("res/models/stage2/floor.obj");
	Model* m_ceiling = new Model("res/models/stage2/ceiling.obj");
	Model* m_front_wall1 = new Model("res/models/stage2/front1.obj");
	Model* m_front_wall2 = new Model("res/models/stage2/front2.obj");
	Model* m_front_wall3 = new Model("res/models/stage2/front3.obj");
	Model* m_back_wall1 = new Model("res/models/stage2/back1.obj");
	Model* m_back_wall2 = new Model("res/models/stage2/back2.obj");
	Model* m_back_wall3 = new Model("res/models/stage2/back3.obj");
	Model* m_left_wall = new Model("res/models/stage2/left.obj");
	Model* m_right_wall = new Model("res/models/stage2/right.obj");


	// 바닥
	Wall* floor = new Wall(*m_floor);
	BoxCollider* ptr = new BoxCollider;
	floor->AddComponent(ptr);
	//	GET_SINGLE(CollisionManager)->AddCollider(ptr);
	room2.push_back(floor);

	Wall* front_wall_upper = new Wall(*m_front_wall1);
	BoxCollider* ptr2 = new BoxCollider;
	front_wall_upper->AddComponent(ptr2);
	GET_SINGLE(CollisionManager)->AddCollider(ptr2);
	room2.push_back(front_wall_upper);

	Wall* front_wall_left = new Wall(*m_front_wall2);
	BoxCollider* ptr3 = new BoxCollider;
	front_wall_left->AddComponent(ptr3);
	GET_SINGLE(CollisionManager)->AddCollider(ptr3);
	room2.push_back(front_wall_left);


	Wall* front_wall_right = new Wall(*m_front_wall3);
	BoxCollider* ptr4 = new BoxCollider;
	front_wall_right->AddComponent(ptr4);
	GET_SINGLE(CollisionManager)->AddCollider(ptr4);
	room2.push_back(front_wall_right);

	////////////////////////////////////////////////////////////////////////////////////////////////////

	Wall* back_wall_upper = new Wall(*m_back_wall1);
	BoxCollider* ptr5 = new BoxCollider;
	back_wall_upper->AddComponent(ptr5);
	GET_SINGLE(CollisionManager)->AddCollider(ptr5);
	room2.push_back(back_wall_upper);

	Wall* back_wall_left = new Wall(*m_back_wall2);
	BoxCollider* ptr6 = new BoxCollider;
	back_wall_left->AddComponent(ptr6);
	GET_SINGLE(CollisionManager)->AddCollider(ptr6);
	room2.push_back(back_wall_left);

	Wall* back_wall_right = new Wall(*m_back_wall3);
	BoxCollider* ptr7 = new BoxCollider;
	back_wall_right->AddComponent(ptr7);
	GET_SINGLE(CollisionManager)->AddCollider(ptr7);
	room2.push_back(back_wall_right);

	////////////////////////////////////////////////////////////////////////////////////////////////////

	Wall* left_wall = new Wall(*m_left_wall);
	BoxCollider* ptr8 = new BoxCollider;
	left_wall->AddComponent(ptr8);
	GET_SINGLE(CollisionManager)->AddCollider(ptr8);
	room2.push_back(left_wall);

	Wall* right_wall = new Wall(*m_right_wall);
	BoxCollider* ptr9 = new BoxCollider;
	right_wall->AddComponent(ptr9);
	GET_SINGLE(CollisionManager)->AddCollider(ptr9);
	room2.push_back(right_wall);

	////////////////////////////////////////////////////////////////////////////////////////////////////
	// 
	//천장
	Wall* celing = new Wall(*m_ceiling);
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
