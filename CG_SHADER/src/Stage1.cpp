#include "pch.h"
#include "Stage1.h"
#include "Player.h"
#include "Wall.h"
#include "BoxCollider.h"
#include "CollisionManager.h"
#include "Light2.h"
#include "Test.h"

Stage1::Stage1()
{
	

}

Stage1::~Stage1()
{


}

void Stage1::Init()
{

	shader = new Shader("res/shader/simple.vs", "res/shader/simple.fs");
	text_shader =new Shader("res/shader/real_simple.vs", "res/shader/real_simple.fs");
	shader->Bind();
	
	///////////////////////////////////////////////////모델 불러오기 
	test_model = new Model("res/models/box.obj");
	player_model = new Model("res/models/player.obj");
	wall_model = new Model("res/models/test_box.obj");
	ptr = new Model("res/models/test.obj");
	///////////////////////////////////////////////////////////////////////////////////////////

	///오브젝트 생성////////////////////////////////////////////////////////////////////////////
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
		test = new Test(*test_model);
		BoxCollider* ptr = new BoxCollider;
		test->AddComponent(ptr);
		GET_SINGLE(CollisionManager)->AddCollider(ptr);
	}


	///////////////////////////////////////////////////////////////////////////////////
	
	/////////텍스처 만들기/////////////////////////////////////////////////////////////
	texture = new Texture("res/textures/1.jpg");
	texture2 = new Texture("res/textures/putin.jpeg");
	texture3 = new Texture("res/textures/text_first.png");

	texture->Bind(0);
	texture2->Bind(1);
	texture3->Bind(2);

	////////////////////////조명작업///////////////////////////////////////////////////
	light = new Light2();
	light->UseLight(*shader);

	light->SetLightPos(glm::vec3(0, 10.0f, 0.0f));


	shader->SetUniformMat4f("u_proj", matrix::GetInstance()->GetProjection());
	///////////////////////////////////////////////////////////////////////////////////

	test_model->PrintInfo();
}

void Stage1::Update()
{

	CameraManager::GetInstance()->KeyUpdate();
	CameraManager::GetInstance()->MouseUpdate(MouseManager::GetInstance()->GetMousePos().x, MouseManager::GetInstance()->GetMousePos().y);

	player->Update();
	test->Update();


	light->_light.position = CameraManager::GetInstance()->m_cameraPos;
	light->_light.direction = CameraManager::GetInstance()->m_cameraFront;
	light->UseLight(*shader);

	shader->SetUniform3f("u_viewpos", CameraManager::GetInstance()->m_cameraPos.x, CameraManager::GetInstance()->m_cameraPos.y, CameraManager::GetInstance()->m_cameraPos.z);
	shader->SetUniformMat4f("u_view", CameraManager::GetInstance()->GetMatrix());
	for (auto& ele : v_wall)
	{
		ele->Update();
	}

	GET_SINGLE(CollisionManager)->Update();
	

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
	



}

void Stage1::Render()
{

	glEnable(GL_DEPTH_TEST);
	glViewport(0, 0, 3000, 3000);

	shader->SetUniform1i("u_texture", 0);
	player->Render(*shader, *player_model, matrix::GetInstance()->GetTranslation(player->GetCenter_x(), player->GetCenter_y(), player->GetCenter_z()));



	
	shader->SetUniform1i("u_texture", 1);
	for (auto& ele : v_wall)
	{
		
		ele->Render(*shader, *wall_model,matrix::GetInstance()->GetSimple());
	}

	test->Render(*shader, *test_model,glm::mat4(1.0f));


	if (test->_collusion)
	{
		shader->SetUniform1i("u_texture", 2);
		glDisable(GL_DEPTH_TEST);
		glViewport(0, 0, 3000, 800);
		shader->SetUniformMat4f("u_view", matrix::GetInstance()->
			GetCamera(glm::vec3(ptr->GetCenter().x, ptr->GetCenter().y, ptr->GetCenter().z + 10), glm::vec3(ptr->GetCenter().x, ptr->GetCenter().y, ptr->GetCenter().z), glm::vec3(0, 1, 0)));
		ptr->RenderModel(*shader);
	}






}
