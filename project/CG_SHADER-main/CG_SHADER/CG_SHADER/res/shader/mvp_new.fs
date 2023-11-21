#version 330

layout(location = 0) out vec4 color;

struct light
{

	vec3 lightColor; 
	float ambientIntensity;

	vec3 direction;
	float diffuseIntensity;

	float specularIntensity;
	float shinIness; //sh
};


in vec2 v_TexCoord; 
in vec3 v_Normal;
in vec3 v_worldPosition;




uniform sampler2D u_texture;
uniform light u_light;
uniform vec3 control_color;
uniform vec3 u_eyePosition; //specular 계산을 위한 카메라 위치

void main()
{
	//앰비언트
	vec3 lightAmbient = u_light.lightColor * u_light.ambientIntensity;



	vec3 lightDir = normalize(-u_light.direction);
	//디퓨즈

	float diffuseFactor = max(dot(normalize(v_Normal), lightDir), 0.0);
	vec3 lightDiffuse = u_light.lightColor * u_light.diffuseIntensity * diffuseFactor;



	//스펙큘러
	vec3 fragToEye = normalize(u_eyePosition - v_worldPosition);
	vec3 rVec = 2.0 * v_Normal * dot(v_Normal, lightDir) - lightDir; //r vector 계산
	vec3 lightSpecular = pow(max(dot(rVec, fragToEye), 0.0), u_light.shinIness) * u_light.lightColor * u_light.specularIntensity;

	color = texture(u_texture, v_TexCoord)* vec4(lightAmbient+lightDiffuse +lightSpecular ,1.0) + vec4(control_color,1);


};