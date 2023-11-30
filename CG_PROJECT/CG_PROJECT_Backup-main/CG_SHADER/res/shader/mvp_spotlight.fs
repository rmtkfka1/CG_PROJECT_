#version 330 core

in vec3 v_normal;
in vec3 v_position;
in vec2 v_texcoord;

out vec4 fragcolor;

// 스폿라이트를 구현하기 위한 변수들
struct Spot_Light 
{
    vec3 position; 
    vec3 direction;
    vec2 cutoff;
    vec3 attenuation;
    vec3 ambient;  
    vec3 diffuse;
    vec3 specular;
}; 

struct Material
{
    vec3 specular;
    float shininess;
}; 

uniform Spot_Light spot_light;

// 공용 변수
uniform Material material;
uniform sampler2D u_texture;
uniform vec3 control_color;
uniform vec3 u_viewpos;

vec3 Calculate_spot_light()
{
    vec3 textcolor = texture(u_texture, v_texcoord).xyz;
    vec3 ambient = textcolor * spot_light.ambient;

    float dist = length(spot_light.position - v_position);
    vec3 distpoly = vec3(1.0, dist, dist * dist);
    float attenuation = 1.0 / dot(distpoly, spot_light.attenuation);
    vec3 lightdir = (spot_light.position - v_position) / dist;
   
    float theta = dot(lightdir, normalize(-spot_light.direction));
    vec3 result = ambient;

    float intensity = clamp((theta - spot_light.cutoff[1]) / (spot_light.cutoff[0] - spot_light.cutoff[1]), 0.0, 1.0);

    if (intensity > 0.0)
    {
        vec3 pixelnorm = normalize(v_normal);
        float diff = max(dot(pixelnorm, lightdir), 0.0);
        vec3 diffuse = diff * textcolor * spot_light.diffuse;

        vec3 specColor = texture(u_texture, v_texcoord).xyz;
        vec3 viewdir = normalize(u_viewpos - v_position);
        vec3 reflectdir = reflect(-lightdir, pixelnorm);
        float spec = pow(max(dot(viewdir, reflectdir), 0.0), material.shininess);
        vec3 specular = spec * specColor * spot_light.specular;

        result += (diffuse + specular) * intensity;   
    }
    
    result *= attenuation;

    return result;
}

// 포인트 라이트 구현하기 위한 변수들
struct Point_Light 
{
    vec3 position[3]; 
    vec3 attenuation[3];
    vec3 ambient;  
    vec3 diffuse;
    vec3 specular;
}; 

uniform Point_Light point_light;

vec3 Calculate_point_light(int i)
{
    vec3 textcolor = texture(u_texture, v_texcoord).xyz;
    vec3 ambient = textcolor * point_light.ambient;

    float dist = length(point_light.position[i] - v_position);
    vec3 distpoly = vec3(1.0, dist, dist * dist);
    float attenuation = 1.0 / dot(distpoly, point_light.attenuation[i]);
    vec3 lightdir = (point_light.position[i] - v_position) / dist;
    vec3 pixelnorm = normalize(v_normal);

    // 디퓨즈항 계산
    float diff = max(dot(pixelnorm, lightdir), 0.0);
    vec3 diffuse = diff * textcolor * point_light.diffuse;

    // 스펙큘러항 계산
    vec3 viewdir = normalize(u_viewpos - v_position);
    vec3 reflectdir = reflect(-lightdir, pixelnorm);
    float spec = pow(max(dot(viewdir, reflectdir), 0.0), material.shininess);
    vec3 specular = spec * material.specular * point_light.specular;

    vec3 result = (ambient + diffuse + specular) * attenuation;

    return result;
}

void main() 
{
    vec3 spot_result = Calculate_spot_light();

    vec3 point_result = vec3(0.0);
    for (int i = 0; i < 3; ++i)
    {
        point_result += Calculate_point_light(i);
    }

    fragcolor = vec4(spot_result + point_result + control_color, 1.0);
}

