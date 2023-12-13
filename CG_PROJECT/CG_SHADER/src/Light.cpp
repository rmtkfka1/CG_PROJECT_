#include "pch.h"
#include "Light.h"

Light_test::Light_test()
{
	_lightColor = glm::vec3(1.0f, 1.0f, 1.0f) ;
	_ambientIntensity = 0.0f;

	_lvector = glm::vec3(1.0f, 1.0f, 1.0);
	_diffuseIntensity =10.0f;

	_specularIntensity = 0.1f;
	_shinIness =1.0f;

}

Light_test::~Light_test()
{

}


void Light_test::SetLvector(glm::vec3 lvector)
{
	_lvector = glm::normalize(lvector);
}


void Light_test::SetAmbientIntensity(float ambientIntensity)
{
	_ambientIntensity = ambientIntensity;
}

void Light_test::SetDiffuseIntensity(float diffuseIntensity)
{
	_diffuseIntensity = diffuseIntensity;
}


void Light_test::SetSpecularIntensity(float specularIntensity)
{
	_specularIntensity = specularIntensity;
}

void Light_test::SetShinIness(float shinelness)
{
	_shinIness = shinelness;
}

void Light_test::SetLightColor(glm::vec3 lightcolor)
{
	_lightColor = lightcolor;
}

void Light_test::UseLight(Shader& shader)
{


	shader.SetUniform3f("u_light.lightColor", _lightColor.r, _lightColor.g, _lightColor.b);
	shader.SetUniform1f("u_light.ambientIntensity", _ambientIntensity);

	shader.SetUniform3f("u_light.direction", _lvector.x, _lvector.y, _lvector.z);
	shader.SetUniform1f("u_light.diffuseIntensity", _diffuseIntensity);

	shader.SetUniform1f("u_light.specularIntensity", _specularIntensity);
	shader.SetUniform1f("u_light.shinIness", _shinIness);


}

