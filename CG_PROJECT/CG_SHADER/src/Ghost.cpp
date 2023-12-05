#include "pch.h"
#include "Ghost.h"


Ghost::Ghost(Model& model_body, Model& model_left_arm, Model& model_right_arm) :Object(ObjectType::GHOST)
{

	_center = model_body.GetCenter();
	_size.x = model_body.GetSize().x + 10.0f;
	_size.y = model_body.GetSize().y;
	_size.z = model_body.GetSize().z + 10.0f;

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

	if (_left_arm != nullptr)
	{
		delete _left_arm;
		_left_arm = nullptr;
	}

	if (_right_arm != nullptr)
	{
		delete _right_arm;
		_right_arm = nullptr;
	}

	if (_model != nullptr)
	{
		delete _model;
		_model = nullptr;
	}
}

void Ghost::Init()
{
	Super::Init();

	_patrol_locations.clear();
	_patrol_locations.shrink_to_fit();

	//	1 - 3번방 주위를 돔
	{
		_patrol_locations.push_back(glm::vec3(0.0f,		0.0f,	-470.0f));
		_patrol_locations.push_back(glm::vec3(-40.0f,	0.0f,	-470.0f));
		_patrol_locations.push_back(glm::vec3(-77.5f,	0.0f,	-470.0f));
		_patrol_locations.push_back(glm::vec3(-115.0f,	0.0f,	-470.0f));
		_patrol_locations.push_back(glm::vec3(-152.5f,	0.0f,	-470.0f));
		_patrol_locations.push_back(glm::vec3(-190.0f,	0.0f,	-470.0f));
		_patrol_locations.push_back(glm::vec3(-227.0f,	0.0f,	-470.0f));
		_patrol_locations.push_back(glm::vec3(-265.0f,	0.0f,	-470.0f));
		_patrol_locations.push_back(glm::vec3(-302.0f,	0.0f,	-470.0f));
		_patrol_locations.push_back(glm::vec3(-340.0f,	0.0f,	-470.0f));
		_patrol_locations.push_back(glm::vec3(-377.5f,	0.0f,	-470.0f));
		_patrol_locations.push_back(glm::vec3(-415.0f,	0.0f,	-470.0f));
	
		_patrol_locations.push_back(glm::vec3(-415.0f,	0.0f,	-485.0f));
		_patrol_locations.push_back(glm::vec3(-415.0f,	0.0f,	-522.5f));
		_patrol_locations.push_back(glm::vec3(-415.0f,	0.0f,	-560.0f));	// ROOM3 왼쪽문
		room3_left_door = _patrol_locations.size() - 1;
		_patrol_locations.push_back(glm::vec3(-415.0f,	0.0f,	-597.5f));
		_patrol_locations.push_back(glm::vec3(-415.0f,	0.0f,	-635.0f));
		_patrol_locations.push_back(glm::vec3(-415.0f,	0.0f,	-660.0f));
	
		_patrol_locations.push_back(glm::vec3(-377.5f,	0.0f,	-660.0f));
		_patrol_locations.push_back(glm::vec3(-340.0f,	0.0f,	-660.0f));
		_patrol_locations.push_back(glm::vec3(-302.5f,	0.0f,	-660.0f));
		_patrol_locations.push_back(glm::vec3(-227.5f,	0.0f,	-660.0f));
		_patrol_locations.push_back(glm::vec3(-190.0f,	0.0f,	-660.0f));
		_patrol_locations.push_back(glm::vec3(-152.5f,	0.0f,	-660.0f));
		_patrol_locations.push_back(glm::vec3(-115.0f,	0.0f,	-660.0f));
	
		_patrol_locations.push_back(glm::vec3(-115.0f,	0.0f,	-635.0f));
		_patrol_locations.push_back(glm::vec3(-115.0f,	0.0f,	-597.5f));
		_patrol_locations.push_back(glm::vec3(-115.0f,	0.0f,	-560.0f));	// ROOM3 오른쪽문
		room3_right_door = _patrol_locations.size() - 1;
		_patrol_locations.push_back(glm::vec3(-115.0f,	0.0f,	-522.5f));
		_patrol_locations.push_back(glm::vec3(-115.0f,	0.0f,	-470.0f));
	
		_patrol_locations.push_back(glm::vec3(-77.5f,	0.0f,	-470.0f));
		_patrol_locations.push_back(glm::vec3(-40.0f,	0.0f,	-470.0f));
		_patrol_locations.push_back(glm::vec3(0.0f,		0.0f,	-470.0f));
	
	
	}
	
	// 2 - 2번방 주위를 돔
	{
		_patrol_locations.push_back(glm::vec3(0.0f,		0.0f,	-470.0f));
		_patrol_locations.push_back(glm::vec3(0.0f,		0.0f,	-455.0f));
		_patrol_locations.push_back(glm::vec3(0.0f,		0.0f,	-417.5f));
		_patrol_locations.push_back(glm::vec3(0.0f,		0.0f,	-380.0f));	// ROOM2 왼쪽문
		room2_left_door = _patrol_locations.size() - 1;
		_patrol_locations.push_back(glm::vec3(0.0f,		0.0f,	-342.5f));
		_patrol_locations.push_back(glm::vec3(0.0f,		0.0f,	-305.0f));
		_patrol_locations.push_back(glm::vec3(0.0f,		0.0f,	-290.0f));
	
		_patrol_locations.push_back(glm::vec3(+35.0f,	0.0f,	-290.0f));
		_patrol_locations.push_back(glm::vec3(+82.5f,	0.0f,	-290.0f));
		_patrol_locations.push_back(glm::vec3(+130.0f,	0.0f,	-290.0f));
		_patrol_locations.push_back(glm::vec3(+177.5f,	0.0f,	-290.0f));
		_patrol_locations.push_back(glm::vec3(+225.0f,	0.0f,	-290.0f));
		_patrol_locations.push_back(glm::vec3(+272.5f,	0.0f,	-290.0f));
		_patrol_locations.push_back(glm::vec3(+320.0f,	0.0f,	-290.0f));
		_patrol_locations.push_back(glm::vec3(+367.5f,	0.0f,	-290.0f));
		_patrol_locations.push_back(glm::vec3(+415.0f,	0.0f,	-290.0f));
	
		_patrol_locations.push_back(glm::vec3(+415.0f,	0.0f,	-305.0f));
		_patrol_locations.push_back(glm::vec3(+415.0f,	0.0f,	-342.5f));
		_patrol_locations.push_back(glm::vec3(+415.0f,	0.0f,	-380.0f));	// ROOM2 오른쪽문
		room2_right_door = _patrol_locations.size() - 1;
		_patrol_locations.push_back(glm::vec3(+415.0f,	0.0f,	-417.5f));
		_patrol_locations.push_back(glm::vec3(+415.0f,	0.0f,	-455.0f));
		_patrol_locations.push_back(glm::vec3(+415.0f,	0.0f,	-470.0f));
	
		_patrol_locations.push_back(glm::vec3(+367.5f,	0.0f,	-470.0f));
		_patrol_locations.push_back(glm::vec3(+320.0f,	0.0f,	-470.0f));
		_patrol_locations.push_back(glm::vec3(+272.5f,	0.0f,	-470.0f));
		_patrol_locations.push_back(glm::vec3(+225.0,	0.0f,	-470.0f));
		_patrol_locations.push_back(glm::vec3(+177.5f,	0.0f,	-470.0f));
		_patrol_locations.push_back(glm::vec3(+130.0f,	0.0f,	-470.0f));
		_patrol_locations.push_back(glm::vec3(+82.5f,	0.0f,	-470.0f));
		_patrol_locations.push_back(glm::vec3(+35.0f,	0.0f,	-470.0f));
		_patrol_locations.push_back(glm::vec3(0.0f, 	0.0f,	-470.0f));
	}
	
	// 3 - 1번방 주위를 돔
	{
		_patrol_locations.push_back(glm::vec3(0.0f,		0.0f,	-470.0f));
		_patrol_locations.push_back(glm::vec3(-40.0f,	0.0f,	-470.0f));
		_patrol_locations.push_back(glm::vec3(-77.5f,	0.0f,	-470.0f));
		_patrol_locations.push_back(glm::vec3(-115.0f,	0.0f,	-470.0f));
		_patrol_locations.push_back(glm::vec3(-152.5f,	0.0f,	-470.0f));	// ROOM1 위쪽문
		room1_upper_door = _patrol_locations.size() - 1;
		_patrol_locations.push_back(glm::vec3(-190.0f,	0.0f,	-470.0f));
		_patrol_locations.push_back(glm::vec3(-227.5f,	0.0f,	-470.0f));
		_patrol_locations.push_back(glm::vec3(-265.0f,	0.0f,	-470.0f));
		_patrol_locations.push_back(glm::vec3(-302.5f,	0.0f,	-470.0f));
		_patrol_locations.push_back(glm::vec3(-340.0f,	0.0f,	-470.0f));
		_patrol_locations.push_back(glm::vec3(-377.5f,	0.0f,	-470.0f));
		_patrol_locations.push_back(glm::vec3(-415.0f,	0.0f,	-470.0f));
	
		_patrol_locations.push_back(glm::vec3(-415.0f,	0.0f,	-455.0f));
		_patrol_locations.push_back(glm::vec3(-415.0f,	0.0f,	-417.5f));
		_patrol_locations.push_back(glm::vec3(-415.0f,	0.0f,	-380.0f));
		_patrol_locations.push_back(glm::vec3(-415.0f,	0.0f,	-342.5f));
		_patrol_locations.push_back(glm::vec3(-415.0f,	0.0f,	-305.0f));
		_patrol_locations.push_back(glm::vec3(-415.0f,	0.0f,	-290.0f));
	
		_patrol_locations.push_back(glm::vec3(-367.5f,	0.0f,	-290.0f));	// ROOM1 아래쪽문
		room1_lower_door = _patrol_locations.size() - 1;
		_patrol_locations.push_back(glm::vec3(-320.0f,	0.0f,	-290.0f));
		_patrol_locations.push_back(glm::vec3(-272.5f,	0.0f,	-290.0f));
		_patrol_locations.push_back(glm::vec3(-225.0f,	0.0f,	-290.0f));
		_patrol_locations.push_back(glm::vec3(-177.5f,	0.0f,	-290.0f));
		_patrol_locations.push_back(glm::vec3(-130.0f,	0.0f,	-290.0f));
		_patrol_locations.push_back(glm::vec3(-82.5f,	0.0f,	-290.0f));
		_patrol_locations.push_back(glm::vec3(-35.0f,	0.0f,	-290.0f));
		_patrol_locations.push_back(glm::vec3(0.0f,		0.0f,	-290.0f));
	
		_patrol_locations.push_back(glm::vec3(0.0f,		0.0f,	-305.0f));
		_patrol_locations.push_back(glm::vec3(0.0f,		0.0f,	-342.5f));
		_patrol_locations.push_back(glm::vec3(0.0f,		0.0f,	-380.0f));
		_patrol_locations.push_back(glm::vec3(0.0f,		0.0f,	-417.5f));
		_patrol_locations.push_back(glm::vec3(0.0f,		0.0f,	-455.0f));
		_patrol_locations.push_back(glm::vec3(0.0f,		0.0f,	-470.0f));
	}

	// 4 - 4번방 주위를 돔
	{
		_patrol_locations.push_back(glm::vec3(0.0f,		0.0f,	-470.0f));
		_patrol_locations.push_back(glm::vec3(-40.0f,	0.0f,	-470.0f));
		_patrol_locations.push_back(glm::vec3(-77.5f,	0.0f,	-470.0f));
		_patrol_locations.push_back(glm::vec3(-115.0f,	0.0f,	-470.0f));

		_patrol_locations.push_back(glm::vec3(-115.0f,	0.0f,	-485.0f));
		_patrol_locations.push_back(glm::vec3(-115.0f,	0.0f,	-522.5f));
		_patrol_locations.push_back(glm::vec3(-115.0f,	0.0f,	-560.0f));
		_patrol_locations.push_back(glm::vec3(-115.0f,	0.0f,	-597.5f));
		_patrol_locations.push_back(glm::vec3(-115.0f,	0.0f,	-635.0f));
		_patrol_locations.push_back(glm::vec3(-115.0f,	0.0f,	-660.0f));

		_patrol_locations.push_back(glm::vec3(-77.5f,	0.0f,	-660.0f));
		_patrol_locations.push_back(glm::vec3(-40.0f, 	0.0f,	-660.0f));
		_patrol_locations.push_back(glm::vec3(0.0f,		0.0f,	-660.0f));	// ROOM4 윗문
		room4_upper_door = _patrol_locations.size() - 1;
		_patrol_locations.push_back(glm::vec3(+35.0f,	0.0f,	-660.0f));
		_patrol_locations.push_back(glm::vec3(+82.5f,	0.0f,	-660.0f));
		_patrol_locations.push_back(glm::vec3(+130.0f,	0.0f,	-660.0f));
		_patrol_locations.push_back(glm::vec3(+177.5f,	0.0f,	-660.0f));
		_patrol_locations.push_back(glm::vec3(+225.0f,	0.0f,	-660.0f));
		_patrol_locations.push_back(glm::vec3(+272.5f,	0.0f,	-660.0f));
		_patrol_locations.push_back(glm::vec3(+320.0f,	0.0f,	-660.0f));
		_patrol_locations.push_back(glm::vec3(+367.5f,	0.0f,	-660.0f));
		_patrol_locations.push_back(glm::vec3(+415.0f,	0.0f,	-660.0f));

		_patrol_locations.push_back(glm::vec3(+415.0f,	0.0f,	-635.0f));
		_patrol_locations.push_back(glm::vec3(+415.0f,	0.0f,	-597.5f));
		_patrol_locations.push_back(glm::vec3(+415.0f,	0.0f,	-560.0f));
		_patrol_locations.push_back(glm::vec3(+415.0f,	0.0f,	-522.5f));
		_patrol_locations.push_back(glm::vec3(+415.0f,	0.0f,	-485.0f));
		_patrol_locations.push_back(glm::vec3(+415.0f,	0.0f,	-470.0f));

		_patrol_locations.push_back(glm::vec3(+367.5f,	0.0f,	-470.0f));
		_patrol_locations.push_back(glm::vec3(+320.0f,	0.0f,	-470.0f));	// ROOM4 아랫문
		room4_lower_door = _patrol_locations.size() - 1;
		_patrol_locations.push_back(glm::vec3(+272.5f,	0.0f,	-470.0f));
		_patrol_locations.push_back(glm::vec3(+225.0f,	0.0f,	-470.0f));
		_patrol_locations.push_back(glm::vec3(+177.5f,	0.0f,	-470.0f));
		_patrol_locations.push_back(glm::vec3(+130.0f,	0.0f,	-470.0f));
		_patrol_locations.push_back(glm::vec3(+82.5f, 	0.0f,	-470.0f));
		_patrol_locations.push_back(glm::vec3(+35.0f, 	0.0f,	-470.0f));
		_patrol_locations.push_back(glm::vec3(0.0f,   	0.0f,	-470.0f));
	}

	// 1번방 아랫문 -> 윗문 순찰경로
	{
		_room1_patrol_lower2upper.push_back(glm::vec3(-367.5f, 0.0f, -305.0f));
		_room1_patrol_lower2upper.push_back(glm::vec3(-350.0f, 0.0f, -330.0f));
		_room1_patrol_lower2upper.push_back(glm::vec3(-300.0f, 0.0f, -330.0f));
		_room1_patrol_lower2upper.push_back(glm::vec3(-250.0f, 0.0f, -330.0f));
		_room1_patrol_lower2upper.push_back(glm::vec3(-200.0f, 0.0f, -330.0f));
		_room1_patrol_lower2upper.push_back(glm::vec3(-150.0f, 0.0f, -330.0f));
		_room1_patrol_lower2upper.push_back(glm::vec3(-100.0f, 0.0f, -330.0f));
		_room1_patrol_lower2upper.push_back(glm::vec3(-100.0f, 0.0f, -380.0f));
		_room1_patrol_lower2upper.push_back(glm::vec3(-100.0f, 0.0f, -430.0f));
		_room1_patrol_lower2upper.push_back(glm::vec3(-150.0f, 0.0f, -430.0f));
		_room1_patrol_lower2upper.push_back(glm::vec3(-150.0f, 0.0f, -455.0f));
	}

	// 1번방 윗문 -> 아랫문 순찰경로
	{
		_room1_patrol_upper2lower.push_back(glm::vec3(-150.0f, 0.0f, -455.0f));
		_room1_patrol_upper2lower.push_back(glm::vec3(-150.0f, 0.0f, -430.0f));
		_room1_patrol_upper2lower.push_back(glm::vec3(-200.0f, 0.0f, -430.0f));
		_room1_patrol_upper2lower.push_back(glm::vec3(-250.0f, 0.0f, -430.0f));
		_room1_patrol_upper2lower.push_back(glm::vec3(-300.0f, 0.0f, -430.0f));
		_room1_patrol_upper2lower.push_back(glm::vec3(-350.0f, 0.0f, -430.0f));
		_room1_patrol_upper2lower.push_back(glm::vec3(-350.0f, 0.0f, -380.0f));
		_room1_patrol_upper2lower.push_back(glm::vec3(-350.0f, 0.0f, -330.0f));
		_room1_patrol_upper2lower.push_back(glm::vec3(-367.5f, 0.0f, -305.0f));
	}

	// 2번방 왼쪽문 -> 오른쪽문 순찰경로
	{
		_room2_patrol_left2right.push_back(glm::vec3(+50.0f, 0.0f, -380.0f));
		_room2_patrol_left2right.push_back(glm::vec3(+100.0f, 0.0f, -380.0f));
		_room2_patrol_left2right.push_back(glm::vec3(+100.0f, 0.0f, -330.0f));
		_room2_patrol_left2right.push_back(glm::vec3(+150.0f, 0.0f, -330.0f));
		_room2_patrol_left2right.push_back(glm::vec3(+200.0f, 0.0f, -330.0f));
		_room2_patrol_left2right.push_back(glm::vec3(+250.0f, 0.0f, -330.0f));
		_room2_patrol_left2right.push_back(glm::vec3(+300.0f, 0.0f, -330.0f));
		_room2_patrol_left2right.push_back(glm::vec3(+350.0f, 0.0f, -330.0f));
		_room2_patrol_left2right.push_back(glm::vec3(+350.0f, 0.0f, -380.0f));
		_room2_patrol_left2right.push_back(glm::vec3(+400.0f, 0.0f, -380.0f));
	}

	// 2번방 오른쪽문 -> 왼쪽문 순찰경로
	{
		_room2_patrol_right2left.push_back(glm::vec3(+400.0f, 0.0f, -380.0f));
		_room2_patrol_right2left.push_back(glm::vec3(+350.0f, 0.0f, -380.0f));
		_room2_patrol_right2left.push_back(glm::vec3(+350.0f, 0.0f, -430.0f));
		_room2_patrol_right2left.push_back(glm::vec3(+300.0f, 0.0f, -430.0f));
		_room2_patrol_right2left.push_back(glm::vec3(+250.0f, 0.0f, -430.0f));
		_room2_patrol_right2left.push_back(glm::vec3(+200.0f, 0.0f, -430.0f));
		_room2_patrol_right2left.push_back(glm::vec3(+150.0f, 0.0f, -430.0f));
		_room2_patrol_right2left.push_back(glm::vec3(+100.0f, 0.0f, -430.0f));
		_room2_patrol_right2left.push_back(glm::vec3(+100.0f, 0.0f, -380.0f));
		_room2_patrol_right2left.push_back(glm::vec3(+50.0f, 0.0f, -380.0f));
	}

	// 3번방 왼쪽문 -> 오른쪽문 순찰경로
	{
		_room3_patrol_left2right.push_back(glm::vec3(-400.0f, 0.0f, -560.0f));
		_room3_patrol_left2right.push_back(glm::vec3(-370.0f, 0.0f, -560.0f));
		_room3_patrol_left2right.push_back(glm::vec3(-370.0f, 0.0f, -530.0f));
		_room3_patrol_left2right.push_back(glm::vec3(-370.0f, 0.0f, -500.0f));
		_room3_patrol_left2right.push_back(glm::vec3(-340.0f, 0.0f, -500.0f));
		_room3_patrol_left2right.push_back(glm::vec3(-310.0f, 0.0f, -500.0f));
		_room3_patrol_left2right.push_back(glm::vec3(-280.0f, 0.0f, -500.0f));
		_room3_patrol_left2right.push_back(glm::vec3(-250.0f, 0.0f, -500.0f));
		_room3_patrol_left2right.push_back(glm::vec3(-220.0f, 0.0f, -500.0f));
		_room3_patrol_left2right.push_back(glm::vec3(-190.0f, 0.0f, -500.0f));
		_room3_patrol_left2right.push_back(glm::vec3(-160.0f, 0.0f, -500.0f));
		_room3_patrol_left2right.push_back(glm::vec3(-160.0f, 0.0f, -530.0f));
		_room3_patrol_left2right.push_back(glm::vec3(-160.0f, 0.0f, -560.0f));
		_room3_patrol_left2right.push_back(glm::vec3(-130.0f, 0.0f, -560.0f));
	}

	// 3번방 오른쪽문 -> 왼쪽문 순찰경로
	{
		_room3_patrol_right2left.push_back(glm::vec3(-130.0f, 0.0f, -560.0f));
		_room3_patrol_right2left.push_back(glm::vec3(-160.0f, 0.0f, -560.0f));
		_room3_patrol_right2left.push_back(glm::vec3(-160.0f, 0.0f, -590.0f));
		_room3_patrol_right2left.push_back(glm::vec3(-160.0f, 0.0f, -620.0f));
		_room3_patrol_right2left.push_back(glm::vec3(-190.0f, 0.0f, -620.0f));
		_room3_patrol_right2left.push_back(glm::vec3(-220.0f, 0.0f, -620.0f));
		_room3_patrol_right2left.push_back(glm::vec3(-250.0f, 0.0f, -620.0f));
		_room3_patrol_right2left.push_back(glm::vec3(-280.0f, 0.0f, -620.0f));
		_room3_patrol_right2left.push_back(glm::vec3(-310.0f, 0.0f, -620.0f));
		_room3_patrol_right2left.push_back(glm::vec3(-340.0f, 0.0f, -620.0f));
		_room3_patrol_right2left.push_back(glm::vec3(-370.0f, 0.0f, -620.0f));
		_room3_patrol_right2left.push_back(glm::vec3(-370.0f, 0.0f, -590.0f));
		_room3_patrol_right2left.push_back(glm::vec3(-370.0f, 0.0f, -560.0f));
		_room3_patrol_right2left.push_back(glm::vec3(-400.0f, 0.0f, -560.0f));
	}

	// 4번방 아랫문 -> 윗문 순찰경로
	{
		_room4_patrol_upper2lower.push_back(glm::vec3(+320.0f, 0.0f, -485.0f));
		_room4_patrol_upper2lower.push_back(glm::vec3(+250.0f, 0.0f, -510.0f));
		_room4_patrol_upper2lower.push_back(glm::vec3(+200.0f, 0.0f, -510.0f));
		_room4_patrol_upper2lower.push_back(glm::vec3(+150.0f, 0.0f, -510.0f));
		_room4_patrol_upper2lower.push_back(glm::vec3(+100.0f, 0.0f, -510.0f));
		_room4_patrol_upper2lower.push_back(glm::vec3(+50.0f, 0.0f, -510.0f));
		_room4_patrol_upper2lower.push_back(glm::vec3(0.0f, 0.0f, -510.0f));
		_room4_patrol_upper2lower.push_back(glm::vec3(-50.0f, 0.0f, -510.0f));
		_room4_patrol_upper2lower.push_back(glm::vec3(-50.0f, 0.0f, -560.0f));
		_room4_patrol_upper2lower.push_back(glm::vec3(-50.0f, 0.0f, -610.0f));
		_room4_patrol_upper2lower.push_back(glm::vec3(0.0f, 0.0f, -610.0f));
		_room4_patrol_upper2lower.push_back(glm::vec3(0.0f, 0.0f, -635.0f));
	}
	
	// 4번방 윗문 -> 아랫문 순찰경로
	{
		_room4_patrol_lower2upper.push_back(glm::vec3(-0.0f,	0.0f, -635.0f));
		_room4_patrol_lower2upper.push_back(glm::vec3(-0.0f,	0.0f, -610.0f));
		_room4_patrol_lower2upper.push_back(glm::vec3(+50.0f,	0.0f, -610.0f));
		_room4_patrol_lower2upper.push_back(glm::vec3(+100.0f,	0.0f, -610.0f));
		_room4_patrol_lower2upper.push_back(glm::vec3(+150.0f,	0.0f, -610.0f));
		_room4_patrol_lower2upper.push_back(glm::vec3(+200.0f,	0.0f, -610.0f));
		_room4_patrol_lower2upper.push_back(glm::vec3(+250.0f,	0.0f, -610.0f));
		_room4_patrol_lower2upper.push_back(glm::vec3(+300.0f,	0.0f, -610.0f));
		_room4_patrol_lower2upper.push_back(glm::vec3(+350.0f,	0.0f, -610.0f));
		_room4_patrol_lower2upper.push_back(glm::vec3(+350.0f,	0.0f, -560.0f));
		_room4_patrol_lower2upper.push_back(glm::vec3(+350.0f,	0.0f, -510.0f));
		_room4_patrol_lower2upper.push_back(glm::vec3(+300.0f,	0.0f, -510.0f));
		_room4_patrol_lower2upper.push_back(glm::vec3(+320.0f,	0.0f,-485.0f));
	}




	MakeBehaviorTree();
}

void Ghost::Update()
{
	Super::Update();


	if (_anim_switch)
	{
		degree += 20.0f * 8.0f * GET_SINGLE(TimeManager)->GetDeltaTime();

		if (degree > 45.0f)
			_anim_switch = false;
	}
	else
	{
		degree -= 20.0f * 8.0f * GET_SINGLE(TimeManager)->GetDeltaTime();
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

	// _center도 같이 이동
	_center.x = _pos.x;
	_center.y = 15.0f;
	_center.z = _pos.z;


	_location = GetLocation(_pos.x, _pos.z);
	_player_location = GetLocation(_player_pos.x, _player_pos.z);




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
	_center = _pos;
}

void Ghost::OnComponentBeginOverlap(Collider* collider, Collider* other)
{
	if (other->GetOwner()->GetObjectType() == ObjectType::PLAYER)
	{
		cout << "PLAYER_COLLISION" << endl;
		_collusion = true;
		// 여기에 change scene

	}
	
}

void Ghost::OnComponentEndOverlap(Collider* collider, Collider* other)
{
	_collusion = true;

}



////////////////
// BehaviorNode
// - 행동과 관련된 함수들과 노드들을 생성합니다.
////////////////

void Ghost::SetGhostSpeed(float speed)
{
	_speed = speed;
}

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

Location Ghost::GetLocation(float x, float z)
{
	// 1번방은 x-400 ~ x-50, z-305 ~ z-455 

	if((x >= -430.0f && x <= 430.0f) && (z <= -275.0f && z >= -685.0f))
	{
		if ((x >= -400.0f && x <= -50.0f) && (z <= -305.0f && z >= -455.0f))
		{
			return Location::ROOM1;
		}
		else if ((x >= 50.0f && x <= 400.0f) && (z <= -305.0f && z >= -455.0f))
		{
			return Location::ROOM2;
		}
		else if ((x <= -130.0f && x >= -400.0f) && (z <= -485.0f && z >= -635.0f))
		{
			return Location::ROOM3;
		}
		else if ((x >= -100.0f && x <= 400.0f) && (z <= -485.0f && z >= -635.0f))
		{
			return Location::ROOM4;
		}
		else
		{
			return Location::CORRIDOR;
		}
	}
	else
	{
		return Location::NONE;
	}


}

BehaviorStatus Ghost::GetNearestPatrolLocAtPlayer()
{
	float x = _player_pos.x;
	float z = _player_pos.z;
	int minLoc = 0;
	float minDist = 9999.9f;
	for (int i = 0; i < _patrol_locations.size(); i++)
	{
		float distance2 = glm::pow((x - _patrol_locations[i].x), 2) + glm::pow((z - _patrol_locations[i].z), 2);
		float compare = minDist;	// minDist는 기본적으로 갱신하면서 제곱이 되므로 따로 제곱할 필요가 없다.
		if (distance2 < compare)
		{
			minLoc = i;
			minDist = distance2;
		}
	}

	_patrol_location_no = minLoc;
	_to.x = _patrol_locations[minLoc].x;
	_to.z = _patrol_locations[minLoc].z;
	_patrol_location_no = (_patrol_location_no + 1) % _patrol_locations.size();
	_state = GhostState::CHASE;
	return BehaviorStatus::BT_SUCCESS;
}

BehaviorStatus Ghost::GetNearestPatrolLocAtGhost()
{
	float x = _pos.x;
	float z = _pos.z;
	int minLoc = 0;
	float minDist = 9999.9f;
	for (int i = 0; i < _patrol_locations.size(); i++)
	{
		float distance2 = glm::pow((x - _patrol_locations[i].x), 2) + glm::pow((z - _patrol_locations[i].z), 2);
		float compare = minDist;	// minDist는 기본적으로 갱신하면서 제곱이 되므로 따로 제곱할 필요가 없다.
		if (distance2 < compare)
		{
			minLoc = i;
			minDist = distance2;
		}
	}

	_patrol_location_no = minLoc;
	_to.x = _patrol_locations[minLoc].x;
	_to.z = _patrol_locations[minLoc].z;
	_patrol_location_no = (_patrol_location_no + 1) % _patrol_locations.size();
	_state = GhostState::PATROL;
	return BehaviorStatus::BT_SUCCESS;
}

BehaviorStatus Ghost::IsGhostInChase()
{
	if (_state == GhostState::CHASE)
	{
		return BT_SUCCESS;
	}
	else
	{
		return BT_FAIL;
	}
}

BehaviorStatus Ghost::IsGhostInCorridorPatrol()
{
	if (_state == GhostState::PATROL)
	{
		return BT_SUCCESS;
	}
	else
	{
		return BT_FAIL;
	}
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
	if (DistanceLessThan(_pos.x, _pos.z, _player_pos.x, _player_pos.z, _detection_distance))
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

BehaviorStatus Ghost::IsPlayerVeryNearBy()
{
	if (DistanceLessThan(_pos.x, _pos.z, _player_pos.x, _player_pos.z, _detection_distance/2))
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

BehaviorStatus Ghost::IsPlayerOnSight()
{
	// 귀신의 방향벡터와 (플레이어 위치 - 귀신 위치)벡터를 정규화하여 내적해서 구함
	glm::vec3 v1 = glm::normalize(_dir);
	glm::vec3 v2 = glm::normalize(_player_pos - _pos);
	float temp = glm::dot(v1, v2);

	if (temp >= glm::cos(glm::radians(_detection_degree)))	// cos(탐지각도)보다 크다면 탐지각도보다 안에있음 -> v1, v2가 모두 정규화 되어있기 때문
	{
		cout << "player on sight" << endl;
		return BehaviorStatus::BT_SUCCESS;
	}
	else
	{
		return BehaviorStatus::BT_FAIL;
	}


}

BehaviorStatus Ghost::IsPlayerOnMoreSight()
{	// 귀신의 방향벡터와 (플레이어 위치 - 귀신 위치)벡터를 정규화하여 내적해서 구함
	glm::vec3 v1 = glm::normalize(_dir);
	glm::vec3 v2 = glm::normalize(_player_pos - _pos);
	float temp = glm::dot(v1, v2);

	if (temp >= glm::cos(glm::radians(_detection_degree*2)))	// cos(탐지각도 / 2)보다 크다면 탐지각도보다 안에있음 -> v1, v2가 모두 정규화 되어있기 때문
	{
		cout << "player on near sight" << endl;
		return BehaviorStatus::BT_SUCCESS;
	}
	else
	{
		return BehaviorStatus::BT_FAIL;
	}


}

BehaviorStatus Ghost::IsPlayerInRoom()
{
	if ((_player_location == Location::ROOM1) || 
		(_player_location == Location::ROOM2) ||
		(_player_location == Location::ROOM3) || 
		(_player_location == Location::ROOM4))
	{
		return BehaviorStatus::BT_SUCCESS;
	}
	else
	{
		return BehaviorStatus::BT_FAIL;
	}
}

BehaviorStatus Ghost::IsPlayerInCorridor()
{
	if (_player_location == Location::CORRIDOR)
	{
		return BehaviorStatus::BT_SUCCESS;
	}
	else
	{
		return BehaviorStatus::BT_FAIL;
	}
}

BehaviorStatus Ghost::ChasePlayer()
{
	_state = GhostState::CHASE;
	MoveSlightlyTo(_player_pos.x, _player_pos.z);
	if (DistanceLessThan(_pos.x, _pos.z, _player_pos.x, _player_pos.z, 0.5f))
	{
		// cout << "Chase Complete Game Over" << endl;
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
	// 노드는 맨 밑 단말노드부터 만들어 나가는 것이 좋음

	///// 순찰 시퀀스 /////////////////////////////////////////////////////////////////
	{

		///////// 복도 순찰 시작 SEQ //////////////////////////////////////////////////////////////////////////////

		act_get_near_loc_from_ghost._name = "get nearest loc from ghost";
		act_get_near_loc_from_ghost._type = ACTION;
		act_get_near_loc_from_ghost._func = &Ghost::GetNearestPatrolLocAtGhost;

		act_move_to._name = "move to loc";
		act_move_to._type = ACTION;
		act_move_to._func = &Ghost::MoveTo;

		seq_corridor_patrol_start._name = "start corridor patrol";
		seq_corridor_patrol_start._type = SEQUENCE;
		seq_corridor_patrol_start._children.push_back(act_get_near_loc_from_ghost);
		seq_corridor_patrol_start._children.push_back(act_move_to);

		///////// 순찰 시작 SEQ //////////////////////////////////////////////////////////////////////////////

		cond_was_chasing._name = "was chasing";
		cond_was_chasing._type = CONDITION;
		cond_was_chasing._func = &Ghost::IsGhostInChase;

		seq_start_patrol._name = "start patrol";
		seq_start_patrol._type = SEQUENCE;
		seq_start_patrol._children.push_back(cond_was_chasing);
		seq_start_patrol._children.push_back(seq_corridor_patrol_start);

		///////// 순찰 중 SEQ //////////////////////////////////////////////////////////////////////////////

		act_get_next_patrol_loc._name = "get next patrol loc";
		act_get_next_patrol_loc._type = ACTION;
		act_get_next_patrol_loc._func = &Ghost::GetPatrolLoc;

		seq_in_patrol._name = "in patrol";
		seq_in_patrol._type = SEQUENCE;
		seq_in_patrol._children.push_back(act_get_next_patrol_loc);
		seq_in_patrol._children.push_back(act_move_to);

		///////// 최상위 순찰 SEQ //////////////////////////////////////////////////////////////////////////////
		sel_patrol._name = "in patrol";
		sel_patrol._type = SELECTOR;
		sel_patrol._children.push_back(seq_start_patrol);
		sel_patrol._children.push_back(seq_in_patrol);


		//BT._root = &seq_Patrol;
	}

	///// 추격 시퀀스 /////////////////////////////////////////////////////////////////
	{

		///////// 복도 추격 SEQ //////////////////////////////////////////////////////////////////////////////

		act_get_near_loc_from_player._name = "get nearest loc from player";
		act_get_near_loc_from_player._type = ACTION;
		act_get_near_loc_from_player._func = &Ghost::GetNearestPatrolLocAtPlayer;
		
		act_move_to_loc._name = "move to loc";
		act_move_to_loc._type = ACTION;
		act_move_to_loc._func = &Ghost::MoveTo;

		seq_corridor_chase._name = "corridor chase";
		seq_corridor_chase._type = SEQUENCE;
		seq_corridor_chase._children.push_back(act_get_near_loc_from_player);
		seq_corridor_chase._children.push_back(act_move_to_loc);

		///////// 먼 추격 조건 SEL //////////////////////////////////////////////////////////////////////////////

		cond_is_player_on_sight._name = "is player on sight";
		cond_is_player_on_sight._type = CONDITION;
		cond_is_player_on_sight._func = &Ghost::IsPlayerOnSight;

		cond_is_already_chase._name = "is already chase";
		cond_is_already_chase._type = CONDITION;
		cond_is_already_chase._func = &Ghost::IsGhostInChase;

		sel_far_chase_condition._name = "far chase condition";
		sel_far_chase_condition._type = SELECTOR;
		sel_far_chase_condition._children.push_back(cond_is_player_on_sight);
		sel_far_chase_condition._children.push_back(cond_is_already_chase);


		///////// 먼 추격 SEQ //////////////////////////////////////////////////////////////////////////////

		cond_is_player_near._name = "is player nearby";
		cond_is_player_near._type = CONDITION;
		cond_is_player_near._func = &Ghost::IsPlayerNearBy;

		seq_far_chase._name = "far chase";
		seq_far_chase._type = SEQUENCE;
		seq_far_chase._children.push_back(cond_is_player_near);
		seq_far_chase._children.push_back(sel_far_chase_condition);
		seq_far_chase._children.push_back(seq_corridor_chase);

		///////// 가까운 추격  조건 SEL //////////////////////////////////////////////////////////////////////////////

		cond_is_player_on_more_sight._name = "is player on more sight";
		cond_is_player_on_more_sight._type = CONDITION;
		cond_is_player_on_more_sight._func = &Ghost::IsPlayerOnMoreSight;

		sel_near_chase_condition._name = "near chase condition";
		sel_near_chase_condition._type = SELECTOR;
		sel_near_chase_condition._children.push_back(cond_is_player_on_more_sight);
		sel_near_chase_condition._children.push_back(cond_is_already_chase);

		///////// 가까운 추격 SEQ //////////////////////////////////////////////////////////////////////////////

		cond_is_player_very_near._name = "is player very nearby";
		cond_is_player_very_near._type = CONDITION;
		cond_is_player_very_near._func = &Ghost::IsPlayerVeryNearBy;
		

		act_move_direct_to_player._name = "move direct to player";
		act_move_direct_to_player._type = ACTION;
		act_move_direct_to_player._func = &Ghost::ChasePlayer;

		seq_near_chase._name = "near chase";
		seq_near_chase._type = SEQUENCE;
		seq_near_chase._children.push_back(cond_is_player_very_near);
		seq_near_chase._children.push_back(sel_near_chase_condition);
		seq_near_chase._children.push_back(act_move_direct_to_player);

		///////// 추격 시작 SEL //////////////////////////////////////////////////////////////////////////////

		sel_chase_start._name = "chase start";
		sel_chase_start._type = SELECTOR;
		sel_chase_start._children.push_back(seq_near_chase);
		sel_chase_start._children.push_back(seq_far_chase);

		///////// 최상위 추격 SEQ //////////////////////////////////////////////////////////////////////////////
		
		cond_is_player_in_corridor._name = "is player in corridor";
		cond_is_player_in_corridor._type = CONDITION;
		cond_is_player_in_corridor._func = &Ghost::IsPlayerInCorridor;

		seq_chase._name = "chase";
		seq_chase._type = SEQUENCE;
		seq_chase._children.push_back(cond_is_player_in_corridor);
		seq_chase._children.push_back(sel_chase_start);


		BT._root = &seq_chase;
		TagCondition(BT._root);
	}

	///// 순찰 혹은 추격 셀렉터 /////////////////////////////////////////////////////////////////
	{
		sel_Patrol_or_Chase._name = "Patrol or Chase";
		sel_Patrol_or_Chase._type = SELECTOR;
		sel_Patrol_or_Chase._children.push_back(seq_chase);
		sel_Patrol_or_Chase._children.push_back(sel_patrol);
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
		for (int i = 0; i < node->_children.size(); i++)
		{
			Reset(&node->_children[i]);
		}
	}
	else if (node->_type == SELECTOR)
	{
		node->_value = BT_UNDEF;
		for (int i = 0; i < node->_children.size(); i++)
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
		for (int i = 0; i < node->_children.size(); i++)
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
		for (int i = 0; i < node->_children.size(); i++)
		{
			if (node->_children[i]._value == BT_UNDEF || node->_children[i]._value == BT_RUNNING || node->_children[i]._has_condition == true)
			{
				node->_value = RunNode(&node->_children[i]);
				if (node->_value == BT_RUNNING || node->_value == BT_FAIL)
				{
					//cout << node->_name << " -> Value : " << node->_value << endl;
					return node->_value;
				}
			}
		}
		node->_value = BT_SUCCESS;
		//cout << node->_name << " -> Value : " << node->_value << endl;
		return node->_value;
	}
	else if (node->_type == SELECTOR)
	{
		for (int i = 0; i < node->_children.size(); i++)
		{
			if (node->_children[i]._value == BT_UNDEF || node->_children[i]._value == BT_RUNNING || node->_children[i]._has_condition == true)
			{
				node->_value = RunNode(&node->_children[i]);
				if (node->_value == BT_RUNNING || node->_value == BT_SUCCESS)
				{
					//cout << node->_name << " -> Value : " << node->_value << endl;
					return node->_value;
				}
			}
		}
		//cout << node->_name << " -> Value : " << node->_value << endl;
		node->_value = BT_FAIL;
		return node->_value;
	}
	else
	{
		if (node->_func)
		{
			// 일단 작동함
			node->_value = (this->*(node->_func))();
			//cout << node->_name << " -> Value : " << node->_value << endl;
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















