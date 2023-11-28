#include "pch.h"
#include "Light2.h"

Light2::Light2()
{
	
	_light.position = glm::vec3(-9.8f, 5.9f, -3.3f);
	_light.direction = glm::vec3(1.0f, 1.0f, 1.0f);

	_light.cutoff = glm::vec2(-10.0f, 741.0f);
	_light.distance = 1000.0f;


	_light.ambient = glm::vec3(0.01f, 0.01f, 0.01f);
	_light.diffuse = glm::vec3(0.5f, 0.5f, 0.5f);
	_light.specular = glm::vec3(0.1f, 0.1f, 0.1f);


	_material.shininess = 20.0f;
	_material.specular = glm::vec3(1.0f, 1.0f, 1.0f);




}

Light2::~Light2()
{

}

void Light2::UseSpotLight(Shader& shader)
{


	shader.Bind();
	shader.SetUniform3f("u_light.attenuation", GetAttenuationCoeff(_light.distance).x, GetAttenuationCoeff(_light.distance).y, GetAttenuationCoeff(_light.distance).z);
	shader.SetUniform3f("u_light.position", _light.position.x, _light.position.y ,_light.position.z);
	shader.SetUniform3f("u_light.ambient", _light.ambient.r, _light.ambient.g, _light.ambient.b);

	shader.SetUniform3f("u_light.direction", _light.direction.x, _light.direction.y, _light.direction.z);
	shader.SetUniform2fv("u_light.cutoff", glm::vec2(glm::cos(glm::radians(_light.cutoff[0])), glm::cos(glm::radians(_light.cutoff[1] + _light.cutoff[0]))));

	shader.SetUniform3f("u_light.diffuse", _light.diffuse.r , _light.diffuse.g ,_light.diffuse.b );
	shader.SetUniform3f("u_light.specular", _light.specular.r, _light.specular.g, _light.specular.b);
	////shader.SetUniform3f("u_material.specular", _material.specular.r, _material.specular.g, _material.specular.b);
	shader.SetUniform1f("u_material.shininess", _material.shininess);


}

void Light2::SetLightPos(glm::vec3 pos)
{
	_light.position = pos;
}

void Light2::SetLightAmbient(glm::vec3 sa)
{
	_light.ambient = sa;
}

void Light2::SetLightDiffuse(glm::vec3 sd)
{
	_light.diffuse = sd;
}

void Light2::SetLightSpecular(glm::vec3 ss)
{
	_light.specular = ss;
}


void Light2::SetMaterialSpecular(glm::vec3 ms)
{
	_material.specular = ms;
}

void Light2::SetShininess(float shininess)
{

	_material.shininess = shininess;


}

