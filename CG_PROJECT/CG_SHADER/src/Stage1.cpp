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
#include "SceneManager.h"
#include "Cat.h"
#include "Spherequiz.h"

Stage1::Stage1()
{
	

}

Stage1::~Stage1()
{

	//// Delete shader
	//delete shader;

	//// Delete objects with different textures
	//delete player;
	//delete flash;
	//delete fake_flash;
	//delete billboard;
	//delete table;
	//delete ghost;
	//delete Corridor_left_door;
	//delete Corridor_right_door;
	//delete deadbody;
	//delete mask_event;
	//delete mask;
	//delete exitdoor;
	//delete exitdoor2;

	//// Delete objects related to room 1 quiz
	//delete quizbox;
	//delete Lockedbox;
	//delete Lockedtable;
	//delete Lockedkey;
	//delete quizbox_event;
	//delete answerbox;

	//// Delete objects related to room 2 quiz
	//delete quizbox2;
	//delete Lockedbox2;
	//delete Lockedtable2;
	//delete Lockedkey2;
	//delete answerbox2;


	//delete texture;
	//delete billboard_texture;
	//delete light_texture;
	//delete table_texture;
	//delete flash_fake_texture;
	//delete ghost_texture;
	//delete door_texture;
	//delete deadbody_texture;
	//delete mask_texture;
	//delete exitdoor_texture;
	//delete quizbox_texture;
	//delete lockedbox_texture;
	//delete answer1_texture;

	//// Deleting light object
	//delete light;

	//for (Object* obj : room1) {
	//	delete obj;
	//}
	//room1.clear();

	//for (Object* obj : corridor1) {
	//	delete obj;
	//}
	//corridor1.clear();

	//for (Object* obj : room2) {
	//	delete obj;
	//}
	//room2.clear();

	//for (Object* obj : room3) {
	//	delete obj;
	//}
	//room3.clear();

	//for (Object* obj : room4) {
	//	delete obj;
	//}
	//room4.clear();

	//for (Object* obj : room5) {
	//	delete obj;
	//}
	//room5.clear();

	//for (Object* obj : room6) {
	//	delete obj;
	//}
	//room6.clear();

	//for (Object* obj : last_corridor) {
	//	delete obj;
	//}
	//last_corridor.clear();

	//for (Object* obj : last_room) {
	//	delete obj;
	//}
	//last_room.clear();

	//for (Object* obj : end_room) {
	//	delete obj;
	//}
	//end_room.clear();






}

void Stage1::Init()
{

	shader = new Shader("res/shader/mvp_spotlight.vs", "res/shader/mvp_spotlight.fs");
	shader->Bind();

	shader2 = new Shader("res/shader/mvp.vs", "res/shader/mvp.fs");



	///////////////////////////////////////////////////모델 불러오기 



	{

		Model* model = new Model("res/models/exitdoor.obj");
		exitdoor = new ExitDoor(*model);
		BoxCollider* ptr = new BoxCollider;
		exitdoor->AddComponent(ptr);
		GET_SINGLE(CollisionManager)->AddCollider(ptr);


	}


	{
		//고스트 생성
		Model* ghost_body = new Model("res/models/ghost/ghost_body.obj");
		Model* ghost_left_arm = new Model("res/models/ghost/ghost_left_arm.obj");
		Model* ghost_right_arm = new Model("res/models/ghost/ghost_right_arm.obj");

		ghost = new Ghost(*ghost_body, *ghost_left_arm, *ghost_right_arm);
		ghost->Init();
		ghost->SetPosition(0.0f, -480.0f);
		BoxCollider* ptr = new BoxCollider;
		ghost->AddComponent(ptr);
		GET_SINGLE(CollisionManager)->AddCollider(ptr);

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
		billboard->SetSize(15.0f, 15.0f);
		billboard->SetPosition(150.0f, 30.0f, -560.0f);
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

	{
		Model* computer_model = new Model("res/models/computer.obj");
		computer = new Event(*computer_model);
		computer->SetSize(glm::vec3(computer->GetSize().x + 20, computer->GetSize().y, computer->GetSize().z));
		BoxCollider* ptr = new BoxCollider;
		computer->AddComponent(ptr);
		GET_SINGLE(CollisionManager)->AddCollider(ptr);
	}

	// 엔딩 고양이
	{
		Model* cat_model = new Model("res/models/cat.obj");
		cat = new Cat(*cat_model);
		BoxCollider* ptr = new BoxCollider;
		cat->AddComponent(ptr);
		GET_SINGLE(CollisionManager)->AddCollider(ptr);
		cat_model->PrintInfo();

	}






	//방1 퀴즈 생성
	MakeRoom1_QUIZ();
	MakeRoom2_QUIZ();
	MakeRoom3_QUIZ();
	MakeRoom4_QUIZ();
/////////////	
	MakeRoom();
	/////////텍스처 만들기/////////////////////////////////////////////////////////////
	MakeTexture();
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


	Corridor_left_door->Update();
	Corridor_right_door->Update();

	{

		quizbox->Update();
		table->Update();
		Lockedbox->Update();
		Lockedtable->Update();
		Lockedkey->Update();
		quizbox_event->Update();
		


		Lockedbox2->Update();
		Lockedtable2->Update();
		Lockedkey2->Update();
		answerbox2->Update();
		box1->Update();
		box2->Update();
		box3->Update();
		box4->Update();
		wall1->Update();
		wall2->Update();

		Lockedbox3->Update();
		Lockedtable3->Update();
		Lockedkey3->Update();
		answerbox3->Update();
		sphere_quiz->SpecialUpdate(Lockedkey3);

		Lockedbox4->Update();
		Lockedtable4->Update();
		Lockedkey4->Update();
		answerbox4->Update();
		room4_event->Update();
		prof->Update();


	}



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
	
	for (int i = 0; i < last_corridor.size(); i++)
	{
		last_corridor[i]->Update();
	}
	
	for (int i = 0; i < last_room.size(); i++)
	{
		last_room[i]->Update();
	}
	
	for (int i = 0; i < end_room.size(); i++)
	{
		end_room[i]->Update();
	}


	

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
	//exitdoor->Update();
	cat->Update();
	computer->Update();
	computer_table->Update();

	//cout << CameraManager::GetInstance()->m_cameraPos.x << "  " << CameraManager::GetInstance()->m_cameraPos.y << "  " << CameraManager::GetInstance()->m_cameraPos.z << endl;


}

void Stage1::Render()
{



	shader->Bind();
	Object_Render();


	shader->Unbind();
	Texture_Render();
	player->DrawGage();






	

}

void Stage1::Object_Render()
{

	light->UseSpotLight(*shader, *ghost);

	shader->SetUniform1i("u_texture", 0);
	player->Render(*shader);

	shader->SetUniformMat4f("u_proj", matrix::GetInstance()->GetProjection());
	shader->SetUniform3f("u_viewpos", CameraManager::GetInstance()->m_cameraPos.x, CameraManager::GetInstance()->m_cameraPos.y, CameraManager::GetInstance()->m_cameraPos.z);
	shader->SetUniformMat4f("u_view", CameraManager::GetInstance()->GetMatrix());


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

	for (int i = 0; i < last_corridor.size(); i++)
	{
		last_corridor[i]->Render(*shader);
	}

	for (int i = 0; i < last_room.size(); i++)
	{
		last_room[i]->Render(*shader);
	}

	for (int i = 0; i < end_room.size(); i++)
	{
		end_room[i]->Render(*shader);
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
		shader->SetUniform1i("u_texture", ghost_texture->GetSlot());
		ghost->Render(*shader);
	}

	//{
	//	shader->SetUniform1i("u_texture", flash_fake_texture->GetSlot());
	//	flash->Render(*shader);
	//}

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
		//shader->SetUniform1i("u_texture", exitdoor_texture->GetSlot());
		//exitdoor->Render(*shader);
	}

	{
		shader->SetUniformMat4f("u_model", glm::mat4(1.0f));
		shader->SetUniform1i("u_texture", cat_texture->GetSlot());
		cat->Render(*shader);
	}


	//퀴즈
	{
		shader->SetUniform1i("u_texture", table_texture->GetSlot());
		table->Render(*shader);
		Lockedtable->Render(*shader);
		Lockedtable2->Render(*shader);
		Lockedtable3->Render(*shader);
		Lockedtable4->Render(*shader);
		computer_table->Render(*shader);
	}



	{
		shader->SetUniform1i("u_texture", quizbox_texture->GetSlot());
		quizbox->Render(*shader);
	}

	{

		shader->SetUniform1i("u_texture", lockedbox_texture->GetSlot());
		Lockedbox->Render(*shader);
		Lockedkey->Render(*shader);
		Lockedbox2->Render(*shader);
		Lockedkey2->Render(*shader);
		Lockedbox3->Render(*shader);
		Lockedkey3->Render(*shader);
		Lockedbox4->Render(*shader);
		Lockedkey4->Render(*shader);

	}

	{
		shader->SetUniform1i("u_texture", answer1_texture->GetSlot());
		shader->SetUniformMat4f("u_model", glm::mat4(1.0f));
		answerbox->RenderModel(*shader);
		answerbox2->Render(*shader);
	}

	{	
		shader->SetUniformMat4f("u_model", glm::mat4(1.0f));
		shader->SetUniform1i("u_texture", starfish_texture->GetSlot());
		sphere_quiz->Render(*shader);
	}


	{
		shader->SetUniform1i("u_texture", answer1_texture->GetSlot());
		answerbox3->Render(*shader);
		answerbox4->Render(*shader);

	}

	{
		shader->SetUniformMat4f("u_model", glm::mat4(1.0f));
		shader->SetUniform1i("u_texture", computer_texture->GetSlot());
		computer->Render(*shader);
	}


	//물고기그리기
	{
		shader->SetUniformMat4f("u_model", glm::mat4(1.0f));
		shader->SetUniform1i("u_texture",fish_texture->GetSlot());

		fish->RenderModel(*shader);
		shader->SetUniformMat4f("u_model", matrix::GetInstance()->GetTranslation(30, 0, -70));
		fish->RenderModel(*shader);

		auto trans = matrix::GetInstance()->GetTranslation(-fish->GetCenter().x, -fish->GetCenter().y, -fish->GetCenter().z);
		auto rotate = matrix::GetInstance()->GetRotate(90, 0, 1, 0);
		auto trans2 = matrix::GetInstance()->GetTranslation(fish->GetCenter().x + 70, fish->GetCenter().y + 0, fish->GetCenter().z - 50);
		auto result = trans2 * rotate * trans;
		shader->SetUniformMat4f("u_model", result);
		fish->RenderModel(*shader);
	}

	//룸2 이벤트 박스그리기
	{
		shader->SetUniform1i("u_texture", box_texture->GetSlot());
		box1->Render(*shader);
		box2->Render(*shader);
		box3->Render(*shader);
		box4->Render(*shader);
		wall1->Render(*shader);
		wall2->Render(*shader);
	}
	//불가사리 그리기
	{
		shader->SetUniform1i("u_texture", starfish_texture->GetSlot());
		starfish->RenderModel(*shader);
	}
	//볼그리기
	{
		shader->SetUniform1i("u_texture", zz_texture->GetSlot());
		shader->SetUniformMat4f("u_model", glm::mat4(1.0f));
		balls->RenderModel(*shader);
	}

	//////////룸4이벤트
	{
		shader->SetUniform1i("u_texture",snape_texture->GetSlot());
		shader->SetUniformMat4f("u_model", glm::mat4(1.0f));
		prof->Render(*shader);
	}





}


void Stage1::Texture_Render()
{

	TextManager::GetInstance()->Render(-1.0f, -0.95f, "GAGE");



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

	if (quizbox_event->box_collusion == true)
	{
		TextManager::GetInstance()->Render(0.0f, 0.0f, " RGBA !?");
	}


	if (Lockedkey->_collusion == true)
	{


		TextManager::GetInstance()->Render(-0.1f, 0.1f,"Press 1,2,3,4");


		string strValue = std::to_string(Lockedkey->_first_set[0]);
		strValue += std::to_string(Lockedkey->_first_set[1]);
		strValue += std::to_string(Lockedkey->_first_set[2]);
		strValue += std::to_string(Lockedkey->_first_set[3]);

		TextManager::GetInstance()->Render(0.0f,0.0f, strValue.c_str());
	}



	if (Lockedkey2->_collusion == true)
	{
		shader2->Bind();
		shader2->SetUniform1i("u_texture", room2_puzzle->GetSlot());
		shader2->SetUniformMat4f("u_model", glm::mat4(1.0f));
		shader2->SetUniformMat4f("u_view", matrix::GetInstance()->GetCamera(glm::vec3(0,0,-2.0f),glm::vec3(0,0,0),glm::vec3(0,1.0f,0)));
		shader2->SetUniformMat4f("u_proj", matrix::GetInstance()->GetProjection());
		render_box->RenderModel(*shader);


		shader->Unbind();



		string strValue = std::to_string(Lockedkey2->_first_set[0]);
		strValue += "    ";
		strValue += std::to_string(Lockedkey2->_first_set[1]);
		strValue += "    ";
		strValue += std::to_string(Lockedkey2->_first_set[2]);
		strValue += "    ";
		strValue += std::to_string(Lockedkey2->_first_set[3]);

		TextManager::GetInstance()->Render(-0.2f, -0.2f, strValue.c_str());
	}

	if (Lockedkey3->_collusion == true)
	{
		TextManager::GetInstance()->Render(0.0f, 0.0f, "solve the quiz!!");
	}

	if (sphere_quiz->_collusion == true)
	{
		TextManager::GetInstance()->Render(0.0f, 0.0f, "solve the quiz!!");
	}


	if (Lockedkey4->_collusion == true)
	{

		TextManager::GetInstance()->Render(-0.1f, 0.1f, "Press 1,2,3,4");


		string strValue = std::to_string(Lockedkey4->_first_set[0]);
		strValue += std::to_string(Lockedkey4->_first_set[1]);
		strValue += std::to_string(Lockedkey4->_first_set[2]);
		strValue += std::to_string(Lockedkey4->_first_set[3]);

		TextManager::GetInstance()->Render(0.0f, 0.0f, strValue.c_str());
	}

	if (room4_event->box_collusion==true)
	{

		shader2->Bind();
		shader2->SetUniform1i("u_texture", room4_puzzle->GetSlot());
		shader2->SetUniformMat4f("u_model", glm::mat4(1.0f));
		shader2->SetUniformMat4f("u_view", matrix::GetInstance()->GetCamera(glm::vec3(0, 0, 2.5f), glm::vec3(0, 0, 0), glm::vec3(0, 1.0f, 0)));
		shader2->SetUniformMat4f("u_proj", matrix::GetInstance()->GetProjection());
		render_box2->RenderModel(*shader);

	}

}


void Stage1::MakeRoom2_QUIZ()
{
	//방2 퀴즈 생성
	{
		Model* box = new Model("res/models/lockedbox.obj");
		Lockedbox2 = new Wall(*box);
		Lockedbox2->SetTransPose(455, 0, 20);
		BoxCollider* ptr = new BoxCollider;
		Lockedbox2->AddComponent(ptr);
		GET_SINGLE(CollisionManager)->AddCollider(ptr);
	}

	{
		Model* table_model = new Model("res/models/lockedtable.obj");
		Lockedtable2 = new Wall(*table_model);
		Lockedtable2->SetTransPose(455, 0, 20);
		BoxCollider* ptr = new BoxCollider;
		Lockedtable2->AddComponent(ptr);
		GET_SINGLE(CollisionManager)->AddCollider(ptr);
	}

	{
		Model* locked_key = new Model("res/models/lockedkey.obj");
		int num[4] = { 3,1,4,4 };// 너가 정답을 설정해줘야됨
		Lockedkey2 = new Locked(*locked_key, num);
		Lockedkey2->SetTransPose(455, 0, 20);
		BoxCollider* ptr = new BoxCollider;
		Lockedkey2->AddComponent(ptr);
		GET_SINGLE(CollisionManager)->AddCollider(ptr);
	}



	{
		Model* answerbox = new Model("res/models/room1_event/answer_box.obj");
		answerbox2 = new Wall(*answerbox);
		answerbox2->SetTransPose(455, 0, 20);
		BoxCollider* ptr = new BoxCollider;
		answerbox2->AddComponent(ptr);
		GET_SINGLE(CollisionManager)->AddCollider(ptr);

	}
	{

		render_box = new Model("res/models/test.obj");
		render_box2 = new Model("res/models/render_box2.obj");
		fish = new Model("res/models/room2_event/fish.obj");
	}

	{
		Model* box1_model = new Model("res/models/room2_event/box1.obj");
		box1 = new Wall(*box1_model);
		BoxCollider* ptr = new BoxCollider;
		box1->AddComponent(ptr);
		GET_SINGLE(CollisionManager)->AddCollider(ptr);
	}

	{
		Model* box2_model = new Model("res/models/room2_event/box2.obj");
		box2 = new Wall(*box2_model);
		BoxCollider* ptr = new BoxCollider;
		box2->AddComponent(ptr);
		GET_SINGLE(CollisionManager)->AddCollider(ptr);
	}

	{
		Model* box3_model = new Model("res/models/room2_event/box3.obj");
		box3 = new Wall(*box3_model);
		BoxCollider* ptr = new BoxCollider;
		box3->AddComponent(ptr);
		GET_SINGLE(CollisionManager)->AddCollider(ptr);
	}

	{
		Model* box4_model = new Model("res/models/room2_event/box4.obj");
		box4 = new Wall(*box4_model);
		BoxCollider* ptr = new BoxCollider;
		box4->AddComponent(ptr);
		GET_SINGLE(CollisionManager)->AddCollider(ptr);
	}

	{


		balls = new Model("res/models/room2_event/balls.obj");
		starfish = new Model("res/models/room2_event/starfish.obj");

	}

	{
		Model* wall1_m = new Model("res/models/room2_event/wall1.obj");
		wall1 = new Wall(*wall1_m);
		BoxCollider* ptr = new BoxCollider;
		wall1->AddComponent(ptr);
		GET_SINGLE(CollisionManager)->AddCollider(ptr);
	}


	{
		Model* wall2_m = new Model("res/models/room2_event/wall2.obj");
		wall2 = new Wall(*wall2_m);
		BoxCollider* ptr = new BoxCollider;
		wall2->AddComponent(ptr);
		GET_SINGLE(CollisionManager)->AddCollider(ptr);
	}
}

void Stage1::MakeRoom3_QUIZ()
{
	//방3 퀴즈 생성
	{
		Model* box = new Model("res/models/lockedbox.obj");
		Lockedbox3 = new Wall(*box);
		Lockedbox3->SetTransPose(0, 0, -250);
		BoxCollider* ptr = new BoxCollider;
		Lockedbox3->AddComponent(ptr);
		GET_SINGLE(CollisionManager)->AddCollider(ptr);
	}

	{
		Model* table_model = new Model("res/models/lockedtable.obj");
		Lockedtable3 = new Wall(*table_model);
		Lockedtable3->SetTransPose(0, 0, -250);
		BoxCollider* ptr = new BoxCollider;
		Lockedtable3->AddComponent(ptr);
		GET_SINGLE(CollisionManager)->AddCollider(ptr);
	}

	{
		Model* locked_key = new Model("res/models/lockedkey.obj");
		int num[4] = { 1,2,3,4 };// 너가 정답을 설정해줘야됨
		Lockedkey3 = new Locked(*locked_key, num);
		Lockedkey3->SetTransPose(0, 0, -250);
		BoxCollider* ptr = new BoxCollider;
		Lockedkey3->AddComponent(ptr);
		GET_SINGLE(CollisionManager)->AddCollider(ptr);
	}

	{
		Model* answerbox = new Model("res/models/room1_event/answer_box.obj");
		answerbox3 = new Wall(*answerbox);
		answerbox3->SetTransPose(0, 0, -250);
		BoxCollider* ptr = new BoxCollider;
		answerbox3->AddComponent(ptr);
		GET_SINGLE(CollisionManager)->AddCollider(ptr);

	}

	{
		Model* upper = new Model("res/models/sphere_quiz/q_upper.obj");
		Model* middle = new Model("res/models/sphere_quiz/q_middle.obj");
		Model* lower = new Model("res/models/sphere_quiz/q_lower.obj");

		sphere_quiz = new Spherequiz(*upper, *middle, *lower);
		BoxCollider* ptr = new BoxCollider;
		sphere_quiz->AddComponent(ptr);
		GET_SINGLE(CollisionManager)->AddCollider(ptr);
	}

	{
		Model* upper = new Model("res/models/sphere_quiz/q_upper.obj");
		Model* middle = new Model("res/models/sphere_quiz/q_middle.obj");
		Model* lower = new Model("res/models/sphere_quiz/q_lower.obj");

		sphere_quiz = new Spherequiz(*upper, *middle, *lower);
		BoxCollider* ptr = new BoxCollider;
		sphere_quiz->AddComponent(ptr);
		GET_SINGLE(CollisionManager)->AddCollider(ptr);
	}
}

void Stage1::MakeRoom4_QUIZ()
{

	//방3 퀴즈 생성
	{
		Model* box = new Model("res/models/lockedbox.obj");
		Lockedbox4 = new Wall(*box);
		Lockedbox4->SetTransPose(300, 0, -250);
		BoxCollider* ptr = new BoxCollider;
		Lockedbox4->AddComponent(ptr);
		GET_SINGLE(CollisionManager)->AddCollider(ptr);
	}

	{
		Model* table_model = new Model("res/models/lockedtable.obj");
		Lockedtable4 = new Wall(*table_model);
		Lockedtable4->SetTransPose(300, 0, -250);
		BoxCollider* ptr = new BoxCollider;
		Lockedtable4->AddComponent(ptr);
		GET_SINGLE(CollisionManager)->AddCollider(ptr);
	}

	{
		Model* locked_key = new Model("res/models/lockedkey.obj");
		int num[4] = { 0,2,0,3 };// 너가 정답을 설정해줘야됨
		Lockedkey4 = new Locked(*locked_key, num);
		Lockedkey4->SetTransPose(300, 0, -250);
		BoxCollider* ptr = new BoxCollider;
		Lockedkey4->AddComponent(ptr);
		GET_SINGLE(CollisionManager)->AddCollider(ptr);
	}

	{
		Model* answerbox = new Model("res/models/room1_event/answer_box.obj");
		answerbox4 = new Wall(*answerbox);
		answerbox4->SetTransPose(300, 0, -250);
		BoxCollider* ptr = new BoxCollider;
		answerbox4->AddComponent(ptr);
		GET_SINGLE(CollisionManager)->AddCollider(ptr);

	}

	{
		Model* pt = new Model("res/models/room4_event/snape.obj");
		prof = new Wall(*pt);
		BoxCollider* ptr = new BoxCollider;
		prof->AddComponent(ptr);
		GET_SINGLE(CollisionManager)->AddCollider(ptr);

	}

	{

		Model* pt = new Model("res/models/room4_event/snape_event.obj");
		room4_event = new Event(*pt);
		BoxCollider* ptr = new BoxCollider;
		room4_event->AddComponent(ptr);
		GET_SINGLE(CollisionManager)->AddCollider(ptr);

	}
}

void Stage1::MakeRoom1_QUIZ()
{
	{
		//퀴즈박스1
		Model* box = new Model("res/models/room1_event/box.obj");
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

		Model* table_model = new Model("res/models/lockedtable.obj");
		Lockedtable = new Wall(*table_model);
		BoxCollider* ptr = new BoxCollider;
		Lockedtable->AddComponent(ptr);
		GET_SINGLE(CollisionManager)->AddCollider(ptr);

	}

	{
		Model* locked_key = new Model("res/models/lockedkey.obj");

		int num[4] = { 1,3,4,1 };
		Lockedkey = new Locked(*locked_key, num);
		BoxCollider* ptr = new BoxCollider;
		Lockedkey->AddComponent(ptr);
		GET_SINGLE(CollisionManager)->AddCollider(ptr);


	}
	{
		Model* temp = new Model("res/models/room1_event/fake_box.obj");
		quizbox_event = new Event(*temp);
		BoxCollider* ptr = new BoxCollider;
		quizbox_event->AddComponent(ptr);
		GET_SINGLE(CollisionManager)->AddCollider(ptr);

	}
	{

		//정답 
		shader->SetUniformMat4f("u_model", glm::mat4(1.0f));
		answerbox = new Model("res/models/room1_event/answer_box.obj");

	}
}

void Stage1::MakeTexture()
{
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
	room2_puzzle = new Texture("res/textures/puzzle.png");
	box_texture = new Texture("res/textures/box.jpg");
	fish_texture = new Texture("res/textures/fish.jpeg");
	starfish_texture = new Texture("res/textures/color.jpeg");
	zz_texture = new Texture("res/textures/zz.jpg");
	room4_puzzle = new Texture("res/textures/puzzle4.png");
	snape_texture = new Texture("res/textures/snape.png");
	computer_texture = new Texture("res/textures/computer.jpeg");
	cat_texture = new Texture("res/textures/cat.png");


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
	room2_puzzle->Bind(12);
	box_texture->Bind(13);
	fish_texture->Bind(14);
	starfish_texture->Bind(15);
	zz_texture->Bind(16);
	room4_puzzle->Bind(17);
	snape_texture->Bind(18);
	computer_texture->Bind(19);
	cat_texture->Bind(20);

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

	MakeLastCorridor();

	MakeLastRoom();

	MakeEndRoom();
}

void Stage1::MakeEndRoom()
{
	Model* floor_model = new Model("res/models/end_room/floor.obj");
	Model* ceiling_model = new Model("res/models/end_room/ceiling.obj");
	Model* front_model = new Model("res/models/end_room/front.obj");
	Model* back_model = new Model("res/models/end_room/back.obj");
	Model* left_model = new Model("res/models/end_room/left.obj");
	Model* right_model = new Model("res/models/end_room/right.obj");

	Wall* floor = new Wall(*floor_model);
	BoxCollider* ptr = new BoxCollider;
	floor->AddComponent(ptr);
	end_room.push_back(floor);

	Wall* front = new Wall(*front_model);
	BoxCollider* ptr2 = new BoxCollider;
	front->AddComponent(ptr2);
	GET_SINGLE(CollisionManager)->AddCollider(ptr2);
	end_room.push_back(front);

	Wall* back = new Wall(*back_model);
	BoxCollider* ptr3 = new BoxCollider;
	back->AddComponent(ptr3);
	GET_SINGLE(CollisionManager)->AddCollider(ptr3);
	end_room.push_back(back);

	Wall* left = new Wall(*left_model);
	BoxCollider* ptr5 = new BoxCollider;
	left->AddComponent(ptr5);
	GET_SINGLE(CollisionManager)->AddCollider(ptr5);
	end_room.push_back(left);

	Wall* right = new Wall(*right_model);
	BoxCollider* ptr6 = new BoxCollider;
	right->AddComponent(ptr6);
	GET_SINGLE(CollisionManager)->AddCollider(ptr6);
	end_room.push_back(right);

	Wall* celing = new Wall(*ceiling_model);
	BoxCollider* ptr7 = new BoxCollider;
	celing->AddComponent(ptr7);
	GET_SINGLE(CollisionManager)->AddCollider(ptr7);
	end_room.push_back(celing);

	{

		Model* table_model = new Model("res/models/computer_table.obj");
		computer_table = new Wall(*table_model);
		BoxCollider* ptr = new BoxCollider;
		computer_table->AddComponent(ptr);
		GET_SINGLE(CollisionManager)->AddCollider(ptr);
	}

}

void Stage1::MakeLastRoom()
{
	Model* floor_model = new Model("res/models/last_room/floor.obj");
	Model* ceiling_model = new Model("res/models/last_room/ceiling.obj");
	Model* front_model = new Model("res/models/last_room/front.obj");
	Model* back1_model = new Model("res/models/last_room/back1.obj");
	Model* back2_model = new Model("res/models/last_room/back2.obj");
	Model* left_model = new Model("res/models/last_room/left.obj");
	Model* right_model = new Model("res/models/last_room/right.obj");


	Wall* floor = new Wall(*floor_model);
	BoxCollider* ptr = new BoxCollider;
	floor->AddComponent(ptr);
	last_room.push_back(floor);

	Wall* front = new Wall(*front_model);
	BoxCollider* ptr2 = new BoxCollider;
	front->AddComponent(ptr2);
	GET_SINGLE(CollisionManager)->AddCollider(ptr2);
	last_room.push_back(front);

	Wall* back1 = new Wall(*back1_model);
	BoxCollider* ptr3 = new BoxCollider;
	back1->AddComponent(ptr3);
	GET_SINGLE(CollisionManager)->AddCollider(ptr3);
	last_room.push_back(back1);
	
	Wall* back2 = new Wall(*back2_model);
	BoxCollider* ptr4 = new BoxCollider;
	back2->AddComponent(ptr4);
	GET_SINGLE(CollisionManager)->AddCollider(ptr4);
	last_room.push_back(back2);

	Wall* left = new Wall(*left_model);
	BoxCollider* ptr5 = new BoxCollider;
	left->AddComponent(ptr5);
	GET_SINGLE(CollisionManager)->AddCollider(ptr5);
	last_room.push_back(left);

	Wall* right = new Wall(*right_model);
	BoxCollider* ptr6 = new BoxCollider;
	right->AddComponent(ptr6);
	GET_SINGLE(CollisionManager)->AddCollider(ptr6);
	last_room.push_back(right);

	Wall* celing = new Wall(*ceiling_model);
	BoxCollider* ptr7 = new BoxCollider;
	celing->AddComponent(ptr7);
	GET_SINGLE(CollisionManager)->AddCollider(ptr7);
	last_room.push_back(celing);

}

void Stage1::MakeLastCorridor()
{
	Model* floor_model = new Model("res/models/last_corridor/floor.obj");
	Model* ceiling_model = new Model("res/models/last_corridor/ceiling.obj");
	Model* left_model = new Model("res/models/last_corridor/left.obj");
	Model* right_model = new Model("res/models/last_corridor/right.obj");


	Wall* floor = new Wall(*floor_model);
	BoxCollider* ptr = new BoxCollider;
	floor->AddComponent(ptr);
	//	GET_SINGLE(CollisionManager)->AddCollider(ptr);
	last_corridor.push_back(floor);

	Wall* ceiling = new Wall(*ceiling_model);
	BoxCollider* ptr2 = new BoxCollider;
	ceiling->AddComponent(ptr2);
	GET_SINGLE(CollisionManager)->AddCollider(ptr2);
	last_corridor.push_back(ceiling);


	Wall* left_wall = new Wall(*left_model);
	BoxCollider* ptr3 = new BoxCollider;
	left_wall->AddComponent(ptr3);
	GET_SINGLE(CollisionManager)->AddCollider(ptr3);
	last_corridor.push_back(left_wall);

	Wall* right_wall = new Wall(*right_model);
	BoxCollider* ptr4 = new BoxCollider;
	right_wall->AddComponent(ptr4);
	GET_SINGLE(CollisionManager)->AddCollider(ptr4);
	last_corridor.push_back(right_wall);

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
	Model* left_obj_model = new Model("res/models/room4/left_obj.obj");
	Model* right_obj_model = new Model("res/models/room4/right_obj.obj");
	Model* front_obj_model = new Model("res/models/room4/front_obj.obj");
	Model* back_obj_model = new Model("res/models/room4/back_obj.obj");
	Model* base_obj_model = new Model("res/models/room4/billboard_base.obj");

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
	
	{
		Wall* left = new Wall(*left_obj_model);
		BoxCollider* ptr = new BoxCollider;
		left->AddComponent(ptr);
		GET_SINGLE(CollisionManager)->AddCollider(ptr);
		room6.push_back(left);
	}
	
	{
		Wall* right = new Wall(*right_obj_model);
		BoxCollider* ptr = new BoxCollider;
		right->AddComponent(ptr);
		GET_SINGLE(CollisionManager)->AddCollider(ptr);
		room6.push_back(right);
	}
	
	{
		Wall* front = new Wall(*front_obj_model);
		BoxCollider* ptr = new BoxCollider;
		front->AddComponent(ptr);
		GET_SINGLE(CollisionManager)->AddCollider(ptr);
		room6.push_back(front);
	}
	
	{
		Wall* back = new Wall(*back_obj_model);
		BoxCollider* ptr = new BoxCollider;
		back->AddComponent(ptr);
		GET_SINGLE(CollisionManager)->AddCollider(ptr);
		room6.push_back(back);
	}
	
	{
		Wall* base = new Wall(*base_obj_model);
		BoxCollider* ptr = new BoxCollider;
		base->AddComponent(ptr);
		GET_SINGLE(CollisionManager)->AddCollider(ptr);
		room6.push_back(base);
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
	Model* model_quizpillar = new Model("res/models/sphere_quiz/pillar.obj");

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

	{
		Wall* pillar = new Wall(*model_quizpillar);
		BoxCollider* ptr = new BoxCollider;
		pillar->AddComponent(ptr);
		GET_SINGLE(CollisionManager)->AddCollider(ptr);
		room5.push_back(pillar);
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
