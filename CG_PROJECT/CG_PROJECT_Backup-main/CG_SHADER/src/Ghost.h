#pragma once

#include "Object.h"


class Model;

class Ghost :public Object
{

	using Super = Object;

public:
	Ghost(Model& model_body, Model& model_left_arm, Model& model_right_arm);
	~Ghost();


	void Init() override;
	void Update() override;
	void Render(Shader& shader) override;

	void MatrixUpdate();
	void SetPosition(float x, float z);

	void OnComponentBeginOverlap(Collider* collider, Collider* other) override;
	void OnComponentEndOverlap(Collider* collider, Collider* other) override;


	void UpdatePlayerLocation(glm::vec3 pos);


public:

	bool _collusion = false;

	Model* _left_arm;
	Model* _right_arm;

	glm::vec3 left_arm_center = glm::vec3(-1.51369f + 0.38f, 12.708f, -0.480505f);
	glm::vec3 right_arm_center = glm::vec3(1.22144f - 0.358f, 12.7469f, -0.554352f);

	/// �ٵ�� ������Ʈ�� ���ǵ�����
	glm::mat4 _left_arm_matrix = glm::mat4(1.0f);
	glm::mat4 _right_arm_matrix = glm::mat4(1.0f);

	float degree = 0;


	glm::vec3 _player_pos = glm::vec3(0.0f, 0.0f, 0.0f);	// �÷��̾��� ��ġ ������Ʈ
	glm::vec3 _to = glm::vec3(0.0f, 0.0f, 0.0f);	// ���ϴ� ��ġ(�߰ݽÿ��� X)
	glm::vec3 _pos = glm::vec3(0.0f, 0.0f, 0.0f);	// ���� ��ġ
	glm::vec3 _dir = glm::vec3(0.0f, 0.0f, 0.0f);	// �̵�����, ����ȭ��
	glm::mat4 _trans_matrix = glm::mat4(1.0f);		// �̵����
	glm::mat4 _rotate_matrix = glm::mat4(1.0f);		// �̵������� �ٶ󺸵��� �ϴ� ȸ�����
	vector<glm::vec3> _patrol_locations;
	//glm::vec3 _patrol_locations[91];					// �������
	int _patrol_location_no = 0;
	float _speed = 40.0f;

	float _anim_switch = true;

	////////////////////////////////////
	// 
	// BehaviorTree�� Ghost ���ο��� ������ ���� ������
	// 
	// �Ʒ�ó�� ������ �����Ҵ��� �޴°� vector����� ����
	// �׷��� ������ �ִ°� 100���� vector��¸�?
	// ������ ��ü������� �Ÿ��� �� C��Ÿ�� �ڵ�����?
	// 
	// ����X ONLY �����͸�
	// 
	////////////////////////////////////

	void SetTargetLocation(float to_x, float to_y);
	bool DistanceLessThan(float x1, float z1, float x2, float z2, float radius);
	void MoveSlightlyTo(float to_x, float to_z);
	BehaviorStatus MoveTo();
	BehaviorStatus IsPlayerNearBy();
	BehaviorStatus ChasePlayer();
	BehaviorStatus GetPatrolLoc();

	void MakeBehaviorTree();

	BehaviorStatus(Ghost::* moveto)() = &Ghost::MoveTo;
	BehaviorStatus(Ghost::* player_nearby)() = &Ghost::IsPlayerNearBy;
	BehaviorStatus(Ghost::* chase_player)() = &Ghost::ChasePlayer;
	BehaviorStatus(Ghost::* get_patrol_loc)() = &Ghost::GetPatrolLoc;

	struct BehaviorNode
	{
		string _name = "UNDEFINED";
		NodeType _type = UNDEFINED;
		BehaviorStatus _value = BT_UNDEF;
		bool _has_condition = false;

		BehaviorStatus(Ghost::* _func)() = nullptr;
		vector<BehaviorNode> _children = {};
		int _childrenCount = 0;
	};

	struct BehaviorTree
	{
		BehaviorNode* _root;
	};

	BehaviorNode act_MoveTo;
	BehaviorNode act_GetPatrol;
	BehaviorNode seq_Patrol;

	BehaviorNode cond_PlayerNearby;
	BehaviorNode act_Chase;
	BehaviorNode seq_Chase;

	BehaviorNode sel_Patrol_or_Chase;


	BehaviorTree BT;

	void Reset(BehaviorNode* node);
	void TagCondition(BehaviorNode* node);
	BehaviorStatus RunNode(BehaviorNode* node);
	void RunBT();




};