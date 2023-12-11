#include "pch.h"
#include "MaskEvent.h"
#include "BoxCollider.h"
#include "DeadBody.h"


Event::Event(Model& model,string type) :Object(ObjectType::MASKEVENT)
{
	_center = model.GetCenter();
	_size = model.GetSize();
	_first_center = _center;
	_model = &model;
	_type = type;

}

Event::~Event()
{

	if (_model != nullptr)
	{
		delete _model;
		_model = nullptr;
	}
}

void Event::Init()
{
	Super::Init();
}

void Event::Update()
{
	Super::Update();

}



void Event::Render(Shader& shader)
{

	Super::Render(shader);


	shader.SetUniform3f("control_color", 0, 0, 0);
	shader.SetUniformMat4f("u_model", _matrix);
	_model->RenderModel(shader);

}

void Event::OnComponentBeginOverlap(Collider* collider, Collider* other)
{
	if (other->GetOwner()->GetObjectType() == ObjectType::PLAYER)
	{
	
		_collison_onetime = true;
		_collison_everytime = true;

		if (_type == "mask")
		{
			if (scare_sound1 == false)
			{
				SoundManager::GetInstance()->Play(SCARE);
				scare_sound1 = true;
			}
		}

		
	}
}

void Event::OnComponentEndOverlap(Collider* collider, Collider* other)
{

	if (other->GetOwner()->GetObjectType() == ObjectType::PLAYER)
	{
		_collison_everytime = false;
	}
}

