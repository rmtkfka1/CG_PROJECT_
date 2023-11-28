#version 330 core

in vec3 v_normal;
in vec3 v_position;
in vec2 v_texcoord;

out vec4 fragcolor;

struct Spot_Light {
    vec3 position; 
    vec3 direction;
    vec2 cutoff;
    vec3 attenuation;
    vec3 ambient;  
    vec3 diffuse;
    vec3 specular;

}; 

struct Spot_Material
{
    vec3 specular;
    float shininess;
}; 

uniform Spot_Light spot_light;
uniform Spot_Material spot_material;
uniform vec3 u_viewpos;
uniform vec3 control_color;
uniform sampler2D u_texture;


vec3 Calculate_spot_light()
{
    vec3 textcolor = texture(u_texture, v_texcoord).xyz;

    vec3 ambient = textcolor * spot_light.ambient;


    float dist =length(spot_light.position - v_position);
    vec3 distpoly = vec3(1.0,dist,dist*dist);
    float attenuation = 1.0/dot(distpoly,spot_light.attenuation);
    vec3 lightdir = (spot_light.position - v_position)/dist;
   
 
    float theta = dot(lightdir,normalize(-spot_light.direction));
    vec3 result = ambient;

    float intensity = clamp((theta-spot_light.cutoff[1]) / (spot_light.cutoff[0]- spot_light.cutoff[1]),0.0,1.0);


    if(intensity>0.0)
    {
         vec3 pixelnorm = normalize(v_normal);
         
        float diff = max(dot(pixelnorm, lightdir), 0.0);
        vec3 diffuse = diff * textcolor * spot_light.diffuse;

        vec3 specColor = texture2D(u_texture,v_texcoord).xyz;
        vec3 viewdir = normalize(u_viewpos - v_position);
        vec3 reflectdir = reflect(-lightdir, pixelnorm);
        float spec = pow(max(dot(viewdir, reflectdir), 0.0), spot_material.shininess);
        vec3 specular = spec * specColor * spot_light.specular;

        result += (diffuse +specular) * intensity;   
    }
    
    result *= attenuation;

    return result;


}

void main() 
{
  

    vec3 spot_result = Calculate_spot_light();



    fragcolor = vec4(spot_result,1.0) + vec4(control_color,1);

}