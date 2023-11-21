#pragma once



class Light
{
public:
	Light();
	~Light();

	void SetLvector(glm::vec3 lvector);
	void SetAmbientIntensity(float ambientIntensity);
	void SetDiffuseIntensity(float diffuseIntensity);

	void SetSpecularIntensity(float specularIntensity);
	void SetShinIness(float shinelness);
	void SetLightColor(glm::vec3 lightcolor);
	void UseLight(Shader& shader);

private:


	glm::vec3 _lightColor;
	glm::vec3 _lvector; // max((n*l),0)*sd*md 에서의 l

	float _ambientIntensity; // 앰비언트 세기 
	float _diffuseIntensity; //  세기 

	float _specularIntensity; //스펙큘러 세기
	float _shinIness; //반짝임 계수
};