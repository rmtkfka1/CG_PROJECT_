#version 330

layout(location = 0) out vec4 color;

in vec2 v_TexCoord; //버텍스 셰이더에서 넘겨받은 데이터
in vec3 v_Normal;

uniform sampler2D u_texture; //texture는 sampler2D 타입
uniform vec3 control_color;

void main()
{
	//--빨간색으로 표시해 보기
	//color = vec4(1.0, 0.0, 0.0, 1.0);

	//--normal을 색상으로 표시해 보기


	//--uvchecker 입혀 보기, 왜 어떤 부분은 검은색으로 보일까?
	color = texture(u_texture, v_TexCoord) + vec4(control_color,0);

	//color = v_Color;
};