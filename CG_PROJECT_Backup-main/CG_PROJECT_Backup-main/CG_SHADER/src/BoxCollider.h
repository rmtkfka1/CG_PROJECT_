#pragma once

#include "Collider.h"

class Shader;

class BoxCollider : public Collider
{


public:
	BoxCollider();
	virtual ~BoxCollider() override;

	virtual void Init() override;
	virtual void Update() override;
	virtual void Render(Shader& shader) override;

	virtual bool CheckCollision(Collider* other);

	glm::vec3 GetSize() { return _size; }
	void SetSize(glm::vec3 size) { _size = size; }

	glm::vec3 GetCenter() { return _center; }

private:

	glm::vec3 _center;
	glm::vec3 _size;
};

