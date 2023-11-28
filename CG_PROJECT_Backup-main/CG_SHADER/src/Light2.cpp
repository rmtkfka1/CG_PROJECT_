#include "pch.h"
#include "Light2.h"

Light2::Light2()
{
	
	Spot_light.position = glm::vec3(-9.8f, 5.9f, -3.3f);
	Spot_light.direction = glm::vec3(1.0f, 1.0f, 1.0f);

	Spot_light.cutoff = glm::vec2(-10.0f, 350.0f);
	Spot_light.distance = 300.0f;


	Spot_light.ambient = glm::vec3(0.01f, 0.01f, 0.01f);
	Spot_light.diffuse = glm::vec3(0.5f, 0.5f, 0.5f);
	Spot_light.specular = glm::vec3(0.1f, 0.1f, 0.1f);

	Spot_material.shininess = 20.0f;
	Spot_material.specular = glm::vec3(1.0f, 1.0f, 1.0f);




}

Light2::~Light2()
{

}

void Light2::UseSpotLight(Shader& shader)
{


	shader.Bind();
	shader.SetUniform3f("u_light.attenuation", GetAttenuationCoeff(Spot_light.distance).x, GetAttenuationCoeff(Spot_light.distance).y, GetAttenuationCoeff(Spot_light.distance).z);
	shader.SetUniform3f("u_light.position", Spot_light.position.x, Spot_light.position.y ,Spot_light.position.z);
	shader.SetUniform3f("u_light.ambient", Spot_light.ambient.r, Spot_light.ambient.g, Spot_light.ambient.b);

	shader.SetUniform3f("u_light.direction", Spot_light.direction.x, Spot_light.direction.y, Spot_light.direction.z);
	shader.SetUniform2fv("u_light.cutoff", glm::vec2(glm::cos(glm::radians(Spot_light.cutoff[0])), glm::cos(glm::radians(Spot_light.cutoff[1] + Spot_light.cutoff[0]))));

	shader.SetUniform3f("u_light.diffuse", Spot_light.diffuse.r , Spot_light.diffuse.g ,Spot_light.diffuse.b );
	shader.SetUniform3f("u_light.specular", Spot_light.specular.r, Spot_light.specular.g, Spot_light.specular.b);
	////shader.SetUniform3f("u_material.specular", _material.specular.r, _material.specular.g, _material.specular.b);
	shader.SetUniform1f("u_material.shininess", Spot_material.shininess);


}

void Light2::UsePointLight(Shader& shader)
{
	shader.Bind();
	shader.SetUniform3f("u_light.position", Spot_light.position.x, Spot_light.position.y, Spot_light.position.z);
	shader.SetUniform3f("u_light.attenuation", GetAttenuationCoeff(Spot_light.distance).x, GetAttenuationCoeff(Spot_light.distance).y, GetAttenuationCoeff(Spot_light.distance).z);
	shader.SetUniform3f("u_light.ambient", Spot_light.ambient.r, Spot_light.ambient.g, Spot_light.ambient.b);
	shader.SetUniform3f("u_light.diffuse", Spot_light.diffuse.r, Spot_light.diffuse.g, Spot_light.diffuse.b);
	shader.SetUniform3f("u_light.specular", Spot_light.specular.r, Spot_light.specular.g, Spot_light.specular.b);
	shader.SetUniform1f("u_material.shininess", Spot_material.shininess);
}

void Light2::SetLightPos(glm::vec3 pos)
{
	Spot_light.position = pos;
}

void Light2::SetLightAmbient(glm::vec3 sa)
{
	Spot_light.ambient = sa;
}

void Light2::SetLightDiffuse(glm::vec3 sd)
{
	Spot_light.diffuse = sd;
}

void Light2::SetLightSpecular(glm::vec3 ss)
{
	Spot_light.specular = ss;
}


void Light2::SetMaterialSpecular(glm::vec3 ms)
{
	Spot_material.specular = ms;
}

void Light2::SetShininess(float shininess)
{

	Spot_material.shininess = shininess;


}

