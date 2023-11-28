#include "pch.h"
#include "Light.h"

Light::Light()
{
	_lightColor = glm::vec3(1.0f, 1.0f, 1.0f) ;
	_ambientIntensity = 1.0f;

	_lvector = glm::vec3(0, 0, 0);
	_diffuseIntensity = 1.0f;


	_specularIntensity = 1.0f;
	_shinIness =1.0f;

}

Light::~Light()
{

}


void Light::SetLvector(glm::vec3 lvector)
{
	_lvector = glm::normalize(lvector);
}


void Light::SetAmbientIntensity(float ambientIntensity)
{
	_ambientIntensity = ambientIntensity;
}

void Light::SetDiffuseIntensity(float diffuseIntensity)
{
	_diffuseIntensity = diffuseIntensity;
}


void Light::SetSpecularIntensity(float specularIntensity)
{
	_specularIntensity = specularIntensity;
}

void Light::SetShinIness(float shinelness)
{
	_shinIness = shinelness;
}

void Light::SetLightColor(glm::vec3 lightcolor)
{
	_lightColor = lightcolor;
}

void Light::UseLight(Shader& shader)
{


	shader.SetUniform3f("u_light.lightColor", _lightColor.r, _lightColor.g, _lightColor.b);
	shader.SetUniform1f("u_light.ambientIntensity", _ambientIntensity);

	shader.SetUniform3f("u_light.direction", _lvector.x, _lvector.y, _lvector.z);
	shader.SetUniform1f("u_light.diffuseIntensity", _diffuseIntensity);

	shader.SetUniform1f("u_light.specularIntensity", _specularIntensity);
	shader.SetUniform1f("u_light.shinIness", _shinIness);


}

