#include "pch.h"
#include "Collider.h"
#include "BoxCollider.h"

Collider::Collider(ColliderType colliderType)
{
}

Collider::~Collider()
{
}

void Collider::Init()
{
}

void Collider::Update()
{
}

void Collider::Render(Shader& shader)
{


}

bool Collider::CheckCollision(Collider* other)
{
	return false;  //virtual 
}

bool Collider::CheckCollisionBox2Box(BoxCollider* b1, BoxCollider* b2)
{


	float b1_left = b1->GetCenter().x - b1->GetSize().x/2;
	float b1_right = b1->GetCenter().x + b1->GetSize().x / 2;

	float b1_top = b1->GetCenter().y + b1->GetSize().y/ 2;
	float b1_bottom = b1->GetCenter().y - b1->GetSize().y / 2;

	float b1_front = b1->GetCenter().z + b1->GetSize().z / 2;
	float b1_back = b1->GetCenter().z - b1->GetSize().z / 2;

	/////////////////////////////////////////////////////////////
	float b2_left = b2->GetCenter().x - b2->GetSize().x / 2;
	float b2_right = b2->GetCenter().x + b2->GetSize().x / 2;

	float b2_top = b2->GetCenter().y + b2->GetSize().y / 2;
	float b2_bottom = b2->GetCenter().y - b2->GetSize().y / 2;

	float b2_front = b2->GetCenter().z + b2->GetSize().z / 2;
	float b2_back = b2->GetCenter().z - b2->GetSize().z / 2;

	if (b1_left <= b2_right && b1_right >= b2_left &&
		b1_bottom <= b2_top && b1_top >= b2_bottom &&
		b1_back <= b2_front && b1_front >= b2_back)
	{

		return true;
	}

	return false;
}

bool Collider::CheckCollisionSphere2Box(SphereCollider* s1, BoxCollider* b2)
{
	return false;
}

bool Collider::CheckCollisionSphere2Sphere(SphereCollider* s1, SphereCollider* s2)
{
	return false;
}
