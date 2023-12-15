#include "pch.h"
#include "Spherequiz.h"
#include "Locked.h"

Spherequiz::Spherequiz(Model& upper, Model& middle, Model& lower) :Object(ObjectType::SPHEREQUIZ)
{
	_center = middle.GetCenter();
	_size.x = middle.GetSize().x + 20.0f;
	_size.y = middle.GetSize().y;
	_size.z = middle.GetSize().z + 20.0f;

	_first_center = _center;
	_model = &middle;

	_upper = &upper;
	_lower = &lower;

	_quiz_degrees[0] = _upper_deg;
	_quiz_degrees[1] = _lower_deg;


	MatrixUpdate();

}

Spherequiz::~Spherequiz()
{
}

void Spherequiz::Init()
{
	Super::Init();

}

void Spherequiz::Update()
{




}

void Spherequiz::SpecialUpdate(Locked* ptr)
{
	Super::Update();

	_upper_correction = fmod(_quiz_degrees[0], 360.0f);
	_lower_correction = fmod(_quiz_degrees[1], 360.0f);

	if (_collusion)
	{
		if (_solved == false)
		{
			if (KeyManager::GetInstance()->Getbutton(KeyType::ONE))
			{
				_selected = QuizPart::UPPER;
			}

			if (KeyManager::GetInstance()->Getbutton(KeyType::TWO))
			{
				_selected = QuizPart::LOWER;
			}

			if (KeyManager::GetInstance()->Getbutton(KeyType::T))
			{
				_quiz_degrees[static_cast<int>(_selected)] += _rot_speed * GET_SINGLE(TimeManager)->GetDeltaTime();
				MatrixUpdate();

				SoundManager::GetInstance()->Play(SWAP);
			}

		}


		if (((_upper_correction >= 360.0 - 1.0f) || (_upper_correction <= 1.0f)) &&
			((_lower_correction >= 360.0 - 1.0f) || (_lower_correction <= 1.0f)))
		{
			_solved = true;
		}

		if (_solved)
		{
			ptr->_locked = false;
		}

	}
}

void Spherequiz::Render(Shader& shader)
{
	Super::Render(shader);

	shader.SetUniform3f("control_color", 0, 0, 0);
	shader.SetUniformMat4f("u_model", _matrix); // Áß°£ºÎ
	_model->RenderModel(shader);

	shader.SetUniformMat4f("u_model", _quiz_matrixs[0] * _matrix); // À­ºÎºÐ
	_upper->RenderModel(shader);

	shader.SetUniformMat4f("u_model", _quiz_matrixs[1] * _matrix); // ¾Æ·§ºÎºÐ
	_lower->RenderModel(shader);

}

void Spherequiz::MatrixUpdate()
{
	glm::mat4 _upper_t1 = GET_SINGLE(matrix)->GetTranslation(-_upper->GetCenter().x, -_upper->GetCenter().y, -_upper->GetCenter().z);
	glm::mat4 _upper_r = GET_SINGLE(matrix)->GetRotate(_quiz_degrees[0], 0.0f, 1.0f, 0.0f);
	glm::mat4 _upper_t2 = GET_SINGLE(matrix)->GetTranslation(_upper->GetCenter().x, _upper->GetCenter().y, _upper->GetCenter().z);
	_quiz_matrixs[0] = _upper_t2 * _upper_r * _upper_t1;

	glm::mat4 _lower_t1 = GET_SINGLE(matrix)->GetTranslation(-_lower->GetCenter().x, -_lower->GetCenter().y, -_lower->GetCenter().z);
	glm::mat4 _lower_r = GET_SINGLE(matrix)->GetRotate(_quiz_degrees[1], 0.0f, 1.0f, 0.0f);
	glm::mat4 _lower_t2 = GET_SINGLE(matrix)->GetTranslation(_lower->GetCenter().x, _lower->GetCenter().y, _lower->GetCenter().z);
	_quiz_matrixs[1] = _lower_t2 * _lower_r * _lower_t1;

}

void Spherequiz::OnComponentBeginOverlap(Collider* collider, Collider* other)
{
	if (other->GetOwner()->GetObjectType() == ObjectType::PLAYER)
	{

		_collusion = true;


	}
}

void Spherequiz::OnComponentEndOverlap(Collider* collider, Collider* other)
{
	if (other->GetOwner()->GetObjectType() == ObjectType::PLAYER)
	{

		_collusion = false;


	}
}