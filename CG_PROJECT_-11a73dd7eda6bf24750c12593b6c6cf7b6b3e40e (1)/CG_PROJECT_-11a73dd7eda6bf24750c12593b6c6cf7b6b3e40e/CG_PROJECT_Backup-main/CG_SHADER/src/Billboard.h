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

	// 사이즈 조절
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

// 기본적으로 빌보드에 쓸려고 만든 평면은 1*1 사이즈에 가로로 서있음
// 필요할때 크기를 조절해서 사용하고자 하는데 문제는 AABB
// 어차피 단순한 평면이니까 그냥 조절시키는것도 나쁘지않을듯?

//	아래는 게임수학 chapter7에 설명된 빌보드
//	스크린에 정렬된 빌보드 Screen - aligned billboard
//	카메라 공간에 미리 정의된 4개 벡터{ p1, p2, p3, p4 }.
//	뷰 변환 행렬 Mview 의 역행렬에서 회전 변환(왼쪽 위 3x3 부분 행렬) 적용
//	시뮬레이션에 계산한 파티클의 월드 공간 위치 pw 더함
//	GS는 월드 공간 위치 p’’을 계산하고 이를 클립공간으로 변환