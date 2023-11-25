#version 330 core

in vec3 v_normal;
in vec3 v_position;
in vec2 v_texcoord;

out vec4 fragcolor;

struct Light {
    vec3 position; // 광원의 위치
    vec3 direction;
    vec2 cutoff;
    vec3 attenuation;
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


    float dist =length(u_light.position - v_position);
    vec3 distpoly = vec3(1.0,dist,dist*dist);
    float attenuation = 1.0/dot(distpoly,u_light.attenuation);
    vec3 lightdir = (u_light.position - v_position)/dist;
   
 
    float theta = dot(lightdir,normalize(-u_light.direction));
    vec3 result = ambient;

    float intensity = clamp((theta-u_light.cutoff[1]) / (u_light.cutoff[0]- u_light.cutoff[1]),0.0,1.0);


    if(intensity>0.0)
    {
         vec3 pixelnorm = normalize(v_normal);
         
        float diff = max(dot(pixelnorm, lightdir), 0.0);
        vec3 diffuse = diff * textcolor * u_light.diffuse;

        vec3 specColor = texture2D(u_texture,v_texcoord).xyz;
        vec3 viewdir = normalize(u_viewpos - v_position);
        vec3 reflectdir = reflect(-lightdir, pixelnorm);
        float spec = pow(max(dot(viewdir, reflectdir), 0.0), u_material.shininess);
        vec3 specular = spec * specColor * u_light.specular;

        result += (diffuse +specular) * intensity;   
    }


    result *= attenuation;
    fragcolor = vec4(result,1.0) + vec4(control_color,1);


}