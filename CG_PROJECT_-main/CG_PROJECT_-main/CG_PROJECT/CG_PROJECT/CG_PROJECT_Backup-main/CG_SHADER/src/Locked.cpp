#include "pch.h"
#include "Locked.h"

Locked::Locked(Model& model):Object(ObjectType::LOCKED)
{
	_center.x = model.GetCenter().x;
	_center.y = model.GetCenter().y;
	_center.z = model.GetCenter().z;

	_size.x = model.GetSize().x+  20;
	_size.y = model.GetSize().y;
	_size.z = model.GetSize().z;

	_first_center = _center;
	_model = &model;



}

Locked::~Locked()
{


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

			num2[0] = (num2[0] + 1) % 10;

		}

		if (KeyManager::GetInstance()->GetbuttonDown(KeyType::TWO))
		{

			num2[1] = (num2[1] + 1) % 10;

		}

		if (KeyManager::GetInstance()->GetbuttonDown(KeyType::THREE))
		{

			num2[2] = (num2[2] + 1) % 10;

		}

		if (KeyManager::GetInstance()->GetbuttonDown(KeyType::FOUR))
		{

			num2[3] = (num2[3] + 1) % 10;

		}

		if (num2[0] == 1 && num2[1] == 3 && num2[2] == 4 && num2[3] == 1)
		{
			locked2 = false;
		}


	}



	if (_collusion && locked2 == false)
	{

		if (_degree < 180.0f)
		{
			_degree += _speed * TimeManager::GetInstance()->GetDeltaTime();
			auto trans1 = matrix::GetInstance()->GetTranslation(-(_center.x), - _center.y,-  (_center.z -_size.z/2));
			auto rotate = matrix::GetInstance()->GetRotate(_degree, 0, 1, 0);
			auto trans2 = matrix::GetInstance()->GetTranslation(_center.x, _center.y, (_center.z- _size.z/2));

			auto result = trans2 * rotate * trans1;
			_matrix = result;
		}


	}


}

void Locked::Render(Shader& shader)
{
	cout << CameraManager::GetInstance()->m_cameraPos.x<<"  " << CameraManager::GetInstance()->m_cameraPos.y <<"  " << CameraManager::GetInstance()->m_cameraPos.z << endl;
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
