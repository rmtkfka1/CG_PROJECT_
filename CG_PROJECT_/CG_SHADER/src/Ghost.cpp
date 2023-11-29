#include "pch.h"
#include "Ghost.h"



Ghost::Ghost(Model& model_body, Model& model_left_arm, Model& model_right_arm):Object(ObjectType::GHOST)
{

	_center = model_body.GetCenter();
	_size = model_body.GetSize();

	_first_center = _center;
	_model = &model_body;

	_left_arm = &model_left_arm;
	_right_arm = &model_right_arm;

}

Ghost::~Ghost()
{

}

void Ghost::Init()
{
	Super::Init();
}

void Ghost::Update()
{
	Super::Update();


	if (KeyManager::GetInstance()->Getbutton(KeyType::SpaceBar))
	{
		degree += 5.0f;
	}

	if (KeyManager::GetInstance()->Getbutton(KeyType::N))
	{
		degree -= 5.0f;
	}


	MatrixUpdate();

}

void Ghost::Render(Shader& shader)
{
	Super::Render(shader);

	shader.SetUniform3f("control_color", 0, 0, 0);
	shader.SetUniformMat4f("u_model", _matrix); // 몸통 바디 그려주는 부분
	_model->RenderModel(shader);

	shader.SetUniformMat4f("u_model", _left_arm_matrix); // 왼쪽팔그려주는 부분
	_left_arm->RenderModel(shader);

	shader.SetUniformMat4f("u_model", _right_arm_matrix); // 왼쪽팔그려주는 부분
	_right_arm->RenderModel(shader);

}

void Ghost::MatrixUpdate()
{

	{
		auto trans1 = matrix::GetInstance()->GetTranslation(-left_arm_center.x, -left_arm_center.y, -left_arm_center.z);
		auto rotate = matrix::GetInstance()->GetRotate(degree, 0, 1, 0);
		auto trans2 = matrix::GetInstance()->GetTranslation(left_arm_center.x, left_arm_center.y, left_arm_center.z);

		auto result = trans2 * rotate * trans1;
		_left_arm_matrix = result;
	}

	{
		auto trans1 = matrix::GetInstance()->GetTranslation(-right_arm_center.x, -right_arm_center.y, -right_arm_center.z);
		auto rotate = matrix::GetInstance()->GetRotate(degree, 0, 1, 0);
		auto trans2 = matrix::GetInstance()->GetTranslation(right_arm_center.x, right_arm_center.y, right_arm_center.z);

		auto result = trans2 * rotate * trans1;
		_right_arm_matrix = result;
	}


}

void Ghost::OnComponentBeginOverlap(Collider* collider, Collider* other)
{
}

void Ghost::OnComponentEndOverlap(Collider* collider, Collider* other)
{
}
