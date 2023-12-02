#include "pch.h"
#include "MaskEvent.h"
#include "BoxCollider.h"
#include "DeadBody.h"
Event::Event(Model& model) :Object(ObjectType::MASKEVENT)
{
	_center = model.GetCenter();
	_size = model.GetSize();
	_first_center = _center;
	_model = &model;

}

Event::~Event()
{


}

void Event::Init()
{
	Super::Init();
}

void Event::Update()
{
	Super::Update();

}



void Event::Render(Shader& shader)
{

	Super::Render(shader);


	shader.SetUniform3f("control_color", 0, 0, 0);
	shader.SetUniformMat4f("u_model", _matrix);
	_model->RenderModel(shader);

}

void Event::OnComponentBeginOverlap(Collider* collider, Collider* other)
{
	if (other->GetOwner()->GetObjectType() == ObjectType::PLAYER)
	{
		mask_collison = true;
		room2_box_collison = true;
	}
}

void Event::OnComponentEndOverlap(Collider* collider, Collider* other)
{

	if (other->GetOwner()->GetObjectType() == ObjectType::PLAYER)
	{
		room2_box_collison = false;
	}
}
