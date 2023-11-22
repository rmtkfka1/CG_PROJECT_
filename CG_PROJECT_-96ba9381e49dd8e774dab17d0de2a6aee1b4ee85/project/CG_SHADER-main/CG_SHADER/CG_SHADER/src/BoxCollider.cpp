#include "pch.h"
#include "BoxCollider.h"
#include "Object.h"

BoxCollider::BoxCollider():Collider(ColliderType::Box)
{

}

BoxCollider::~BoxCollider()
{
}

void BoxCollider::Init()
{
	_center = _owner->GetCenter();
	_size = _owner->GetSize();

}

void BoxCollider::Update()
{
    _center = _owner->GetCenter();
    _size = _owner->GetSize();

}

void BoxCollider::Render(Shader& shader)
{
	
    if (_showDebug)
    {
        glLineWidth(5.0f);

        glBegin(GL_LINES); // 라인 그리기 시작

        glVertex3f(_center.x - _size.x / 2, _center.y + _size.y / 2, _center.z - _size.z / 2);
        glVertex3f(_center.x + _size.x / 2, _center.y + _size.y / 2, _center.z - _size.z / 2);

        glVertex3f(_center.x - _size.x / 2, _center.y + _size.y / 2, _center.z + _size.z / 2);
        glVertex3f(_center.x + _size.x / 2, _center.y + _size.y / 2, _center.z + _size.z / 2);

        glVertex3f(_center.x - _size.x / 2, _center.y + _size.y / 2, _center.z - _size.z / 2);
        glVertex3f(_center.x - _size.x / 2, _center.y + _size.y / 2, _center.z + _size.z / 2);

        glVertex3f(_center.x + _size.x / 2, _center.y + _size.y / 2, _center.z - _size.z / 2);
        glVertex3f(_center.x + _size.x / 2, _center.y + _size.y / 2, _center.z + _size.z / 2);

        glVertex3f(_center.x - _size.x / 2, _center.y - _size.y / 2, _center.z - _size.z / 2);
        glVertex3f(_center.x - _size.x / 2, _center.y + _size.y / 2, _center.z - _size.z / 2);

        glVertex3f(_center.x - _size.x / 2, _center.y - _size.y / 2, _center.z + _size.z / 2);
        glVertex3f(_center.x - _size.x / 2, _center.y + _size.y / 2, _center.z + _size.z / 2);

        glVertex3f(_center.x + _size.x / 2, _center.y - _size.y / 2, _center.z + _size.z / 2);
        glVertex3f(_center.x + _size.x / 2, _center.y + _size.y / 2, _center.z + _size.z / 2);

        glVertex3f(_center.x + _size.x / 2, _center.y - _size.y / 2, _center.z - _size.z / 2);
        glVertex3f(_center.x + _size.x / 2, _center.y + _size.y / 2, _center.z - _size.z / 2);

        glVertex3f(_center.x - _size.x / 2, _center.y - _size.y / 2, _center.z - _size.z / 2);
        glVertex3f(_center.x + _size.x / 2, _center.y - _size.y / 2, _center.z - _size.z / 2);

        glVertex3f(_center.x - _size.x / 2, _center.y - _size.y / 2, _center.z + _size.z / 2);
        glVertex3f(_center.x + _size.x / 2, _center.y - _size.y / 2, _center.z + _size.z / 2);

        glVertex3f(_center.x - _size.x / 2, _center.y - _size.y / 2, _center.z - _size.z / 2);
        glVertex3f(_center.x - _size.x / 2, _center.y - _size.y / 2, _center.z + _size.z / 2);

        glVertex3f(_center.x + _size.x / 2, _center.y - _size.y / 2, _center.z - _size.z / 2);
        glVertex3f(_center.x + _size.x / 2, _center.y - _size.y / 2, _center.z + _size.z / 2);

        glEnd(); // 라인 그리기 종료

    }

}

bool BoxCollider::CheckCollision(Collider* other)
{
    switch (other->GetColliderType())
    {
    case ColliderType::Box:
        return CheckCollisionBox2Box(this, static_cast<BoxCollider*>(other));
    case ColliderType::Sphere:
        return false;
    }

    return false;

}
