#pragma once

#include "Object.h"

class Model;

class Ghost:public Object
{

	using Super = Object;

public:
	Ghost(Model& model_body,Model& model_left_arm, Model& model_right_arm);
	~Ghost();


	void Init() override;
	void Update() override;
	void Render(Shader& shader) override;

	void MatrixUpdate();

	void OnComponentBeginOverlap(Collider* collider, Collider* other) override;
	void OnComponentEndOverlap(Collider* collider, Collider* other) override;

private:

	bool _collusion = false;


	Model* _left_arm;
	Model* _right_arm;


	glm::vec3 left_arm_center = glm::vec3(-1.51369f+0.38f, 12.708f, -0.480505f);
	glm::vec3 right_arm_center = glm::vec3(1.22144f-0.358f, 12.7469f, -0.554352f);

	/// 바디는 오브젝트에 정의되있음
	glm::mat4 _left_arm_matrix=glm::mat4(1.0f);
	glm::mat4 _right_arm_matrix= glm::mat4(1.0f);

	float degree = 0;


};

