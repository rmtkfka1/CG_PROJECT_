#version 330 core


out vec4 color;  
in vec2 v_TexCoord;


uniform sampler2D u_text_texture;
void main()
{
	color = texture(u_text_texture, v_TexCoord);
};
