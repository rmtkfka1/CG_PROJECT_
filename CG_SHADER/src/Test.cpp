#include "pch.h"
#include "Test.h"
#include "Model.h"
#include "BoxCollider.h"
Test::Test(Model& model) :Object(ObjectType::TEST)
{
	_center = model.GetCenter();
	_size = model.GetSize() + glm::vec3(10,10,10);
	_first_center = _center;

}

Test::~Test()
{


}

void Test::Init()
{
	Super::Init();


}

void Test::Update()
{
	Super::Update();

}

void Test::Render(Shader& shader, Model& model, glm::mat4 matrix)
{


	shader.SetUniform3f("control_color", _debug_color.x, _debug_color.y, _debug_color.z);
	auto simple = glm::mat4(1.0f);
	shader.SetUniformMat4f("u_model", simple);
	Super::Render(shader, model, matrix);


	shader.SetUniform3f("control_color", 0, 0, 0);
	shader.SetUniformMat4f("u_model", matrix);
	model.RenderModel(shader);



}

void Test::OnComponentBeginOverlap(Collider* collider, Collider* other)
{


	if (other->GetOwner()->GetObjectType() == ObjectType::PLAYER)
	{
		_collusion = true;
	}






	_debug_color.x = 0;
	_debug_color.y = 1;
	_debug_color.z = 0;




}

void Test::OnComponentEndOverlap(Collider* collider, Collider* other)
{

	_collusion = false;

	_debug_color.x = 1;
	_debug_color.y = 0;
	_debug_color.z = 0;



}
