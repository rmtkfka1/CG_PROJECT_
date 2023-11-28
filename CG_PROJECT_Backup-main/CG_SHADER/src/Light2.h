#pragma once


struct Light
{
	glm::vec3 position; //±¤¿øÀÇ À§Ä¡
	glm::vec3 direction; //±¤¿øÀÇ À§Ä¡
	glm::vec2 cutoff;
	glm::vec3 ambient;
	float distance;
	glm::vec3 diffuse;
	glm::vec3 specular;
};

struct Material
{
	glm::vec3 specular;
	float shininess;
};



class Light2
{

public:

	Light2();
	~Light2();
	void UseSpotLight(Shader& shader);
	void UsePointLight(Shader& shader);




public:
	void SetLightPos(glm::vec3 pos);

	void SetLightAmbient(glm::vec3 sa);
	void SetLightDiffuse(glm::vec3 sd);

	void SetLightSpecular(glm::vec3 ss);

	void SetMaterialSpecular(glm::vec3 ms);
	void SetShininess(float shininess);

public:

	Light Spot_light;
	Material Spot_material;







};

