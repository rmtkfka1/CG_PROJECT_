#include "pch.h"
#include "stage2.h"
#include "SceneManager.h"
#include "TextManager.h"
#include "SoundManager.h"

stage2::stage2()
{




}

stage2::~stage2()
{

	delete shader;
	delete texture;
	delete model;

}

void stage2::Init()
{

	SoundManager::GetInstance()->Play(START);



	shader = new Shader("res/shader/mvp.vs", "res/shader/mvp.fs");
	shader->Bind();

	model = new Model("res/models/render_box3.obj");

	texture = new Texture("res/textures/start_scene.png");
	texture->Bind(0);


	shader->SetUniformMat4f("u_model", glm::mat4(1.0f));
	shader->SetUniformMat4f("u_view", matrix::GetInstance()->GetCamera(glm::vec3(0, 0, -2.0f), glm::vec3(0, 0, 0), glm::vec3(0, 1, 0)));
	shader->SetUniformMat4f("u_proj", matrix::GetInstance()->Getortho());
	shader->SetUniform1i("u_texture", texture->GetSlot());



}

void stage2::Update()
{
	

}

void stage2::Render()
{
	shader->Bind();
	model->RenderModel(*shader);

	shader->Unbind();
	TextManager::GetInstance()->Render(-0.3f, -0.5f, "Press Enter To Start");


	if (KeyManager::GetInstance()->GetbuttonDown(KeyType::ENTER))
	{
		
		start = true;
	}


	if (start)
	{
		TextManager::GetInstance()->Render(-0.3f, -0.7f, "Wait for Loading");



		if (onetime == false)
		{
			start_time = std::chrono::steady_clock::now(); // 현재 시간으로 시작 시간 저장
			onetime = true;
		}
	}


	if (start)
	{

		auto current_time = std::chrono::steady_clock::now();
		std::chrono::duration<double> elapsed_seconds = current_time - start_time;

		if (elapsed_seconds.count() >= 0.1) 
		{

			SceneManager::GetInstance()->ChangeScene(SceneType::Stage1);
		}

	}
}
