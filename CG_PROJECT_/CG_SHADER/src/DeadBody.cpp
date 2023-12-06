#include "pch.h"
#include "DeadBody.h"
#include "FakeFlash.h"
DeadBody::DeadBody(Model& model):Object(ObjectType::DEADBODY)
{
	_center = model.GetCenter();
	_size.x = model.GetSize().x;
	_size.z = model.GetSize().z;
	_size.y = model.GetSize().y;
	_first_center = _center;
	_model = &model;

}

DeadBody::~DeadBody()
{
	if (_model != nullptr)
	{
		delete _model;
		_model = nullptr;
	}
}

void DeadBody::Init()
{
	Super::Init();
}

void DeadBody::Update()
{
	Super::Update();


}



void DeadBody::SpecialRender(Shader& shader, FakeFlash* ptr)
{

	if (ptr->draw==false)
	{
		Super::Render(shader);


		shader.SetUniform3f("control_color", 0, 0, 0);
		shader.SetUniformMat4f("u_model", _matrix);
		_model->RenderModel(shader);
	}
}

