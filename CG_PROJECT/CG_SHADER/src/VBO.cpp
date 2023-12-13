#include "pch.h"
#include "VBO.h"



VBO::VBO(const void* data, unsigned int size)
{
	
	GLCall(glGenBuffers(1, &m_RendererID)); //1. 버퍼 생성
	GLCall(glBindBuffer(GL_ARRAY_BUFFER, m_RendererID)); //2. 바인딩("작업 상태")
	GLCall(glBufferData(GL_ARRAY_BUFFER, size, data, GL_DYNAMIC_DRAW));  //3. 작업 상태 버퍼에 데이터 전달
}

VBO::~VBO()
{
	GLCall(glDeleteBuffers(1, &m_RendererID));
}



void VBO::Bind() const
{
	GLCall(glBindBuffer(GL_ARRAY_BUFFER, m_RendererID)); //바인딩("작업 상태")
}

void VBO::Unbind() const
{
	GLCall(glBindBuffer(GL_ARRAY_BUFFER, 0)); //언바인딩
}

void VBO::Delete() const
{
	GLCall(glDeleteBuffers(1, &m_RendererID));
}
