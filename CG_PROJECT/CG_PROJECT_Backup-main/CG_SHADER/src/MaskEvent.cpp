#include "pch.h"
#include "MaskEvent.h"
#include "BoxCollider.h"
#include "DeadBody.h"
MaskEvent::MaskEvent(Model& model) :Object(ObjectType::MASKEVENT)
{
	_center = model.GetCenter();
	_size = model.GetSize();
	_first_center = _center;
	_model = &model;

}

MaskEvent::~MaskEvent()
{


}

void MaskEvent::Init()
{
	Super::Init();
}

void MaskEvent::Update()
{
	Super::Update();

}





void MaskEvent::Render(Shader& shader)
{

	Super::Render(shader);


	shader.SetUniform3f("control_color", 0, 0, 0);
	shader.SetUniformMat4f("u_model", _matrix);
	_model->RenderModel(shader);

}

void MaskEvent::OnComponentBeginOverlap(Collider* collider, Collider* other)
{
	if (other->GetOwner()->GetObjectType() == ObjectType::PLAYER)
	{
		_collison = true;
	}
}

void MaskEvent::OnComponentEndOverlap(Collider* collider, Collider* other)
{
}

