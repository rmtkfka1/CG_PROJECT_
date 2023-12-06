#include "pch.h"
#include "Mask.h"
#include "MaskEvent.h"
Mask::Mask(Model& model):Object(ObjectType::MASK)
{

	_center = model.GetCenter();
	_size = model.GetSize();
	_first_center = _center;
	_model = &model;
}

Mask::~Mask()
{
	if (_model != nullptr)
	{
		delete _model;
		_model = nullptr;
	}
}

void Mask::Init()
{
	Super::Init();
}

void Mask::Update()
{
	Super::Update();
}

void Mask::Render(Shader& shader)
{
	Super::Render(shader);

	shader.SetUniform3f("control_color", 0, 0, 0);
	shader.SetUniformMat4f("u_model", _matrix);
	_model->RenderModel(shader);
}

void Mask::MatrixUpdate(Event* ptr)
{

	if (delta > 600)
	{
		return;
	}


	if (ptr->GetCollison())
	{


		delta += speed * TimeManager::GetInstance()->GetDeltaTime();

		_matrix = matrix::GetInstance()->GetTranslation(0, 0, delta);
		
		_center =_first_center + glm::vec3(0, 0, delta);
	}


}



void Mask::OnComponentBeginOverlap(Collider* collider, Collider* other)
{

	


		if (other->GetOwner()->GetObjectType() == ObjectType::PLAYER)
		{
			if (play_sound == false)
			{
				SoundManager::GetInstance()->Play(HEARTBEAT);
				play_sound = true;
			}

		
		}
	

}

void Mask::OnComponentEndOverlap(Collider* collider, Collider* other)
{



}
