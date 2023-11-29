#pragma once

class Model;
#include "Object.h"

class Billboard : public Object
{
	using Super = Object;

public:
	Billboard(Model& model);
	~Billboard();

	void Init() override;
	void Update() override;
	void Render(Shader& shader) override;

	// ������ ����
	void SetSize(float x, float y);
	void SetPosition(float x, float y, float z);

	void OnComponentBeginOverlap(Collider* collider, Collider* other) override;
	void OnComponentEndOverlap(Collider* collider, Collider* other) override;

public:

	bool _collusion = false;
	glm::mat4 m_matrix = glm::mat4(1.0f);
	float m_size_x = 1.0f;
	float m_size_y = 1.0f;

};

// �⺻������ �����忡 ������ ���� ����� 1*1 ����� ���η� ������
// �ʿ��Ҷ� ũ�⸦ �����ؼ� ����ϰ��� �ϴµ� ������ AABB
// ������ �ܼ��� ����̴ϱ� �׳� ������Ű�°͵� ������������?

//	�Ʒ��� ���Ӽ��� chapter7�� ����� ������
//	��ũ���� ���ĵ� ������ Screen - aligned billboard
//	ī�޶� ������ �̸� ���ǵ� 4�� ����{ p1, p2, p3, p4 }.
//	�� ��ȯ ��� Mview �� ����Ŀ��� ȸ�� ��ȯ(���� �� 3x3 �κ� ���) ����
//	�ùķ��̼ǿ� ����� ��ƼŬ�� ���� ���� ��ġ pw ����
//	GS�� ���� ���� ��ġ p������ ����ϰ� �̸� Ŭ���������� ��ȯ