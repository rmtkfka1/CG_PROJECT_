#include "pch.h"
#include "Door.h"
#include "Model.h"
#include "Collider.h"

DOOR::DOOR(Model& model) :Object(ObjectType::DOOR)
{
	_center = model.GetCenter();
	_size.x = model.GetSize().x;
	_size.y = model.GetSize().y;
	_size.z = model.GetSize().z + 20.0f;
	_first_center = _center;
	_model = &model;

}

DOOR::~DOOR()
{

}

void DOOR::Init()
{
	Super::Init();
}

void DOOR::Update()
{
	Super::Update();

	if (KeyManager::GetInstance()->Getbutton(KeyType::F))
	{
		if (_status == DoorStatus::LOCKED)
		{
			_status = DoorStatus::UNLOCKED;
			cout << "DOOR UNLOCKED" << endl;
		}
		else
		{
			_status = DoorStatus::LOCKED;
			cout << "DOOR LOCKED" << endl;
		}
	}

	if (_status != DoorStatus::LOCKED)
	{
		if (_status == DoorStatus::OPENING)
		{
			_degree -= _open_speed * GET_SINGLE(TimeManager)->GetDeltaTime();
			auto trans1 = matrix::GetInstance()->GetTranslation(-_model->GetCenter().x - _model->GetSize().x / 2, -_model->GetCenter().y, -_model->GetCenter().z);
			auto rotate = matrix::GetInstance()->GetRotate(_degree, 0, 1, 0);
			auto trans2 = matrix::GetInstance()->GetTranslation(_model->GetCenter().x + _model->GetSize().x / 2, _model->GetCenter().y, _model->GetCenter().z);

			_door_matrix = trans2 * rotate * trans1;

			if (_degree <= -90.0f)
			{
				_status = DoorStatus::OPENED;
			}
		}

		if (_status == DoorStatus::CLOSING)
		{
			_degree += 80.0f * GET_SINGLE(TimeManager)->GetDeltaTime();
			auto trans1 = matrix::GetInstance()->GetTranslation(-_model->GetCenter().x - _model->GetSize().x / 2, -_model->GetCenter().y, -_model->GetCenter().z);
			auto rotate = matrix::GetInstance()->GetRotate(_degree, 0, 1, 0);
			auto trans2 = matrix::GetInstance()->GetTranslation(_model->GetCenter().x + _model->GetSize().x / 2, _model->GetCenter().y, _model->GetCenter().z);

			auto result = trans2 * rotate * trans1;
			_door_matrix = result;

			if (_degree >= 0.0f)
			{
				_status = DoorStatus::CLOSED;
			}
		}

	}
	

}

void DOOR::Render(Shader& shader)
{
	Super::Render(shader);


	shader.SetUniform3f("control_color", 0, 0, 0);
	shader.SetUniformMat4f("u_model", _door_matrix * _matrix);
	_model->RenderModel(shader);

}

void DOOR::OnComponentBeginOverlap(Collider* collider, Collider* other)
{
	_collusion = true;

	if (other->GetOwner()->GetObjectType() == ObjectType::PLAYER)
	{
		if (_degree >= -90.0f && _status != DoorStatus::LOCKED)
		{
			_status = DoorStatus::OPENING;
		}
	}

	_debug_color.x = 0;
	_debug_color.y = 1;
	_debug_color.z = 0;
}

void DOOR::OnComponentEndOverlap(Collider* collider, Collider* other)
{
	_collusion = false;
	
	if (other->GetOwner()->GetObjectType() == ObjectType::PLAYER)
	{
		if (_degree <= 0.0f && _status != DoorStatus::LOCKED)
		{
			_status = DoorStatus::CLOSING;
		}

		
	}
	

	_debug_color.x = 1;
	_debug_color.y = 0;
	_debug_color.z = 0;
}
