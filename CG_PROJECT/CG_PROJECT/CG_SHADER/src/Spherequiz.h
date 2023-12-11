#pragma once

#include "Object.h"
class Model;
class Locked;
enum class QuizPart
{
	UPPER = 0,
	LOWER = 1
};

class Spherequiz :public Object
{

	using Super = Object;

public:
	Spherequiz(Model& upper, Model& middle, Model& lower);
	~Spherequiz();


	void Init() override;
	void Update() override;
	void SpecialUpdate(Locked* ptr);
	void Render(Shader& shader) override;

	void MatrixUpdate();

	void OnComponentBeginOverlap(Collider* collider, Collider* other) override;
	void OnComponentEndOverlap(Collider* collider, Collider* other) override;

public:

	Model* _upper;
	Model* _lower;

	glm::mat4 _upper_mat;
	glm::mat4 _lower_mat;

	float _upper_deg = 120.0f;
	float _lower_deg = 150.0f;
	float _rot_speed = 50.0f;

	glm::mat4 _quiz_matrixs[2];
	float _quiz_degrees[2];
	float _upper_correction = 0.0f;
	float _lower_correction = 0.0f;

	QuizPart _selected = QuizPart::UPPER;

	bool _collusion = false;
	bool _solved = false;

};