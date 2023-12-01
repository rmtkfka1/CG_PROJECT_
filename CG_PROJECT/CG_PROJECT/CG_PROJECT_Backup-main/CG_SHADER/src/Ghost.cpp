#include "pch.h"
#include "Ghost.h"


Ghost::Ghost(Model& model_body, Model& model_left_arm, Model& model_right_arm) :Object(ObjectType::GHOST)
{

	_center = model_body.GetCenter();
	_size = model_body.GetSize();

	_first_center = _center;
	_model = &model_body;

	_left_arm = &model_left_arm;
	_right_arm = &model_right_arm;

	//left_arm_center = _left_arm->GetCenter();
	//right_arm_center = _right_arm->GetCenter();

}

Ghost::~Ghost()
{
	cout << "~Ghost" << endl;
}

void Ghost::Init()
{
	Super::Init();

	//	1
	{
		_patrol_locations.push_back(glm::vec3(0.0f, 0.0f, -525.0f));
		_patrol_locations.push_back(glm::vec3(-75.0f, 0.0f, -525.0f));
		_patrol_locations.push_back(glm::vec3(-150.0f, 0.0f, -525.0f));
		_patrol_locations.push_back(glm::vec3(-225.0f, 0.0f, -525.0f));
		_patrol_locations.push_back(glm::vec3(-300.0f, 0.0f, -525.0f));
		_patrol_locations.push_back(glm::vec3(-375.0f, 0.0f, -525.0f));
		_patrol_locations.push_back(glm::vec3(-450.0f, 0.0f, -525.0f));

		_patrol_locations.push_back(glm::vec3(-450.0f, 0.0f, -525.0f));
		_patrol_locations.push_back(glm::vec3(-450.0f, 0.0f, -575.0f));
		_patrol_locations.push_back(glm::vec3(-450.0f, 0.0f, -625.0f));
		_patrol_locations.push_back(glm::vec3(-450.0f, 0.0f, -675.0f));
		_patrol_locations.push_back(glm::vec3(-450.0f, 0.0f, -725.0f));

		_patrol_locations.push_back(glm::vec3(-450.0f, 0.0f, -725.0f));
		_patrol_locations.push_back(glm::vec3(-375.0f, 0.0f, -725.0f));
		_patrol_locations.push_back(glm::vec3(-300.0f, 0.0f, -725.0f));
		_patrol_locations.push_back(glm::vec3(-225.0f, 0.0f, -725.0f));
		_patrol_locations.push_back(glm::vec3(-150.0f, 0.0f, -725.0f));

		_patrol_locations.push_back(glm::vec3(-150.0f, 0.0f, -725.0f));
		_patrol_locations.push_back(glm::vec3(-150.0f, 0.0f, -675.0f));
		_patrol_locations.push_back(glm::vec3(-150.0f, 0.0f, -625.0f));
		_patrol_locations.push_back(glm::vec3(-150.0f, 0.0f, -575.0f));
		_patrol_locations.push_back(glm::vec3(-150.0f, 0.0f, -525.0f));

		_patrol_locations.push_back(glm::vec3(-75.0f, 0.0f, -525.0f));
		_patrol_locations.push_back(glm::vec3(-0.0f, 0.0f, -525.0f));
	}

	//	2
	{
		_patrol_locations.push_back(glm::vec3(0.0f, 0.0f, -525.0f));
		_patrol_locations.push_back(glm::vec3(0.0f, 0.0f, -450.0f));
		_patrol_locations.push_back(glm::vec3(0.0f, 0.0f, -400.0f));
		_patrol_locations.push_back(glm::vec3(0.0f, 0.0f, -350.0f));
		_patrol_locations.push_back(glm::vec3(0.0f, 0.0f, -300.0f));

		_patrol_locations.push_back(glm::vec3(+75.0f, 0.0f, -300.0f));
		_patrol_locations.push_back(glm::vec3(+150.0f, 0.0f, -300.0f));
		_patrol_locations.push_back(glm::vec3(+225.0f, 0.0f, -300.0f));
		_patrol_locations.push_back(glm::vec3(+300.0f, 0.0f, -300.0f));
		_patrol_locations.push_back(glm::vec3(+375.0f, 0.0f, -300.0f));
		_patrol_locations.push_back(glm::vec3(+450.0f, 0.0f, -300.0f));

		_patrol_locations.push_back(glm::vec3(+450.0f, 0.0f, -350.0f));
		_patrol_locations.push_back(glm::vec3(+450.0f, 0.0f, -400.0f));
		_patrol_locations.push_back(glm::vec3(+450.0f, 0.0f, -450.0f));
		_patrol_locations.push_back(glm::vec3(+450.0f, 0.0f, -525.0f));

		_patrol_locations.push_back(glm::vec3(+375.0f, 0.0f, -525.0f));
		_patrol_locations.push_back(glm::vec3(+300.0f, 0.0f, -525.0f));
		_patrol_locations.push_back(glm::vec3(+225.0f, 0.0f, -525.0f));
		_patrol_locations.push_back(glm::vec3(+75.0f, 0.0f, -525.0f));
		_patrol_locations.push_back(glm::vec3(+0.0f, 0.0f, -525.0f));
	}

	// 3
	{
		_patrol_locations.push_back(glm::vec3(0.0f, 0.0f, -525.0f));
		_patrol_locations.push_back(glm::vec3(-75.0f, 0.0f, -525.0f));
		_patrol_locations.push_back(glm::vec3(-150.0f, 0.0f, -525.0f));
		_patrol_locations.push_back(glm::vec3(-225.0f, 0.0f, -525.0f));
		_patrol_locations.push_back(glm::vec3(-300.0f, 0.0f, -525.0f));
		_patrol_locations.push_back(glm::vec3(-375.0f, 0.0f, -525.0f));
		_patrol_locations.push_back(glm::vec3(-450.0f, 0.0f, -525.0f));

		_patrol_locations.push_back(glm::vec3(-450.0f, 0.0f, -450.0f));
		_patrol_locations.push_back(glm::vec3(-450.0f, 0.0f, -400.0f));
		_patrol_locations.push_back(glm::vec3(-450.0f, 0.0f, -350.0f));
		_patrol_locations.push_back(glm::vec3(-450.0f, 0.0f, -300.0f));

		_patrol_locations.push_back(glm::vec3(-375.0f, 0.0f, -300.0f));
		_patrol_locations.push_back(glm::vec3(-300.0f, 0.0f, -300.0f));
		_patrol_locations.push_back(glm::vec3(-225.0f, 0.0f, -300.0f));
		_patrol_locations.push_back(glm::vec3(-150.0f, 0.0f, -300.0f));
		_patrol_locations.push_back(glm::vec3(-75.0f, 0.0f, -300.0f));
		_patrol_locations.push_back(glm::vec3(0.0f, 0.0f, -300.0f));

		_patrol_locations.push_back(glm::vec3(0.0f, 0.0f, -350.0f));
		_patrol_locations.push_back(glm::vec3(0.0f, 0.0f, -400.0f));
		_patrol_locations.push_back(glm::vec3(0.0f, 0.0f, -450.0f));
		_patrol_locations.push_back(glm::vec3(0.0f, 0.0f, -525.0f));
	}

	// 4
	{
		_patrol_locations.push_back(glm::vec3(0.0f, 0.0f, -525.0f));
		_patrol_locations.push_back(glm::vec3(-75.0f, 0.0f, -525.0f));

		_patrol_locations.push_back(glm::vec3(-150.0f, 0.0f, -525.0f));
		_patrol_locations.push_back(glm::vec3(-150.0f, 0.0f, -575.0f));
		_patrol_locations.push_back(glm::vec3(-150.0f, 0.0f, -625.0f));
		_patrol_locations.push_back(glm::vec3(-150.0f, 0.0f, -675.0f));
		_patrol_locations.push_back(glm::vec3(-150.0f, 0.0f, -725.0f));

		_patrol_locations.push_back(glm::vec3(-75.0f, 0.0f, -725.0f));
		_patrol_locations.push_back(glm::vec3(0.0f, 0.0f, -725.0f));
		_patrol_locations.push_back(glm::vec3(+75.0f, 0.0f, -725.0f));
		_patrol_locations.push_back(glm::vec3(+150.0f, 0.0f, -725.0f));
		_patrol_locations.push_back(glm::vec3(+225.0f, 0.0f, -725.0f));
		_patrol_locations.push_back(glm::vec3(+375.0f, 0.0f, -725.0f));
		_patrol_locations.push_back(glm::vec3(+450.0f, 0.0f, -725.0f));

		_patrol_locations.push_back(glm::vec3(+450.0f, 0.0f, -675.0f));
		_patrol_locations.push_back(glm::vec3(+450.0f, 0.0f, -625.0f));
		_patrol_locations.push_back(glm::vec3(+450.0f, 0.0f, -575.0f));
		_patrol_locations.push_back(glm::vec3(+450.0f, 0.0f, -525.0f));

		_patrol_locations.push_back(glm::vec3(+375.0f, 0.0f, -525.0f));
		_patrol_locations.push_back(glm::vec3(+300.0f, 0.0f, -525.0f));
		_patrol_locations.push_back(glm::vec3(+225.0f, 0.0f, -525.0f));
		_patrol_locations.push_back(glm::vec3(+150.0f, 0.0f, -525.0f));
		_patrol_locations.push_back(glm::vec3(+75.0f, 0.0f, -525.0f));
		_patrol_locations.push_back(glm::vec3(0.0f, 0.0f, -525.0f));
	}

	MakeBehaviorTree();
}

void Ghost::Update()
{
	Super::Update();


	if (_anim_switch)
	{
		degree += _speed * 8.0f * GET_SINGLE(TimeManager)->GetDeltaTime();

		if (degree > 45.0f)
			_anim_switch = false;
	}
	else
	{
		degree -= _speed * 8.0f * GET_SINGLE(TimeManager)->GetDeltaTime();
		if (degree < -45.0f)
			_anim_switch = true;
	}



	if (KeyManager::GetInstance()->Getbutton(KeyType::SpaceBar))
	{
		degree += 750.0f * GET_SINGLE(TimeManager)->GetDeltaTime();
	}

	if (KeyManager::GetInstance()->Getbutton(KeyType::N))
	{
		degree -= 750.0f * GET_SINGLE(TimeManager)->GetDeltaTime();
	}

	// 위치로 이동하도록
	_trans_matrix = GET_SINGLE(matrix)->GetTranslation(_pos.x, _pos.y, _pos.z);

	// 이동방향을 바라보도록
	float angle = glm::degrees(atan2f(_dir.x, _dir.z));
	_rotate_matrix = GET_SINGLE(matrix)->GetRotate(angle, 0.0f, 1.0f, 0.0f);

	MatrixUpdate();

	RunBT();
}

void Ghost::Render(Shader& shader)
{
	Super::Render(shader);

	shader.SetUniform3f("control_color", 0, 0, 0);
	shader.SetUniformMat4f("u_model", _trans_matrix * _rotate_matrix * _matrix); // 몸통 바디 그려주는 부분
	_model->RenderModel(shader);

	shader.SetUniformMat4f("u_model", _trans_matrix * _rotate_matrix * _left_arm_matrix); // 왼쪽팔그려주는 부분
	_left_arm->RenderModel(shader);

	shader.SetUniformMat4f("u_model", _trans_matrix * _rotate_matrix * _right_arm_matrix); // 왼쪽팔그려주는 부분
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



void Ghost::SetPosition(float x, float z)
{
	_pos = glm::vec3(x, _center.y-20.0f, z);
}

void Ghost::OnComponentBeginOverlap(Collider* collider, Collider* other)
{
}

void Ghost::OnComponentEndOverlap(Collider* collider, Collider* other)
{
}



////////////////
// BehaviorNode
// - 행동과 관련된 함수들과 노드들을 생성합니다.
////////////////

void Ghost::SetTargetLocation(float to_x, float to_z)
{
	_to = glm::vec3(to_x, _center.y, to_z);
}

void Ghost::UpdatePlayerLocation(glm::vec3 pos)
{
	_player_pos = pos;
}

bool Ghost::DistanceLessThan(float x1, float z1, float x2, float z2, float radius)
{
	float distance2 = glm::pow((x1 - x2), 2) + glm::pow((z1 - z2), 2);
	float compare = glm::pow(radius, 2);
	if (distance2 < compare)
	{
		//	cout << "Distance Less Than " << radius << endl;
		return true;
	}
	else
	{
		//cout << "Distance Not Less Than " << radius << endl;
		return false;
	}
}

void Ghost::MoveSlightlyTo(float to_x, float to_z)
{
	glm::vec3 toV = glm::vec3(to_x, 0, to_z);
	_dir = glm::normalize(toV - _pos);

	_pos.x += _dir.x * _speed * GET_SINGLE(TimeManager)->GetDeltaTime();
	_pos.z += _dir.z * _speed * GET_SINGLE(TimeManager)->GetDeltaTime();
	//cout << "Move Slightly To : " << _dir.x * _speed * GET_SINGLE(TimeManager)->GetDeltaTime() << ", " << _dir.z * _speed * GET_SINGLE(TimeManager)->GetDeltaTime() << endl;
}

BehaviorStatus Ghost::MoveTo()
{
	MoveSlightlyTo(_to.x, _to.z);
	if (DistanceLessThan(_pos.x, _pos.z, _to.x, _to.z, 5.0f))
	{
		//cout << "Move Complete" << endl;
		return BT_SUCCESS;
	}
	else
	{
		//cout << "Move Not Complete" << endl;
		return BT_RUNNING;
	}
}

BehaviorStatus Ghost::IsPlayerNearBy()
{
	if (DistanceLessThan(_pos.x, _pos.z, _player_pos.x, _player_pos.z, 0.0f))
	{
		//cout << "Player Nearby!!" << endl;
		return BT_SUCCESS;
	}
	else
	{
		//cout << "Player NOT Nearby" << endl;
		return BT_FAIL;
	}
}

BehaviorStatus Ghost::ChasePlayer()
{
	MoveSlightlyTo(_player_pos.x, _player_pos.z);
	if (DistanceLessThan(_pos.x, _pos.z, _player_pos.x, _player_pos.z, 0.5f))
	{
		//cout << "Chase Complete Game Over" << endl;
		return BT_SUCCESS;
	}
	else
	{
		//cout << "Chasing Player" << endl;
		return BT_RUNNING;
	}
}

BehaviorStatus Ghost::GetPatrolLoc()
{
	_to.x = _patrol_locations[_patrol_location_no].x;
	_to.z = _patrol_locations[_patrol_location_no].z;
	_patrol_location_no = (_patrol_location_no + 1) % _patrol_locations.size();
	//cout << "Get Patrol Location" << _patrol_locations[_patrol_location_no].x << ", " << _patrol_locations[_patrol_location_no].z << endl;
	return BT_SUCCESS;
}

void Ghost::MakeBehaviorTree()
{
	///// 순찰 시퀀스 /////////////////////////////////////////////////////////////////
	{
		act_GetPatrol._name = "Get Patrol Location";
		act_GetPatrol._type = ACTION;
		act_GetPatrol._func = get_patrol_loc;

		act_MoveTo._name = "Move To";
		act_MoveTo._type = ACTION;
		act_MoveTo._func = moveto;

		seq_Patrol._name = "Patrol";
		seq_Patrol._type = SEQUENCE;
		seq_Patrol._children.push_back(act_GetPatrol);
		seq_Patrol._children.push_back(act_MoveTo);
		seq_Patrol._childrenCount = seq_Patrol._children.size();
		//BT._root = &seq_Patrol;
	}

	///// 추격 시퀀스 /////////////////////////////////////////////////////////////////
	{
		cond_PlayerNearby._name = "Is Player Nearby?";
		cond_PlayerNearby._type = CONDITION;
		cond_PlayerNearby._func = player_nearby;

		act_Chase._name = "Chase Player";
		act_Chase._type = ACTION;
		act_Chase._func = chase_player;

		seq_Chase._name = "Chase";
		seq_Chase._type = SEQUENCE;
		seq_Chase._children.push_back(cond_PlayerNearby);
		seq_Chase._children.push_back(act_Chase);
		seq_Chase._childrenCount = seq_Chase._children.size();
		//BT._root = &seq_Chase;
	}

	///// 순찰 혹은 추격 셀렉터 /////////////////////////////////////////////////////////////////
	{
		sel_Patrol_or_Chase._name = "Patrol or Chase";
		sel_Patrol_or_Chase._type = SELECTOR;
		sel_Patrol_or_Chase._children.push_back(seq_Chase);
		sel_Patrol_or_Chase._children.push_back(seq_Patrol);
		sel_Patrol_or_Chase._childrenCount = sel_Patrol_or_Chase._children.size();

		BT._root = &sel_Patrol_or_Chase;
		TagCondition(BT._root);
	}

}







////////////////
// BehaviorTree
// - 위에서 만든 노드들을 순회하며 행동하는 로직입니다.
// - Tree보단 노드들의 컨트롤러 느낌으로 접근한다면 좀 더 이해하기 좋습니다
////////////////

void Ghost::Reset(BehaviorNode* node)
{
	if (node->_type == SEQUENCE)
	{
		node->_value = BT_UNDEF;
		for (int i = 0; i < node->_childrenCount; i++)
		{
			Reset(&node->_children[i]);
		}
	}
	else if (node->_type == SELECTOR)
	{
		node->_value = BT_UNDEF;
		for (int i = 0; i < node->_childrenCount; i++)
		{
			Reset(&node->_children[i]);
		}
	}
	else
	{
		node->_value = BT_UNDEF;
	}
}

void Ghost::TagCondition(BehaviorNode* node)
{
	if (node->_type == SEQUENCE || node->_type == SELECTOR)
	{
		for (int i = 0; i < node->_childrenCount; i++)
		{
			TagCondition(&node->_children[i]);
			if (node->_children[i]._has_condition == true)
				node->_has_condition = true;
		}
	}
	else
	{
		if (node->_type == ACTION)
		{
			node->_has_condition = false;
		}
		else
		{
			node->_has_condition = true;
		}
	}
}

BehaviorStatus Ghost::RunNode(BehaviorNode* node)
{
	if (node->_type == SEQUENCE)
	{
		for (int i = 0; i < node->_childrenCount; i++)
		{
			if (node->_children[i]._value == BT_UNDEF || node->_children[i]._value == BT_RUNNING || node->_children[i]._has_condition == true)
			{
				node->_value = RunNode(&node->_children[i]);
				if (node->_value == BT_RUNNING || node->_value == BT_FAIL)
				{
					return node->_value;
				}
			}
		}
		node->_value = BT_SUCCESS;
		return node->_value;
	}
	else if (node->_type == SELECTOR)
	{
		for (int i = 0; i < node->_childrenCount; i++)
		{
			if (node->_children[i]._value == BT_UNDEF || node->_children[i]._value == BT_RUNNING || node->_children[i]._has_condition == true)
			{
				node->_value = RunNode(&node->_children[i]);
				if (node->_value == BT_RUNNING || node->_value == BT_SUCCESS)
				{
					return node->_value;
				}
			}
		}
		node->_value = BT_FAIL;
		return node->_value;
	}
	else
	{
		if (node->_func)
		{
			// 일단 작동함
			node->_value = (this->*(node->_func))();
			return node->_value;
		}
		else
		{
			cout << "함수 없음" << endl;
			return BT_FAIL;
		}
	}
}

void Ghost::RunBT()
{
	//cout << "new tick" << endl;
	RunNode(BT._root);
	if (BT._root->_value == BT_SUCCESS)
	{
		Reset(BT._root);
	}
}















