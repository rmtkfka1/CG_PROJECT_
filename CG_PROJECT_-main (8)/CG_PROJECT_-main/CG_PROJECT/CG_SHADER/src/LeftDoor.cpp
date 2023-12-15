#include "pch.h"
#include "LeftDoor.h"
#include "Player.h"
#include "BoxCollider.h"
LeftDoor::LeftDoor(Model& model):Object(ObjectType::LEFTDOOR)
{
	_center.x = model.GetCenter().x;
	_center.y = model.GetCenter().y+0.1f;
	_center.z = model.GetCenter().z;
	_size.x =  model.GetSize().x;
	_size.y = model.GetSize().y;
	_size.z = model.GetSize().z+30;
	_first_center = _center;
	_model = &model;

}

LeftDoor::~LeftDoor()
{
	if (_model != nullptr)
	{
		delete _model;
		_model = nullptr;
	}

}

void LeftDoor::Init()
{
	Super::Init();
}

void LeftDoor::Update()
{
	Super::Update();


	
	if (_test == false)
	{
		if (_collusion)
		{

			auto current_time = std::chrono::steady_clock::now();
			std::chrono::duration<double> elapsed_seconds = current_time - start_time;

			// 3�ʰ� ������ _collusion�� false�� ����
			if (elapsed_seconds.count() >= 1.0) {
				_collusion = false;
			}


			if (_degree < 90.0f)
			{
				_degree += _speed * TimeManager::GetInstance()->GetDeltaTime();
				auto trans1 = matrix::GetInstance()->GetTranslation(-(_center.x - _size.x / 2), -_center.y, -_center.z);
				auto rotate = matrix::GetInstance()->GetRotate(_degree, 0, 1, 0);
				auto trans2 = matrix::GetInstance()->GetTranslation((_center.x - _size.x / 2), _center.y, _center.z);

				auto result = trans2 * rotate * trans1;
				_matrix = result;
			}

		}

		else
		{
			if (_degree > 0)
			{
				_degree -= _speed * TimeManager::GetInstance()->GetDeltaTime();
				auto trans1 = matrix::GetInstance()->GetTranslation(-(_center.x - _size.x / 2), -_center.y, -_center.z);
				auto rotate = matrix::GetInstance()->GetRotate(_degree, 0, 1, 0);
				auto trans2 = matrix::GetInstance()->GetTranslation((_center.x - _size.x / 2), _center.y, _center.z);

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

			// 3�ʰ� ������ _collusion�� false�� ����
			if (elapsed_seconds.count() >= 1.0) {
				_collusion = false;
			}


			if (_degree > -90.0f)
			{
				_degree -= _speed * TimeManager::GetInstance()->GetDeltaTime();
				auto trans1 = matrix::GetInstance()->GetTranslation(-(_center.x - _size.x / 2), -_center.y, -_center.z);
				auto rotate = matrix::GetInstance()->GetRotate(_degree, 0, 1, 0);
				auto trans2 = matrix::GetInstance()->GetTranslation((_center.x - _size.x / 2), _center.y, _center.z);

				auto result = trans2 * rotate * trans1;
				_matrix = result;
			}

		}

		else
		{
			if (_degree < 0)
			{
				_degree += _speed * TimeManager::GetInstance()->GetDeltaTime();
				auto trans1 = matrix::GetInstance()->GetTranslation(-(_center.x - _size.x / 2), -_center.y, -_center.z);
				auto rotate = matrix::GetInstance()->GetRotate(_degree, 0, 1, 0);
				auto trans2 = matrix::GetInstance()->GetTranslation((_center.x - _size.x / 2), _center.y, _center.z);

				auto result = trans2 * rotate * trans1;
				_matrix = result;
			}

			

		}
	}

}

void LeftDoor::Render(Shader& shader)
{
	Super::Render(shader);


	shader.SetUniform3f("control_color", 0, 0, 0);
	shader.SetUniformMat4f("u_model", _matrix);
	_model->RenderModel(shader);
}


void LeftDoor::OnComponentBeginOverlap(Collider* collider, Collider* other)
{
	if (other->GetOwner()->GetObjectType() == ObjectType::PLAYER)
	{

		_collusion = true;
		start_time = std::chrono::steady_clock::now(); // ���� �ð����� ���� �ð� ����




		if (_center.z < other->GetOwner()->GetCenter_z())
		{
			_test = false;
		}
		else
		{
			_test=true;
		}


		SoundManager::GetInstance()->Play(DOOR);

	}


}

void LeftDoor::OnComponentEndOverlap(Collider* collider, Collider* other)
{
	
	
}
