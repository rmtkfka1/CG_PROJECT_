#include "pch.h"
#include "Wall.h"
#include "Model.h"

Wall::Wall(Model& model) :Object(ObjectType::WALL)
{
	_center = model.GetCenter();
	_size = model.GetSize();
	_first_center = _center;
	_model = &model;

}

Wall::~Wall()
{

}

void Wall::Init()
{
	Super::Init();
}

void Wall::Update()
{
	Super::Update();




}

void Wall::Render(Shader& shader)
{


	//shader.SetUniform3f("control_color", _debug_color.x, _debug_color.y, _debug_color.z);
	//auto simple = glm::mat4(1.0f);
	//shader.SetUniformMat4f("u_model", simple);
	//Super::Render(shader, model, matrix);


	shader.SetUniform3f("control_color", 0, 0, 0);
	shader.SetUniformMat4f("u_model", _matrix);
	_model->RenderModel(shader);


}

void Wall::OnComponentBeginOverlap(Collider* collider, Collider* other)
{
	_collusion = true;

	_debug_color.x = 0;
	_debug_color.y = 1;
	_debug_color.z = 0;
}

void Wall::OnComponentEndOverlap(Collider* collider, Collider* other)
{
	_collusion = false;

	_debug_color.x = 1;
	_debug_color.y = 0;
	_debug_color.z = 0;
}
