#include "pch.h"
#include "Bottom.h"

Bottom::Bottom(Model& model):Object(ObjectType::PlANE)
{
	_center = model.GetCenter();
	_size = model.GetSize();
	_first_center = _center;

}

Bottom::~Bottom()
{



}

void Bottom::Init()
{
	Super::Init();
}

void Bottom::Update()
{
	Super::Update();
}

void Bottom::Render(Shader& shader, Model& model)
{
	shader.SetUniform3f("control_color", _debug_color.x, _debug_color.y, _debug_color.z);
	auto simple = glm::mat4(1.0f);
	shader.SetUniformMat4f("u_model", simple);
	Super::Render(shader,model);


	shader.SetUniform3f("control_color", 0, 0, 0);
	shader.SetUniformMat4f("u_model", _matrix);
	model.RenderModel(shader);


}

void Bottom::OnComponentBeginOverlap(Collider* collider, Collider* other)
{
}

void Bottom::OnComponentEndOverlap(Collider* collider, Collider* other)
{
}
