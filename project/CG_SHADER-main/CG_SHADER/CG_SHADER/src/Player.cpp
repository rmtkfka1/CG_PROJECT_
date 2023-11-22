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
	shader.SetUniformMat4f("u_model", matrix::GetInstance()->GetTranslation(this->GetCenter_x(), this->GetCenter_y(), this->GetCenter_z()));
	model.RenderModel(shader);

	//	cout << "curPos Rendered: " << _center.x << ", " << _center.z << endl;
	//	cout << "camPos Rendered: " << GET_SINGLE(CameraManager)->m_cameraPos.x << ", " << GET_SINGLE(CameraManager)->m_cameraPos.z << endl;
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
	/*	"여기서 충돌처리 해주면 됨 벽이랑 초록 불들어왓을때를 의미하는거임"*/
		//	glm::vec3 inverseMove = CameraManager::GetInstance()->m_cameraLastPos - CameraManager::GetInstance()->m_cameraPos;
		//	
		//	
		//	
		//	CameraManager::GetInstance()->m_cameraPos += inverseMove;
		//	
		//	_center.x = CameraManager::GetInstance()->m_cameraPos.x;
		//	_center.y = 0;
		//	_center.z = CameraManager::GetInstance()->m_cameraPos.z;
		//	
		//	CameraManager::GetInstance()->m_cameraSpeed = 0.0f;


		auto cameraRight = glm::normalize(glm::cross(CameraManager::GetInstance()->m_cameraUp, -(CameraManager::GetInstance()->m_cameraFront)));
		auto cameraFrontDir = glm::normalize(glm::cross(CameraManager::GetInstance()->m_cameraUp, cameraRight));
		float dt = TimeManager::GetInstance()->GetDeltaTime();
		
		if (KeyManager::GetInstance()->Getbutton(KeyType::W))
		{
			// -- front
		
			CameraManager::GetInstance()->m_cameraPos -= (CameraManager::GetInstance()->m_cameraSpeed) * cameraFrontDir * dt;
			_center.x = CameraManager::GetInstance()->m_cameraPos.x;
			_center.y = 0;
			_center.z = CameraManager::GetInstance()->m_cameraPos.z;
		
			if (KeyManager::GetInstance()->Getbutton(KeyType::A))
			{
				CameraManager::GetInstance()->m_cameraPos += (CameraManager::GetInstance()->m_cameraSpeed) * cameraRight * dt;
		
				_center.x = CameraManager::GetInstance()->m_cameraPos.x;
				_center.y = 0;
				_center.z = CameraManager::GetInstance()->m_cameraPos.z;
			}
			if (KeyManager::GetInstance()->Getbutton(KeyType::D))
			{
				CameraManager::GetInstance()->m_cameraPos -= (CameraManager::GetInstance()->m_cameraSpeed) * cameraRight * dt;
		
				_center.x = CameraManager::GetInstance()->m_cameraPos.x;
				_center.y = 0;
				_center.z = CameraManager::GetInstance()->m_cameraPos.z;
			}
		}
		if (KeyManager::GetInstance()->Getbutton(KeyType::S))
		{
			// ++ front
		
			CameraManager::GetInstance()->m_cameraPos += (CameraManager::GetInstance()->m_cameraSpeed) * cameraFrontDir * dt;
		
			_center.x = CameraManager::GetInstance()->m_cameraPos.x;
			_center.y = 0;
			_center.z = CameraManager::GetInstance()->m_cameraPos.z;
		
			if (KeyManager::GetInstance()->Getbutton(KeyType::A))
			{
				CameraManager::GetInstance()->m_cameraPos += (CameraManager::GetInstance()->m_cameraSpeed) * cameraRight * dt;
		
				_center.x = CameraManager::GetInstance()->m_cameraPos.x;
				_center.y = 0;
				_center.z = CameraManager::GetInstance()->m_cameraPos.z;
			}
			if (KeyManager::GetInstance()->Getbutton(KeyType::D))
			{
				CameraManager::GetInstance()->m_cameraPos -= (CameraManager::GetInstance()->m_cameraSpeed) * cameraRight * dt;
		
				_center.x = CameraManager::GetInstance()->m_cameraPos.x;
				_center.y = 0;
				_center.z = CameraManager::GetInstance()->m_cameraPos.z;
			}
		}
		
		if (KeyManager::GetInstance()->Getbutton(KeyType::A))
		{
			// ++ right

			CameraManager::GetInstance()->m_cameraPos += (CameraManager::GetInstance()->m_cameraSpeed) * cameraRight * dt;
		
			_center.x = CameraManager::GetInstance()->m_cameraPos.x;
			_center.y = 0;
			_center.z = CameraManager::GetInstance()->m_cameraPos.z;
		
			if (KeyManager::GetInstance()->Getbutton(KeyType::W))
			{
				CameraManager::GetInstance()->m_cameraPos -= (CameraManager::GetInstance()->m_cameraSpeed) * cameraFrontDir * dt;
		
				_center.x = CameraManager::GetInstance()->m_cameraPos.x;
				_center.y = 0;
				_center.z = CameraManager::GetInstance()->m_cameraPos.z;
			}
			if (KeyManager::GetInstance()->Getbutton(KeyType::S))
			{
				CameraManager::GetInstance()->m_cameraPos += (CameraManager::GetInstance()->m_cameraSpeed) * cameraFrontDir * dt;
		
				_center.x = CameraManager::GetInstance()->m_cameraPos.x;
				_center.y = 0;
				_center.z = CameraManager::GetInstance()->m_cameraPos.z;
			}
		}
		if (KeyManager::GetInstance()->Getbutton(KeyType::D))
		{
			// -- right
			CameraManager::GetInstance()->m_cameraPos -= (CameraManager::GetInstance()->m_cameraSpeed) * cameraRight * dt;
		
			_center.x = CameraManager::GetInstance()->m_cameraPos.x;
			_center.y = 0;
			_center.z = CameraManager::GetInstance()->m_cameraPos.z;
		
			if (KeyManager::GetInstance()->Getbutton(KeyType::W))
			{
				CameraManager::GetInstance()->m_cameraPos -= (CameraManager::GetInstance()->m_cameraSpeed) * cameraFrontDir * dt;
		
				_center.x = CameraManager::GetInstance()->m_cameraPos.x;
				_center.y = 0;
				_center.z = CameraManager::GetInstance()->m_cameraPos.z;
			}
			if (KeyManager::GetInstance()->Getbutton(KeyType::S))
			{
				CameraManager::GetInstance()->m_cameraPos += (CameraManager::GetInstance()->m_cameraSpeed) * cameraFrontDir * dt;
		
				_center.x = CameraManager::GetInstance()->m_cameraPos.x;
				_center.y = 0;
				_center.z = CameraManager::GetInstance()->m_cameraPos.z;
			}
		}
		
		CameraManager::GetInstance()->m_cameraSpeed = 0.0f;
	
	/////////////////////////////////////////////////////////////
	}
	

	_debug_color.x = 0;
	_debug_color.y = 1;
	_debug_color.z = 0;




}

void Player::OnComponentWhileOverlap(Collider* collider, Collider* other)
{
	
	_debug_color.x = 0;
	_debug_color.y = 0;
	_debug_color.z = 1;

}

void Player::OnComponentEndOverlap(Collider* collider, Collider* other)
{
	

	_debug_color.x = 1;
	_debug_color.y = 0;
	_debug_color.z = 0;


	CameraManager::GetInstance()->m_cameraSpeed = 40.0f;

}
