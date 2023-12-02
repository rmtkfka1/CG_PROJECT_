#include "pch.h"
#include "Object.h"
#include "Component.h"
#include "Collider.h"

Object::Object(ObjectType type)
{
	_type = type;

}


Object::~Object()
{
	for (int i = 0; i < v_component.size(); ++i)
	{
		delete v_component[i];
		v_component[i] = nullptr;
	}

	v_component.clear();
}

void Object::Init()
{
	for (Component* component : v_component)
	{
		component->Init();
	}

}

void Object::Update()
{
	for (Component* component : v_component)
	{
		component->Update();
	}

	if (KeyManager::GetInstance()->GetbuttonDown(KeyType::ONE))
	{
		
	}
}

void Object::Render(Shader& shader)
{

	
	shader.SetUniform3f("control_color", _debug_color.x, _debug_color.y, _debug_color.z);
	auto simple = glm::mat4(1.0f);
	shader.SetUniformMat4f("u_model", simple);
	

	for (Component* component : v_component)
	{
		component->Render(shader);
	}

}


void Object::SetRotate(float radian, float x, float y, float z)
{
	
	
	auto trans1 = glm::translate(glm::mat4(1.0f), glm::vec3(-_center.x, -_center.y, -_center.z)); // 원점으로 이동시킴

	auto rotate = glm::rotate(glm::mat4(1.0f), glm::radians(radian), glm::vec3(x, y, z)); //자전 시킴

	auto trans2 = glm::translate(glm::mat4(1.0f), glm::vec3(_center.x, _center.y, _center.z)); // 제자리로 이동시킴

	auto result = trans2 * rotate * trans1;


	glm::vec4 temp = glm::vec4(_size, 1.0f);
	glm::vec4 rotatedSize = result * temp;

	_size = glm::vec3(rotatedSize);

	_matrix = result;

	
}

glm::mat4 Object::GetScale(float dx,float dy ,float dz)
{
	
	auto trans1 = glm::translate(glm::mat4(1.0f), glm::vec3(-_center.x, -_center.y, -_center.z)); // 원점으로 이동시킴

	auto resize = glm::scale(glm::mat4(1.0f), glm::vec3(dx, dy, dz));

	auto trans2 = glm::translate(glm::mat4(1.0f), glm::vec3(_center.x, _center.y, _center.z)); // 제자리로 이동시킴

	auto result = trans2 * resize * trans1;

	return result;

}

void Object::SetTransPose(float dx, float dy, float dz)
{

	_matrix = glm::translate(glm::mat4(1.0f), glm::vec3(dx, dy, dz)); // 원점으로 이동시킴

	_center.x = _first_center.x + dx;
	_center.y = _first_center.y + dy;
	_center.z = _first_center.z + dz;

}

void Object::PrintInfo()
{
	cout << "center :" << _center.x << "," << _center.y << "," << _center.z << endl;
	cout << "size   :" << _size.x << "," << _size.y << "," << _size.z << endl;
}

void Object::AddComponent(Component* component)
{
	if (component == nullptr)
		return;

	component->SetOwner(this);
	v_component.push_back(component);

}

void Object::RemoveComponent(Component* component)
{

	auto findIt = std::find(v_component.begin(), v_component.end(), component);

	if (findIt == v_component.end())
		return;

	v_component.erase(findIt);
}

void Object::OnComponentBeginOverlap(Collider* collider, Collider* other)
{

	_debug_color.x = 1;
	_debug_color.y = 0;
	_debug_color.z = 0;

}

void Object::OnComponentEndOverlap(Collider* collider, Collider* other)
{
	_debug_color.x = 0;
	_debug_color.y = 0;
	_debug_color.z = 1;

}


