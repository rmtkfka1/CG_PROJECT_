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



	glm::vec2 m_prevMousePos{ glm::vec2(0.0f) };
public:
	
	float m_cameraPitch{ 0.0f };
	float m_cameraYaw{ 0.0f };
	float m_cameraSpeed = 200.0f;

	glm::vec3 m_cameraPos{ glm::vec3(0.0f,5.0f,0.0f) };
	glm::vec3 m_cameraFront{ glm::vec3(0.0f,0.0f,-1.0f) };
	glm::vec3 m_cameraUp{ glm::vec3(0.0f,1.0f,0.0f) };




};

