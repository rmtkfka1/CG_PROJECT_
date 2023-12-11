#version 330

//Model 클래스를 보면 3개의 좌표, 2개의 텍스처 좌표, 3개의 법선 벡터 데이터를 넘겨주는 것을 알 수 있음
//이런 순서로 넘어오도록 우리가 vertex buffer layout을 통해 정의했음
layout(location = 0) in vec3 position; 
layout(location = 1) in vec2 texCoord;
layout(location = 2) in vec3 normal;

out vec2 v_TexCoord; //버텍스 셰이더에서 추가적으로 출력하는 데이터(varying)
out vec3 v_Normal;
out vec3 v_worldPosition;

uniform mat4 u_model; //world 변환 행렬
uniform mat4 u_view; //카메라를 통해 변화된 View 행렬
uniform mat4 u_proj; //CPU에서 전달될 (glm 라이브러리를 통해 생성된) 투영 행렬

void main()
{

	gl_Position = u_proj * u_view * u_model * vec4(position,1.0); // 정점 위치를 투영 행렬과 곱
	v_TexCoord = texCoord; //vertex 변환에 따라 바뀌지 않으므로 그대로 넘겨주면 됨
	v_Normal = mat3(transpose(inverse(u_model)))*normal;

	v_worldPosition = (u_model * vec4(position, 1.0)).xyz; //정점의 World space 좌표

};