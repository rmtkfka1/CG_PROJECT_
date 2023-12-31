#include "pch.h"
#include "Cat.h"

Cat::Cat(Model& model) :Object(ObjectType::CAT)
{
	_center = model.GetCenter();
	_size = model.GetSize();
	_first_center = _center;
	_model = &model;
}

Cat::~Cat()
{
	if (_model != nullptr)
	{
		delete _model;
		_model = nullptr;
	}

}


void Cat::Init()
{
	Super::Init();
}

void Cat::Update()
{

	Super::Update();

}

void Cat::Render(Shader& shader)
{

	Super::Render(shader);

	shader.SetUniform3f("control_color", 0, 0, 0);
	shader.SetUniformMat4f("u_model", _matrix);
	_model->RenderModel(shader);

}

void Cat::OnComponentBeginOverlap(Collider* collider, Collider* other)
{
	if (other->GetOwner()->GetObjectType() == ObjectType::PLAYER)
	{

		SoundManager::GetInstance()->Play(TELEPORT);

		SoundManager::GetInstance()->endsong = true;
		SoundManager::GetInstance()->Stop(BACKGROUND);

		GET_SINGLE(CameraManager)->m_cameraFront = { -1,0,0};
		GET_SINGLE(CameraManager)->m_cameraPos.x = 0.0f;
		GET_SINGLE(CameraManager)->m_cameraPos.z = -900.0f;

		SoundManager::GetInstance()->Play(ENDINGSONG);
	}
}

void Cat::OnComponentEndOverlap(Collider* collider, Collider* other)
{
}
