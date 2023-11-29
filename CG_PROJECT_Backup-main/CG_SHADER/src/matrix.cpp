#include "pch.h"
#include "matrix.h"



glm::mat4 matrix::GetSimple()
{
	return glm::mat4(1.0f);
}

glm::mat4 matrix::GetTranslation(float dx , float dy ,float dz)
{
	return  glm::translate(glm::mat4(1.0f), glm::vec3(dx, dy, dz));
}


glm::mat4 matrix::GetScale(float dx, float dy, float dz)
{
	return glm::scale(glm::mat4(1.0f), glm::vec3(dx, dy, dz));
}

glm::mat4 matrix::GetRotate(float degree, float x, float y, float z)
{
	return glm::rotate(glm::mat4(1.0f), glm::radians(degree), glm::vec3(x, y, z));

}


glm::mat4 matrix::GetCamera(glm::vec3 eye, glm::vec3 at, glm::vec3 up)
{
	glm::mat4 view(1.0f);
	view = glm::lookAt(eye, at, up);

	return view;
}

glm::mat4 matrix::GetRotateCamera()
{
	float dt = TimeManager::GetInstance()->GetDeltaTime();
	float angle = camera_speed;

	auto x = sinf(angle) * 60.0f;
	auto z = cosf(angle) * 60.0f;

	glm::mat4 view = glm::mat4(1.0f);
	glm::vec3 cameraPos = glm::vec3(x, 30, z); //--- 카메라 위치
	glm::vec3 cameraDirection = glm::vec3(0.0f, 0.0f, 0.0f); //--- 카메라 바라보는 방향
	glm::vec3 cameraUp = glm::vec3(0.0f, 1.0f, 0.0f); //--- 카메라 위쪽 방향
	view = glm::lookAt(cameraPos, cameraDirection, cameraUp);

	camera_speed += 0.5f * dt; //사실은 스피드가 아니라 라디안개념
	return view;
}

glm::mat4 matrix::GetRotateCamera(float dy)
{
	float dt = TimeManager::GetInstance()->GetDeltaTime();
	float angle = camera_speed;

	auto x = sinf(angle) * 30.0f;
	auto z = cosf(angle) * 30.0f;

	glm::mat4 view = glm::mat4(1.0f);
	glm::vec3 cameraPos = glm::vec3(x, dy, z); //--- 카메라 위치
	glm::vec3 cameraDirection = glm::vec3(0.0f, 0.0f, 0.0f); //--- 카메라 바라보는 방향
	glm::vec3 cameraUp = glm::vec3(0.0f, 1.0f, 0.0f); //--- 카메라 위쪽 방향
	view = glm::lookAt(cameraPos, cameraDirection, cameraUp);

	camera_speed += 0.1f * dt; //사실은 스피드가 아니라 라디안개념
	return view;
}

glm::mat4 matrix::GetProjection()
{
	glm::mat4 projection = glm::mat4(1.0f);
	float screenWidth = glutGet(GLUT_SCREEN_WIDTH); // 모니터의 가로 해상도 가져오기
	float screenHeight = glutGet(GLUT_SCREEN_HEIGHT); // 모니터의 세로 해상도 가져오기
	projection = glm::perspective(glm::radians(50.0f), screenWidth/ screenHeight, 0.1f, 500.0f); //--- 투영 공간 설정: fovy, aspect, near, far

	return projection;
}

glm::mat4 matrix::GetProjection(float _fovy, float _aspect, float _near, float _far)
{
	glm::mat4 projection = glm::mat4(1.0f);


	projection = glm::perspective(glm::radians(_fovy), _aspect, _near, _far); //--- 투영 공간 설정: fovy, aspect, near, far

	return projection;
}

glm::mat4 matrix::Getortho()
{
	glm::mat4 projection = glm::mat4(1.0f);
	projection = glm::ortho(-100.0f, 100.0f, -100.0f, 100.0f, -300.0f, 300.0f);

	return projection;
}


