#pragma once


class matrix
{

public:
	static matrix* GetInstance()
	{
		static matrix mm;
		return &mm;
	}



	glm::mat4 GetSimple();

	glm::mat4 GetTranslation(float dx ,float dy ,float dz);
	
	glm::mat4 GetScale(float dx ,float dy ,float dz);

	glm::mat4 GetRotate(float degree, float x, float y, float z);
	
	glm::mat4 GetCamera(glm::vec3 eye , glm::vec3 at, glm::vec3 up=glm::vec3(0,1.0f,0));

	glm::mat4 GetRotateCamera();
	glm::mat4 GetRotateCamera(float dy);


	glm::mat4 GetProjection();
	glm::mat4 GetProjection(float _fovy,float _aspect, float _near ,float _far);


	glm::mat4 Getortho();

private:

	float camera_speed;
};

