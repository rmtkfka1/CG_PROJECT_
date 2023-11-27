#version 330

//Model Ŭ������ ���� 3���� ��ǥ, 2���� �ؽ�ó ��ǥ, 3���� ���� ���� �����͸� �Ѱ��ִ� ���� �� �� ����
//�̷� ������ �Ѿ������ �츮�� vertex buffer layout�� ���� ��������
layout(location = 0) in vec3 position; 
layout(location = 1) in vec2 texCoord;
layout(location = 2) in vec3 normal;

out vec2 v_TexCoord; 
out vec3 v_Normal;


void main()
{
	gl_Position = vec4(position,1.0f); // ���� ��ġ�� ���� ��İ� ��
	v_TexCoord = texCoord;
	v_Normal = normal;
};
