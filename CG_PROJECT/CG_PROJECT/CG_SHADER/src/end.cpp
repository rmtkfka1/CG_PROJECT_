#include "pch.h"
#include "end.h"
#include "MaskEvent.h"
#include "Model.h"

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

void ENDING::Update(Event* computer)
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
		dt += 1.0f * TimeManager::GetInstance()->GetDeltaTime();
	}
}

void ENDING::Render(Shader* shader)
{

	if (_coding)
	{
	
		shader->SetUniformMat4f("u_model", glm::mat4(1.0f));
		shader->SetUniformMat4f("u_view", matrix::GetInstance()->GetCamera(glm::vec3(0, 6.0f - dt, -2.0f), glm::vec3(0, 6.0f - dt, 0), glm::vec3(0, 1, 0)));
		glm::mat4 projection = glm::mat4(1.0f);
		projection = glm::ortho(-2.0f, 2.0f, -2.0f, 2.0f, -0.1f, 10.0f);
		shader->SetUniformMat4f("u_proj", projection);
		_model->RenderModel(*shader);
	}
}
