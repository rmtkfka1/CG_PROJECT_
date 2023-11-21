#include "pch.h"
#include "CameraManager.h"

void CameraManager::KeyUpdate()
{
	if (!m_cameraControl)
	{
		return;
	}
	
	// 카메라 위치를 이동시키기 전에 이전 카메라의 위치를 저장

	float dt = TimeManager::GetInstance()->GetDeltaTime();

	if(KeyManager::GetInstance()->Getbutton(KeyType::W))
	{
		// 여기서 이동때마다 이전 포지션 업데이트 해주고
		m_cameraLastPos = m_cameraPos;
		m_cameraPos += m_cameraSpeed * m_cameraFront *dt;

		m_cameraPos.y = 50.0f;
	}
	if (KeyManager::GetInstance()->Getbutton(KeyType::S))
	{
		m_cameraLastPos = m_cameraPos;
		m_cameraPos -= m_cameraSpeed * m_cameraFront * dt;

		m_cameraPos.y = 50.0f;
	}


	auto cameraRight = glm::normalize(glm::cross(m_cameraUp, -m_cameraFront));

	if (KeyManager::GetInstance()->Getbutton(KeyType::D))
	{
		m_cameraLastPos = m_cameraPos;
		m_cameraPos += m_cameraSpeed * cameraRight * dt;

		m_cameraPos.y = 50.0f;
	}
	if (KeyManager::GetInstance()->Getbutton(KeyType::A))
	{
		m_cameraLastPos = m_cameraPos;
		m_cameraPos -= m_cameraSpeed * cameraRight * dt;

		m_cameraPos.y = 50.0f;
	}

	auto cameraUp = glm::normalize(glm::cross(-m_cameraFront, cameraRight));


	if (KeyManager::GetInstance()->Getbutton(KeyType::Q))
	{
		m_cameraLastPos = m_cameraPos;
		m_cameraPos += m_cameraSpeed * cameraUp * dt;
	}
	if (KeyManager::GetInstance()->Getbutton(KeyType::E))
	{
		m_cameraLastPos = m_cameraPos;
		m_cameraPos -= m_cameraSpeed * cameraUp * dt;
	}

}

void CameraManager::MouseUpdate(float x, float y)
{
	if (!m_cameraControl)
	{
		return;
	}



	float dt = TimeManager::GetInstance()->GetDeltaTime();

	
	auto pos = glm::vec2(x, y);
	auto deltaPos = pos - m_prevMousePos;

	const float cameraSpeed = 10.0f;

	m_cameraYaw -= deltaPos.x * cameraSpeed * dt;
	m_cameraPitch -= deltaPos.y * cameraSpeed * dt;


	if (m_cameraYaw < 0.0f) m_cameraYaw += 360.0f;
	if (m_cameraYaw > 360.0f) m_cameraYaw -= 360.0f;

	if (m_cameraPitch > 89.0f) m_cameraPitch = 89.0f;
	if (m_cameraPitch < -89.0f) m_cameraPitch = -89.0f;

	m_prevMousePos = pos;

}


glm::mat4 CameraManager::GetMatrix()
{

	m_cameraFront =
		glm::rotate(glm::mat4(1.0f), glm::radians(m_cameraYaw), glm::vec3(0.0f, 1.0f, 0.0f)) *
		glm::rotate(glm::mat4(1.0f), glm::radians(m_cameraPitch), glm::vec3(1.0f, 0, 0.0f)) *
		glm::vec4(0.0f, 0.0f, -1.0f, 0.0f);

	auto view = glm::lookAt(
		m_cameraPos,
		m_cameraPos + m_cameraFront,
		m_cameraUp);

	return view;
}
