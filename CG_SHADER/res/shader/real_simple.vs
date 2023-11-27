#version 330

//Model 클래스를 보면 3개의 좌표, 2개의 텍스처 좌표, 3개의 법선 벡터 데이터를 넘겨주는 것을 알 수 있음
//이런 순서로 넘어오도록 우리가 vertex buffer layout을 통해 정의했음
layout(location = 0) in vec3 position; 
layout(location = 1) in vec2 texCoord;
layout(location = 2) in vec3 normal;

out vec2 v_TexCoord; 
out vec3 v_Normal;


void main()
{
	gl_Position = vec4(position,1.0f); // 정점 위치를 투영 행렬과 곱
	v_TexCoord = texCoord;
	v_Normal = normal;
};
