#include "pch.h"
#include "Player.h"
#include "Object.h"
#include "Object.h"
#include "Collider.h"
#include "Model.h"
#include "Light2.h"

Player::Player(Model& model) :Object(ObjectType::PLAYER)
{
	_center = model.GetCenter();
	_size = model.GetSize();
	_first_center = _center;
	_model = &model;

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

	MatrixUpdate();


}

void Player::Render(Shader& shader)
{

	Super::Render(shader);

	/*shader.SetUniform3f("control_color", 0, 0, 0);
	shader.SetUniformMat4f("u_model", _matrix);
	_model->RenderModel(shader);*/

}

void Player::MatrixUpdate()
{
	_matrix = matrix::GetInstance()->GetTranslation(_center.x, 0,_center.z-187.80f);


}

void Player::KeyUpdate()
{
	if (KeyManager::GetInstance()->Getbutton(KeyType::W))
	{
		_center.x = CameraManager::GetInstance()->m_cameraPos.x;
		_center.z = CameraManager::GetInstance()->m_cameraPos.z;

	}

	if (KeyManager::GetInstance()->Getbutton(KeyType::S))
	{
		_center.x = CameraManager::GetInstance()->m_cameraPos.x;
		_center.z = CameraManager::GetInstance()->m_cameraPos.z;

	}

	if (KeyManager::GetInstance()->Getbutton(KeyType::A))
	{
		_center.x = CameraManager::GetInstance()->m_cameraPos.x;
		_center.z = CameraManager::GetInstance()->m_cameraPos.z;
	}

	if (KeyManager::GetInstance()->Getbutton(KeyType::D))
	{
		_center.x = CameraManager::GetInstance()->m_cameraPos.x;
		_center.z = CameraManager::GetInstance()->m_cameraPos.z;

	}
}

void Player::OnComponentBeginOverlap(Collider* collider, Collider* other)
{

	if (other->GetOwner()->GetObjectType() == ObjectType::WALL)
	{
		// 부딛힌 방향의 역방향 재이동 수행, 대각선은 아직 수정이 필요함
		auto cameraRight = glm::normalize(glm::cross(CameraManager::GetInstance()->m_cameraUp, -(CameraManager::GetInstance()->m_cameraFront)));
		float dt = TimeManager::GetInstance()->GetDeltaTime();

		if (KeyManager::GetInstance()->Getbutton(KeyType::W))
		{
			// -- front

			CameraManager::GetInstance()->m_cameraPos -= (CameraManager::GetInstance()->m_cameraSpeed) * CameraManager::GetInstance()->m_cameraFront * dt;

			_center.x = CameraManager::GetInstance()->m_cameraPos.x;
			_center.z = CameraManager::GetInstance()->m_cameraPos.z;

		}
		if (KeyManager::GetInstance()->Getbutton(KeyType::S))
		{
			// ++ front

			CameraManager::GetInstance()->m_cameraPos += (CameraManager::GetInstance()->m_cameraSpeed) * CameraManager::GetInstance()->m_cameraFront * dt;

			_center.x = CameraManager::GetInstance()->m_cameraPos.x;
			_center.z = CameraManager::GetInstance()->m_cameraPos.z;

		}

		if (KeyManager::GetInstance()->Getbutton(KeyType::A))
		{
			// ++ right

			CameraManager::GetInstance()->m_cameraPos += (CameraManager::GetInstance()->m_cameraSpeed) * cameraRight * dt;


			_center.x = CameraManager::GetInstance()->m_cameraPos.x;
			_center.z = CameraManager::GetInstance()->m_cameraPos.z;

		}
		if (KeyManager::GetInstance()->Getbutton(KeyType::D))
		{
			// -- right
			CameraManager::GetInstance()->m_cameraPos -= (CameraManager::GetInstance()->m_cameraSpeed) * cameraRight * dt;

			_center.x = CameraManager::GetInstance()->m_cameraPos.x;
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

	// 속도 원상복귀
	CameraManager::GetInstance()->m_cameraSpeed = 200.0f;



}
