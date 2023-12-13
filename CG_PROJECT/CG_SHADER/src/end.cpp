#include "pch.h"
#include "end.h"
#include "MaskEvent.h"
#include "Model.h"
#include "Light2.h"
ENDING::ENDING(Model& model)
{

	_model = &model;
}

ENDING::~ENDING()
{
}

void ENDING::Init()
{
}

void ENDING::Update(Event* computer,Light2* light)
{
	if (computer->_collison_onetime)
	{

		if (KeyManager::GetInstance()->GetbuttonDown(KeyType::F))
		{
			_coding = true;

		}
	}

	if (_coding)
	{
		dt += 0.3f * TimeManager::GetInstance()->GetDeltaTime();
	}

	if (dt > 5.5f)
	{
		SoundManager::GetInstance()->real_end = true;
		if (dt < 6.5f)
		{
			SoundManager::GetInstance()->Stop(ENDINGSONG);
		}
		
		if (SoundManager::GetInstance()->realrealreal_end == false)
		{
			SoundManager::GetInstance()->Play(GHOST_SCREAM);
		}
		light->point_light.diffuse = glm::vec3(1.0f, 0, 0);
		light->point_light.distance = 200.0f;
		light->Spot_light.distance = 500.0f;

		
	}

	if (dt > 10.0f)
	{
		ft += 8.0f * TimeManager::GetInstance()->GetDeltaTime();
	}


	
}

void ENDING::Render(Shader* shader)
{

	if (_coding)
	{
	
		shader->SetUniformMat4f("u_model", glm::mat4(1.0f));
		shader->SetUniformMat4f("u_view", matrix::GetInstance()->GetCamera(glm::vec3(0, 6.0f - dt, -2.0f), glm::vec3(0, 6.0f - dt, 0), glm::vec3(0, 1, 0)));
		glm::mat4 projection = glm::mat4(1.0f);
		projection = glm::ortho(-1.0f, 1.0f, -2.0f, 2.0f, -0.1f, 10.0f);
		shader->SetUniformMat4f("u_proj", projection);

		_model->RenderModel(*shader);
	}




}
