#pragma once
#include "Component.h"

class BoxCollider;
class SphereCollider;
class Shader;

class Collider : public Component
{
public:

	Collider(ColliderType colliderType);
	virtual ~Collider() override;

	void Init() override;
	void Update() override;
	void Render(Shader& shader) override;

	virtual bool CheckCollision(Collider* other) ;


	ColliderType GetColliderType() { return _colliderType; }
	void SetShowDebug(bool show) { _showDebug = show; }

public:
	static bool CheckCollisionBox2Box(BoxCollider* b1, BoxCollider* b2);
	static bool CheckCollisionSphere2Box(SphereCollider* s1, BoxCollider* b2);
	static bool CheckCollisionSphere2Sphere(SphereCollider* s1, SphereCollider* s2);


protected:

	ColliderType _colliderType;
	bool _showDebug = true;
	
public:

	unordered_set<Collider*> _collisionMap;
};

