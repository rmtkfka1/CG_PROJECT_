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
	KeyUpdate();

	Super::Update();




}

void Player::Render(Shader& shader,Model& model,glm::mat4 matrix)
{


	shader.SetUniform3f("control_color", _debug_color.x, _debug_color.y, _debug_color.z);
	auto simple = glm::mat4(1.0f);
	shader.SetUniformMat4f("u_model", simple);
	Super::Render(shader,model,matrix);


	shader.SetUniform3f("control_color", 0, 0, 0);
	shader.SetUniformMat4f("u_model", matrix);
	model.RenderModel(shader);

}

void Player::KeyUpdate()
{
	if(KeyManager::GetInstance()->Getbutton(KeyType::W))
	{
		_center.x = CameraManager::GetInstance()->m_cameraPos.x;
		_center.y = 0;
		_center.z = CameraManager::GetInstance()->m_cameraPos.z;

	}

	if (KeyManager::GetInstance()->Getbutton(KeyType::S))
	{
		_center.x = CameraManager::GetInstance()->m_cameraPos.x;
		_center.y = 0;
		_center.z = CameraManager::GetInstance()->m_cameraPos.z;

	}

	if (KeyManager::GetInstance()->Getbutton(KeyType::A))
	{
		_center.x = CameraManager::GetInstance()->m_cameraPos.x;
		_center.y = 0;
		_center.z = CameraManager::GetInstance()->m_cameraPos.z;
	}

	if (KeyManager::GetInstance()->Getbutton(KeyType::D))
	{
		_center.x = CameraManager::GetInstance()->m_cameraPos.x;
		_center.y = 0;
		_center.z = CameraManager::GetInstance()->m_cameraPos.z;

	}
}

void Player::OnComponentBeginOverlap(Collider* collider, Collider* other)
{

	if (other->GetOwner()->GetObjectType() == ObjectType::WALL)
	{
		// �ε��� ������ ������ ���̵� ����, �밢���� ���� ������ �ʿ���
		auto cameraRight = glm::normalize(glm::cross(CameraManager::GetInstance()->m_cameraUp, -(CameraManager::GetInstance()->m_cameraFront)));
		float dt = TimeManager::GetInstance()->GetDeltaTime();

		if (KeyManager::GetInstance()->Getbutton(KeyType::W))
		{
			// -- front

			CameraManager::GetInstance()->m_cameraPos -= (CameraManager::GetInstance()->m_cameraSpeed) * CameraManager::GetInstance()->m_cameraFront * dt;
			CameraManager::GetInstance()->m_cameraPos.y = 5.0f;

			_center.x = CameraManager::GetInstance()->m_cameraPos.x;
			_center.y = 0;
			_center.z = CameraManager::GetInstance()->m_cameraPos.z;

		}
		if (KeyManager::GetInstance()->Getbutton(KeyType::S))
		{
			// ++ front

			CameraManager::GetInstance()->m_cameraPos += (CameraManager::GetInstance()->m_cameraSpeed) * CameraManager::GetInstance()->m_cameraFront * dt;
			CameraManager::GetInstance()->m_cameraPos.y = 5.0f;

			_center.x = CameraManager::GetInstance()->m_cameraPos.x;
			_center.y = 0;
			_center.z = CameraManager::GetInstance()->m_cameraPos.z;

		}

		if (KeyManager::GetInstance()->Getbutton(KeyType::A))
		{
			// ++ right

			CameraManager::GetInstance()->m_cameraPos += (CameraManager::GetInstance()->m_cameraSpeed) * cameraRight * dt;

			_center.x = CameraManager::GetInstance()->m_cameraPos.x;
			_center.y = 0;
			_center.z = CameraManager::GetInstance()->m_cameraPos.z;

		}
		if (KeyManager::GetInstance()->Getbutton(KeyType::D))
		{
			// -- right
			CameraManager::GetInstance()->m_cameraPos -= (CameraManager::GetInstance()->m_cameraSpeed) * cameraRight * dt;

			_center.x = CameraManager::GetInstance()->m_cameraPos.x;
			_center.y = 0;
			_center.z = CameraManager::GetInstance()->m_cameraPos.z;

		}

		CameraManager::GetInstance()->m_cameraSpeed = 0.0f;

		/////////////////////////////////////////////////////////////
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
	CameraManager::GetInstance()->m_cameraSpeed = 40.0f;



}