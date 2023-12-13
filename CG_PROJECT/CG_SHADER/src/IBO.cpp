#include "pch.h"
#include "IBO.h"




IBO::IBO(const unsigned int* data, unsigned int count)
	: m_Count{ count }
{
	ASSERT(sizeof(unsigned int) == sizeof(GLuint));
	GLCall(glGenBuffers(1, &m_RendererID)); //1. 버퍼 생성
	GLCall(glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, m_RendererID)); //2. 바인딩("작업 상태")
	GLCall(glBufferData(GL_ELEMENT_ARRAY_BUFFER, count * sizeof(unsigned int), data, GL_STATIC_DRAW));  //3. 작업 상태 버퍼에 데이터 전달
}

IBO::~IBO()
{
	GLCall(glDeleteBuffers(1, &m_RendererID));
}



void IBO::Bind() const
{
	GLCall(glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, m_RendererID)); //바인딩("작업 상태")
}

void IBO::Unbind() const
{
	GLCall(glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0)); //언바인딩
}

void IBO::Delete() const
{
	GLCall(glDeleteBuffers(1, &m_RendererID));
}

