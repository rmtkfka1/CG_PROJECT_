#include "pch.h"
#include "Locked.h"




Locked::Locked(Model& model, int answer[4]) :Object(ObjectType::LOCKED)
{
	_center.x = model.GetCenter().x;
	_center.y = model.GetCenter().y;
	_center.z = model.GetCenter().z;


	_size.x = model.GetSize().x + 20;
	_size.y = model.GetSize().y;
	_size.z = model.GetSize().z;

	_first_center = _center;
	_model = &model;

	for (int i = 0; i < 4; ++i) {
		_answer[i] = answer[i];
	}

}

Locked::~Locked()
{
	if (_model != nullptr)
	{
		delete _model;
		_model = nullptr;
	}

}

void Locked::Init()
{
	Super::Init();

}

void Locked::Update()
{
	Super::Update();


	if (_collusion)
	{


		if (KeyManager::GetInstance()->GetbuttonDown(KeyType::ONE))
		{

			_first_set[0] = (_first_set[0] + 1) % 10;

		}

		if (KeyManager::GetInstance()->GetbuttonDown(KeyType::TWO))
		{

			_first_set[1] = (_first_set[1] + 1) % 10;

		}

		if (KeyManager::GetInstance()->GetbuttonDown(KeyType::THREE))
		{

			_first_set[2] = (_first_set[2] + 1) % 10;

		}

		if (KeyManager::GetInstance()->GetbuttonDown(KeyType::FOUR))
		{

			_first_set[3] = (_first_set[3] + 1) % 10;

		}

		if (_first_set[0] == _answer[0] && _first_set[1] == _answer[1] && _first_set[2] == _answer[2]  && _first_set[3] == _answer[3])
		{
			_locked = false;
		}


	}



	if (_locked == false)
	{

		if (_degree < 180.0f)
		{
			_degree += _speed * TimeManager::GetInstance()->GetDeltaTime();

			auto trans0 = matrix::GetInstance()->GetTranslation(_dx,_dy,_dz);

			auto trans1 = matrix::GetInstance()->GetTranslation(-(_center.x), - _center.y,-  (_center.z -_size.z/2));
			auto rotate = matrix::GetInstance()->GetRotate(_degree, 0, 1, 0);
			auto trans2 = matrix::GetInstance()->GetTranslation(_center.x, _center.y, (_center.z- _size.z/2));

			auto result = trans2 * rotate * trans1* trans0;
			_matrix = result ;
		}


	}


}

void Locked::Render(Shader& shader)
{
	
	Super::Render(shader);
	
	shader.SetUniform3f("control_color", 0, 0, 0);
	shader.SetUniformMat4f("u_model", _matrix);
	_model->RenderModel(shader);

}

void Locked::OnComponentBeginOverlap(Collider* collider, Collider* other)
{
	if (other->GetOwner()->GetObjectType() == ObjectType::PLAYER)
	{

		_collusion = true;

	
	}

}

void Locked::OnComponentEndOverlap(Collider* collider, Collider* other)
{

	if (other->GetOwner()->GetObjectType() == ObjectType::PLAYER)
	{

		_collusion = false;

	
	}
}
