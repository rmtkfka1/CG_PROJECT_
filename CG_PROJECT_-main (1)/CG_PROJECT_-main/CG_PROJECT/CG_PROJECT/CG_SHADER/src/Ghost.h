#pragma once

#include "Object.h"


class Model;
class Light2;

enum class Location
{
	NONE = -1, // 아직 메인룸에 들어오지 않음
	CORRIDOR = 0,
	ROOM1,
	ROOM2,
	ROOM3,
	ROOM4
};

enum class GhostState
{
	PATROL,
	CHASE
};

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

	void UpdateGhostSpeed();

public:

	bool _collusion = false;

	Model* _left_arm;
	Model* _right_arm;

	glm::vec3 left_arm_center = glm::vec3(3.3f, 24.344f, -0.76f);
	glm::vec3 right_arm_center = glm::vec3(-2.53f , 24.344f, 0.17f);

	/// 바디는 오브젝트에 정의되있음
	glm::mat4 _left_arm_matrix = glm::mat4(1.0f);
	glm::mat4 _right_arm_matrix = glm::mat4(1.0f);

	float degree = 0;


	glm::vec3 _player_pos = glm::vec3(0.0f, 0.0f, 0.0f);	// 플레이어의 위치 업데이트
	glm::vec3 _to = glm::vec3(0.0f, 0.0f, 0.0f);	// 향하는 위치(추격시에는 X)
	glm::vec3 _pos = glm::vec3(0.0f, 0.0, 0.0f);	// 현재 위치
	glm::vec3 _dir = glm::vec3(0.0f, 0.0f, 0.0f);	// 이동방향, 정규화됨
	glm::mat4 _trans_matrix = glm::mat4(1.0f);		// 이동행렬
	glm::mat4 _rotate_matrix = glm::mat4(1.0f);		// 이동방향을 바라보도록 하는 회전행렬
	
	Location _location;
	Location _player_location = Location::NONE;

	GhostState _state;
	float _detection_distance = 130.0f;
	float _detection_degree = 90.0f;	// 탐지 각도(귀신 기준 삼각형의 시야)

	vector<glm::vec3> _patrol_locations;
	vector<glm::vec3> _room1_patrol_lower2upper;
	vector<glm::vec3> _room1_patrol_upper2lower;
	vector<glm::vec3> _room2_patrol_left2right;
	vector<glm::vec3> _room2_patrol_right2left;
	vector<glm::vec3> _room3_patrol_left2right;
	vector<glm::vec3> _room3_patrol_right2left;
	vector<glm::vec3> _room4_patrol_upper2lower;
	vector<glm::vec3> _room4_patrol_lower2upper;

	int room1_upper_door;
	int room1_lower_door;
	int room2_left_door;
	int room2_right_door;
	int room3_left_door;
	int room3_right_door;
	int room4_upper_door;
	int room4_lower_door;

	int _patrol_location_no = 0;
	float _speed = 75.0f;

	float _anim_switch = true;

	////////////////
	// 
	// BehaviorTree
	// 
	////////////////

	void SetGhostSpeed(float speed);
	void SetTargetLocation(float to_x, float to_y);
	bool DistanceLessThan(float x1, float z1, float x2, float z2, float radius);
	void MoveSlightlyTo(float to_x, float to_z);
	
	Location GetLocation(float x, float z);

	BehaviorStatus GetNearestPatrolLocAtPlayer();			// 복도순찰경로만 해서 가장 가까운 지점를 가져옴
	
	BehaviorStatus GetNearestPatrolLocAtGhost();
	
	BehaviorStatus IsGhostInChase();
	BehaviorStatus IsGhostInCorridorPatrol();

	BehaviorStatus MoveTo();
	BehaviorStatus IsPlayerNearBy();
	BehaviorStatus IsPlayerVeryNearBy();
	BehaviorStatus IsPlayerOnSight();
	BehaviorStatus IsPlayerOnMoreSight();

	BehaviorStatus IsPlayerInRoom();
	BehaviorStatus IsPlayerInCorridor();

	BehaviorStatus ChasePlayer();

	BehaviorStatus GetPatrolLoc();

	void MakeBehaviorTree();



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

	// 순찰
	BehaviorNode cond_was_chasing;
	BehaviorNode act_get_near_loc_from_ghost;
	BehaviorNode act_move_to;
	BehaviorNode seq_corridor_patrol_start;
	BehaviorNode seq_start_patrol;
	BehaviorNode act_get_next_patrol_loc;
	BehaviorNode seq_in_patrol;
	BehaviorNode sel_patrol;


	// 추격
	BehaviorNode cond_is_player_very_near;
	BehaviorNode act_move_direct_to_player;
	BehaviorNode cond_is_player_near;
	BehaviorNode cond_is_player_on_sight;
	BehaviorNode cond_is_player_on_more_sight;
	BehaviorNode cond_is_already_chase;
	BehaviorNode sel_near_chase_condition;
	BehaviorNode sel_far_chase_condition;
	BehaviorNode act_get_near_loc_from_player;
	BehaviorNode act_move_to_loc;
	BehaviorNode seq_corridor_chase;
	BehaviorNode seq_far_chase;
	BehaviorNode seq_near_chase;
	BehaviorNode sel_chase_start;
	BehaviorNode cond_is_player_in_corridor;
	BehaviorNode seq_chase;



	BehaviorNode sel_Patrol_or_Chase;


	BehaviorTree BT;

	void Reset(BehaviorNode* node);
	void TagCondition(BehaviorNode* node);
	BehaviorStatus RunNode(BehaviorNode* node);
	void RunBT();




};