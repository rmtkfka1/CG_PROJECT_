#include "pch.h"
#include "Light2.h"

Light2::Light2()
{

	//스폿 라이트 작업//
	
	Spot_light.position = glm::vec3(-9.8f, 5.9f, -3.3f);
	Spot_light.direction = glm::vec3(0, 0, 0);

	Spot_light.cutoff = glm::vec2(-10.0f, 30.0f);
	Spot_light.distance = 400.0f;


	Spot_light.ambient = glm::vec3(0.01f, 0.01f, 0.01f);
	Spot_light.diffuse = glm::vec3(1.0f, 1.0f, 1.0f);
	Spot_light.specular = glm::vec3(0.1, 0.1, 0.1);

	material.shininess = 1.0f;
	material.specular = glm::vec3(1.0f, 1.0f, 1.0f);


	//포인트 라이트 작업

	point_light.position = glm::vec3(0, 22.0f, 0);
	point_light.distance = 100.0f;
	point_light.diffuse = glm::vec3(1.0f, 0, 0);
	point_light.ambient = glm::vec3(0, 0, 0);
	point_light.specular = glm::vec3(0, 0, 0);



}

Light2::~Light2()
{

}

void Light2::UseSpotLight(Shader& shader)
{


	shader.Bind();
	shader.SetUniform3f("spot_light.attenuation", GetAttenuationCoeff(Spot_light.distance).x, GetAttenuationCoeff(Spot_light.distance).y, GetAttenuationCoeff(Spot_light.distance).z);
	shader.SetUniform3f("spot_light.position", Spot_light.position.x, Spot_light.position.y ,Spot_light.position.z);
	shader.SetUniform3f("spot_light.ambient", Spot_light.ambient.r, Spot_light.ambient.g, Spot_light.ambient.b);

	shader.SetUniform3f("spot_light.direction", Spot_light.direction.x, Spot_light.direction.y, Spot_light.direction.z);
	shader.SetUniform2fv("spot_light.cutoff", glm::vec2(glm::cos(glm::radians(Spot_light.cutoff[0])), glm::cos(glm::radians(Spot_light.cutoff[1] + Spot_light.cutoff[0]))));

	shader.SetUniform3f("spot_light.diffuse", Spot_light.diffuse.r , Spot_light.diffuse.g ,Spot_light.diffuse.b );
	shader.SetUniform3f("spot_light.specular", Spot_light.specular.r, Spot_light.specular.g, Spot_light.specular.b);



	//테스트해보자
	shader.SetUniform3f("point_light.attenuation", GetAttenuationCoeff(point_light.distance).x, GetAttenuationCoeff(point_light.distance).y, GetAttenuationCoeff(point_light.distance).z);
	shader.SetUniform3f("point_light.position", point_light.position.x, point_light.position.y, point_light.position.z);
	shader.SetUniform3f("point_light.ambient", point_light.ambient.r, point_light.ambient.g, point_light.ambient.b);
	shader.SetUniform3f("point_light.diffuse", point_light.diffuse.r, point_light.diffuse.g, point_light.diffuse.b);
	shader.SetUniform3f("point_light.specular", point_light.specular.r, point_light.specular.g, point_light.specular.b);


	shader.SetUniform1f("material.shininess", material.shininess);



}

void Light2::UsePointLight(Shader& shader)
{
	shader.Bind();
	shader.SetUniform3f("u_light.position", Spot_light.position.x, Spot_light.position.y, Spot_light.position.z);
	shader.SetUniform3f("u_light.attenuation", GetAttenuationCoeff(Spot_light.distance).x, GetAttenuationCoeff(Spot_light.distance).y, GetAttenuationCoeff(Spot_light.distance).z);
	shader.SetUniform3f("u_light.ambient", Spot_light.ambient.r, Spot_light.ambient.g, Spot_light.ambient.b);
	shader.SetUniform3f("u_light.diffuse", Spot_light.diffuse.r, Spot_light.diffuse.g, Spot_light.diffuse.b);
	shader.SetUniform3f("u_light.specular", Spot_light.specular.r, Spot_light.specular.g, Spot_light.specular.b);
	shader.SetUniform1f("material.shininess", material.shininess);
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
	material.specular = ms;
}

void Light2::SetShininess(float shininess)
{

	material.shininess = shininess;


}

