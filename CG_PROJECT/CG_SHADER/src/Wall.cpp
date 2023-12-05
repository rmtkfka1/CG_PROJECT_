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

	if (_model != nullptr)
	{
		delete _model;
		_model = nullptr;
	}

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


	Super::Render(shader);


	shader.SetUniform3f("control_color", 0, 0, 0);
	shader.SetUniformMat4f("u_model", _matrix);
	_model->RenderModel(shader);


}

void Wall::OnComponentBeginOverlap(Collider* collider, Collider* other)
{

	_collusion = true;

}

void Wall::OnComponentEndOverlap(Collider* collider, Collider* other)
{
	_collusion = false;


}
