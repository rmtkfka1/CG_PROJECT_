#include "pch.h"
#include "Player.h"
#include "Object.h"
#include "Object.h"
#include "Collider.h"
#include "Model.h"

Player::Player(Model& model):Object(ObjectType::PLAYER)
{
	_center = model.GetCenter();
	_size = model.GetSize();
	_first_center = _center;

}

Player::~Player()
{

}

void Player::Init()
{
	Super::Init();


}

void Player::Update()
{


	Super::Update();

	KeyUpdate(); // Ű���� �� �̷������ => ī�޶� ��ġ�� �ٲ� => �÷��̾� ���Ͱ� ������Ʈ�� [ �浹�� ���ؼ�]
	UpdatePos(); // �������Ҷ��� �ڱ⸸�� matrix �� ������ �������� �ϱ⶧���� ��Ʈ���� ���� [ �������� ���ؼ�]


}

void Player::UpdatePos()
{
	_matrix =matrix::GetInstance()->GetTranslation(_center.x, _center.y, _center.z);

}

void Player::Render(Shader& shader,Model& model)
{


	shader.SetUniform3f("control_color", _debug_color.x, _debug_color.y, _debug_color.z);
	auto simple = glm::mat4(1.0f);
	shader.SetUniformMat4f("u_model", simple);
	Super::Render(shader,model);


	shader.SetUniform3f("control_color", 0, 0, 0);
	shader.SetUniformMat4f("u_model", _matrix);
	model.RenderModel(shader);


}

void Player::KeyUpdate()
{
	float dt =TimeManager::GetInstance()->GetDeltaTime();

	
	if(KeyManager::GetInstance()->Getbutton(KeyType::W))
	{

		_center += _speed * CameraManager::GetInstance()->m_cameraFront * dt;



		_center.y = 5.0f;

	}

	if (KeyManager::GetInstance()->Getbutton(KeyType::S))
	{
		_center -= _speed * CameraManager::GetInstance()->m_cameraFront * dt;

		_center.y = 5.0f;
	}

	auto cameraRight = glm::normalize(glm::cross(
		CameraManager::GetInstance()->m_cameraUp, -CameraManager::GetInstance()->m_cameraFront));

	if (KeyManager::GetInstance()->Getbutton(KeyType::A))
	{
		_center -= _speed * cameraRight * dt;
		_center.y = 5.0f;

	}

	if (KeyManager::GetInstance()->Getbutton(KeyType::D))
	{
		_center += _speed * cameraRight * dt;
;		_center.y = 5.0f;
	}
}

void Player::OnComponentBeginOverlap(Collider* collider, Collider* other)
{


	// �ε��� ������ ������ ���̵� ����, �밢���� ���� ������ �ʿ���
	auto cameraRight = glm::normalize(glm::cross(CameraManager::GetInstance()->m_cameraUp, -(CameraManager::GetInstance()->m_cameraFront)));
	float dt = TimeManager::GetInstance()->GetDeltaTime();

	if (other->GetOwner()->GetObjectType() == ObjectType::WALL)
	{
		
		if (KeyManager::GetInstance()->Getbutton(KeyType::W))
		{
			_center -= _speed * CameraManager::GetInstance()->m_cameraFront * dt;

		}

		if (KeyManager::GetInstance()->Getbutton(KeyType::S))
		{
			// ++ front
			_center += _speed * CameraManager::GetInstance()->m_cameraFront * dt;

		}

		if (KeyManager::GetInstance()->Getbutton(KeyType::A))
		{
			// ++ right
			_center += _speed * cameraRight * dt;
			
			
		}
		if (KeyManager::GetInstance()->Getbutton(KeyType::D))
		{
			// ++ right
			_center -= _speed * cameraRight * dt;


		}

		_speed = 0.0f;
	}


	_debug_color.x = 0;
	_debug_color.y = 1;
	_debug_color.z = 0;




}

void Player::OnComponentEndOverlap(Collider* collider, Collider* other)
{
	

	_debug_color.x = 1;
	_debug_color.y = 0;
	_debug_color.z = 0;

	// �ӵ� ���󺹱�

	_speed = 40.0f;


}
