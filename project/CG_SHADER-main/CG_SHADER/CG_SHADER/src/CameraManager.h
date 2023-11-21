#pragma once


class CameraManager
{

public:

	static CameraManager* GetInstance()
	{
		static CameraManager MM;
		return &MM;
	}


	void KeyUpdate();
	void MouseUpdate(float x, float y);

	glm::mat4 GetMatrix();


	bool m_cameraControl{ true };
	glm::vec2 m_prevMousePos{ glm::vec2(0.0f) };

public:

	float m_cameraSpeed = 40.0f;

	float m_cameraPitch{ 0.0f };
	float m_cameraYaw{ 0.0f };

	glm::vec3 m_cameraPos{ glm::vec3(0.0f,50.0f,3.0f) };
	glm::vec3 m_cameraFront{ glm::vec3(0.0f,0.0f,-1.0f) };
	glm::vec3 m_cameraUp{ glm::vec3(0.0f,1.0f,0.0f) };

	// 카메라의 위치변화를 알기 위한 이전 카메라 위치 정의
	glm::vec3 m_cameraLastPos{ glm::vec3(0.0f, 0.0f, 0.0f) };
};

