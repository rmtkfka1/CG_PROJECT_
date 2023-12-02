#include "pch.h"
#include "ExitDoor.h"
#include "BoxCollider.h"
ExitDoor::ExitDoor(Model& model):Object(ObjectType::EXITDOOR)
{

	_center.x = model.GetCenter().x;
	_center.y = model.GetCenter().y;
	_center.z = model.GetCenter().z;
	_size.x = model.GetSize().x;
	_size.y = model.GetSize().y;
	_size.z = model.GetSize().z+10;
	_first_center = _center;
	_model = &model;

}

ExitDoor::~ExitDoor()
{
}

void ExitDoor::Init()
{
	Super::Init();
}

void ExitDoor::Update()
{

	Super::Update();

	if (_collusion && locked==false)
	{

		if (_degree < 90.0f)
		{
			_degree += _speed * TimeManager::GetInstance()->GetDeltaTime();
			auto trans1 = matrix::GetInstance()->GetTranslation(-(_center.x + _size.x / 2), -_center.y, -_center.z);
			auto rotate = matrix::GetInstance()->GetRotate(_degree, 0, -1, 0);
			auto trans2 = matrix::GetInstance()->GetTranslation((_center.x + _size.x / 2), _center.y, _center.z);

			auto result = trans2 * rotate * trans1;
			_matrix = result;
		}

	}


	

}

void ExitDoor::Render(Shader& shader)
{
	Super::Render(shader);


	shader.SetUniform3f("control_color", 0, 0, 0);
	shader.SetUniformMat4f("u_model", _matrix);
	_model->RenderModel(shader);
}

void ExitDoor::OnComponentBeginOverlap(Collider* collider, Collider* other)
{
	if (other->GetOwner()->GetObjectType() == ObjectType::PLAYER)
	{
		_collusion = true;

	}
}

void ExitDoor::OnComponentEndOverlap(Collider* collider, Collider* other)
{

	if (other->GetOwner()->GetObjectType() == ObjectType::PLAYER)
	{
		_collusion = false;
	}
}
