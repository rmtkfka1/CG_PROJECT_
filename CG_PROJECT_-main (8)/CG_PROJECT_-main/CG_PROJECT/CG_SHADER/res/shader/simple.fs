#version 330 core

in vec3 v_normal;
in vec3 v_position;
in vec2 v_texcoord;

out vec4 fragcolor;

struct Light {
    vec3 position; // 광원의 위치
    vec3 ambient;  
    vec3 diffuse;
    vec3 specular;

}; // <- 세미콜론 추가

struct Material
{
    vec3 specular;
    float shininess;
}; // <- 세미콜론 추가

uniform Light u_light;
uniform Material u_material;
uniform vec3 u_viewpos;
uniform vec3 control_color;
uniform sampler2D u_texture;

void main() {
    vec3 textcolor = texture(u_texture, v_texcoord).xyz;

    vec3 ambient = textcolor * u_light.ambient;

    vec3 lightdir = normalize(u_light.position - v_position);
    vec3 pixelnorm = normalize(v_normal);

    // 디퓨즈항 계산 //
    float diff = max(dot(pixelnorm, lightdir), 0.0);
    vec3 diffuse = diff * textcolor * u_light.diffuse;

    // 스펙큘러항 계산 //
    vec3 viewdir = normalize(u_viewpos - v_position);
    vec3 reflectdir = reflect(-lightdir, pixelnorm);
    float spec = pow(max(dot(viewdir, reflectdir), 0.0), u_material.shininess);
    vec3 specular = spec * u_material.specular * u_light.specular;

    vec3 result = ambient + diffuse + specular + control_color;

    fragcolor = vec4(result, 1.0);
}