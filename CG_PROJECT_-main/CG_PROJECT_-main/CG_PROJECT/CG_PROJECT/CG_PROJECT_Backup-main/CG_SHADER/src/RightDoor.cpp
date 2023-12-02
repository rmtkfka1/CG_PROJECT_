#include "pch.h"
#include "RightDoor.h"
#include "BoxCollider.h"



RightDoor::RightDoor(Model& model) :Object(ObjectType::RIGHTDOOR)
{
	_center.x = model.GetCenter().x;
	_center.y = model.GetCenter().y + 0.1f;
	_center.z = model.GetCenter().z;
	_size.x = model.GetSize().x;
	_size.y = model.GetSize().y;
	_size.z = model.GetSize().z + 30;
	_first_center = _center;
	_model = &model;

}

RightDoor::~RightDoor()
{


}

void RightDoor::Init()
{
	Super::Init();
}

void RightDoor::Update()
{
	Super::Update();




	if (_test == false)
	{
		if (_collusion)
		{

			auto current_time = std::chrono::steady_clock::now();
			std::chrono::duration<double> elapsed_seconds = current_time - start_time;

		
			if (elapsed_seconds.count() >= 1.0) {
				_collusion = false;
			}


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

		else
		{
			if (_degree > 0)
			{
				_degree -= _speed * TimeManager::GetInstance()->GetDeltaTime();
				auto trans1 = matrix::GetInstance()->GetTranslation(-(_center.x + _size.x / 2), -_center.y, -_center.z);
				auto rotate = matrix::GetInstance()->GetRotate(_degree, 0, -1, 0);
				auto trans2 = matrix::GetInstance()->GetTranslation((_center.x + _size.x / 2), _center.y, _center.z);

				auto result = trans2 * rotate * trans1;
				_matrix = result;
			}
			
		

		}
	}

	else
	{
		if (_collusion)
		{

			auto current_time = std::chrono::steady_clock::now();
			std::chrono::duration<double> elapsed_seconds = current_time - start_time;


			if (elapsed_seconds.count() >= 1.0) {
				_collusion = false;
			}


			if (_degree > -90.0f)
			{
				_degree -= _speed * TimeManager::GetInstance()->GetDeltaTime();
				auto trans1 = matrix::GetInstance()->GetTranslation(-(_center.x + _size.x / 2), -_center.y, -_center.z);
				auto rotate = matrix::GetInstance()->GetRotate(_degree, 0, -1, 0);
				auto trans2 = matrix::GetInstance()->GetTranslation((_center.x + _size.x / 2), _center.y, _center.z);

				auto result = trans2 * rotate * trans1;
				_matrix = result;
			}

		}

		else
		{
			if (_degree < 0)
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

}

void RightDoor::Render(Shader& shader)
{
	Super::Render(shader);


	shader.SetUniform3f("control_color", 0, 0, 0);
	shader.SetUniformMat4f("u_model", _matrix);
	_model->RenderModel(shader);
}


void RightDoor::OnComponentBeginOverlap(Collider* collider, Collider* other)
{
	if (other->GetOwner()->GetObjectType() == ObjectType::PLAYER)
	{

		_collusion = true;
		start_time = std::chrono::steady_clock::now(); // 현재 시간으로 시작 시간 저장



		if (_center.z < other->GetOwner()->GetCenter_z())
		{
			_test = false;
		}
		else
		{
			_test = true;
		}

	}


}

void RightDoor::OnComponentEndOverlap(Collider* collider, Collider* other)
{

}