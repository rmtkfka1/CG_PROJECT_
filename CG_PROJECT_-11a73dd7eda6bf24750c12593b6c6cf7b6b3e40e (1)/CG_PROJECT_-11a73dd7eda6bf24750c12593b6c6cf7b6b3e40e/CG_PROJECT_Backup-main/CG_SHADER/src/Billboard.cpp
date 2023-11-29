#include "pch.h"
#include "Billboard.h"

Billboard::Billboard(Model& model) :Object(ObjectType::BILLBOARD)
{
	_center = model.GetCenter();
	_size = model.GetSize();
	_first_center = _center;
	_model = &model;
}

Billboard::~Billboard()
{
}

void Billboard::Init()
{
	Super::Init();
}

void Billboard::Update()
{
	Super::Update();
	// ���⼭ �˸°� �����ָ� ��...��?

	m_matrix = glm::inverse(GET_SINGLE(CameraManager)->GetMatrix());

	m_matrix[0][3] = 0.0f;
	m_matrix[1][3] = 0.0f;
	m_matrix[2][3] = 0.0f;
	m_matrix[3][0] = 0.0f;
	m_matrix[3][1] = 0.0f;
	m_matrix[3][2] = 0.0f;
	m_matrix[3][3] = 1.0f;

	m_matrix = m_matrix * GET_SINGLE(matrix)->GetScale(m_size_x, m_size_y, 1.0f) * GET_SINGLE(matrix)->GetTranslation(0.0f, 0.5f, 0.0f);
}

void Billboard::Render(Shader& shader)
{
	Super::Render(shader);

	shader.SetUniform3f("control_color", 0, 0, 0);
	shader.SetUniformMat4f("u_model", m_matrix);
	_model->RenderModel(shader);


}

void Billboard::SetSize(float x, float y)
{
	m_size_x = x;
	m_size_y = y;
	// x������ �翷���� �ø��°� �߽����� �ٲ����� ����
	// y������ ���Ʒ��� �ø��°� �߽����� �ٲ�(���� �÷����)

}

void Billboard::SetPosition(float x, float y, float z)
{
}

void Billboard::OnComponentBeginOverlap(Collider* collider, Collider* other)
{
	_collusion = true;

	_debug_color.x = 0;
	_debug_color.y = 1;
	_debug_color.z = 0;
}

void Billboard::OnComponentEndOverlap(Collider* collider, Collider* other)
{
	_collusion = false;

	_debug_color.x = 1;
	_debug_color.y = 0;
	_debug_color.z = 0;
}
