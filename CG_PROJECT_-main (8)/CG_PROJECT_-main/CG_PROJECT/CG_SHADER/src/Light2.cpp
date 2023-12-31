#include "pch.h"
#include "Light2.h"
#include "Ghost.h"
Light2::Light2()
{

	//스폿 라이트 작업//
	
	Spot_light.position = glm::vec3(-9.8f, 5.9f, -3.3f);
	Spot_light.direction = glm::vec3(0, 0, 0);

	Spot_light.cutoff = glm::vec2(-14.0f, 31.0f); //-10 /30
	Spot_light.distance = 0.1f;


	Spot_light.ambient = glm::vec3(0.01f, 0.01f, 0.01f);
	Spot_light.diffuse = glm::vec3(1.0f, 1.0f, 1.0f);
	Spot_light.specular = glm::vec3(0, 0, 10.0f);

	material.shininess = 1.0f;
	material.specular = glm::vec3(1.0f, 1.0f, 1.0f);


	//포인트 라이트 작업
	//200 -215 250
	point_light.position[8] = glm::vec3(0, 300, 0); //첫번쨰방조명
	point_light.position[7] = glm::vec3(0, 22.0f, 200.0f); //첫번쨰방조명
	point_light.position[0] = glm::vec3(0, 22.0f, 140.0f);
	point_light.position[1] = glm::vec3(0, 22.0f, -250.0f);
	point_light.position[2] = glm::vec3(-413.0f, 35.0f, -294.0f); //왼쪽 입구
	point_light.position[3] = glm::vec3(414.0f, 35.0f, -287.0f); //오른쪽 입구
	point_light.position[4] = glm::vec3(3.7f, 35.0f, -406.0f); //복도중앙홀
	point_light.position[5] = glm::vec3(1.7f, 35.0f, -665.0f); //출구조명
	point_light.position[6] = glm::vec3(0, 0, 0); //귀신대가리에 빨간불


	point_light.distance = 300.0f;


	point_light.diffuse = glm::vec3(1.0f,1.0f, 1.0f);
	point_light.ambient = glm::vec3(0, 0, 0);
	point_light.specular = glm::vec3(1.0f, 1.0f, 1.0f);



}

Light2::~Light2()
{

}

void Light2::UseSpotLight(Shader& shader,Ghost& ghost)
{

	point_light.position[6].x = ghost._pos.x;
	point_light.position[6].y = ghost._pos.y+60;
	point_light.position[6].z = ghost._pos.z + 10;

	shader.Bind();
	shader.SetUniform3f("spot_light.attenuation", GetAttenuationCoeff(Spot_light.distance).x, GetAttenuationCoeff(Spot_light.distance).y, GetAttenuationCoeff(Spot_light.distance).z);
	shader.SetUniform3f("spot_light.position", Spot_light.position.x, Spot_light.position.y ,Spot_light.position.z);
	shader.SetUniform3f("spot_light.ambient", Spot_light.ambient.r, Spot_light.ambient.g, Spot_light.ambient.b);

	shader.SetUniform3f("spot_light.direction", Spot_light.direction.x, Spot_light.direction.y, Spot_light.direction.z);
	shader.SetUniform2fv("spot_light.cutoff", glm::vec2(glm::cos(glm::radians(Spot_light.cutoff[0])), glm::cos(glm::radians(Spot_light.cutoff[1] + Spot_light.cutoff[0]))));

	shader.SetUniform3f("spot_light.diffuse", Spot_light.diffuse.r , Spot_light.diffuse.g ,Spot_light.diffuse.b );
	shader.SetUniform3f("spot_light.specular", Spot_light.specular.r, Spot_light.specular.g, Spot_light.specular.b);




	shader.SetUniform3f("point_light.attenuation", GetAttenuationCoeff(point_light.distance).x, GetAttenuationCoeff(point_light.distance).y, GetAttenuationCoeff(point_light.distance).z);
	shader.SetUniform3f("point_light.position[0]", point_light.position[0].x, point_light.position[0].y, point_light.position[0].z);
	shader.SetUniform3f("point_light.position[1]", point_light.position[1].x, point_light.position[1].y, point_light.position[1].z);
	shader.SetUniform3f("point_light.position[2]", point_light.position[2].x, point_light.position[2].y, point_light.position[2].z);
	shader.SetUniform3f("point_light.position[3]", point_light.position[3].x, point_light.position[3].y, point_light.position[3].z);
	shader.SetUniform3f("point_light.position[4]", point_light.position[4].x, point_light.position[4].y, point_light.position[4].z);
	shader.SetUniform3f("point_light.position[5]", point_light.position[5].x, point_light.position[5].y, point_light.position[5].z);
	shader.SetUniform3f("point_light.position[6]", point_light.position[6].x, point_light.position[6].y, point_light.position[6].z);
	shader.SetUniform3f("point_light.position[7]", point_light.position[7].x, point_light.position[7].y, point_light.position[7].z);
	shader.SetUniform3f("point_light.position[8]", point_light.position[8].x, point_light.position[8].y, point_light.position[8].z);

	shader.SetUniform3f("point_light.ambient", point_light.ambient.r, point_light.ambient.g, point_light.ambient.b);
	shader.SetUniform3f("point_light.diffuse", point_light.diffuse.r, point_light.diffuse.g, point_light.diffuse.b);
	shader.SetUniform3f("point_light.specular", point_light.specular.r, point_light.specular.g, point_light.specular.b);


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

