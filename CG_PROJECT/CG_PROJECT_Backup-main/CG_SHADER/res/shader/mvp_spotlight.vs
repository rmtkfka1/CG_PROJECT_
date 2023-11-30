#version 330 core

layout (location = 0) in vec3 a_position;
layout (location = 1) in vec2 a_texcoord;
layout (location = 2) in vec3 a_normal;

uniform mat4 u_model;
uniform mat4 u_view;
uniform mat4 u_proj;

out vec3 v_normal;
out vec2 v_texcoord;
out vec3 v_position;

void main() {
    gl_Position = u_proj * u_view * u_model * vec4(a_position, 1.0); 
    v_normal = (transpose(inverse(u_model)) * vec4(a_normal, 1.0)).xyz;
    v_texcoord = a_texcoord;
    v_position = (u_model * vec4(a_position, 1.0)).xyz;
}