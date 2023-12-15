#include "pch.h"
#include "VAO.h"
#include "VBO.h"
#include "VertexBufferLayout.h"
VAO::VAO()
{
	GLCall(glGenVertexArrays(1, &m_RendererID)); //vao 생성
}

VAO::~VAO()
{
	GLCall(glDeleteVertexArrays(1, &m_RendererID));

}



void VAO::AddBuffer(const VBO& vb, const VertexBufferLayout& layout)
{

	this->Bind(); //vao를 바인딩

	vb.Bind(); //Vertex Buffer를 바인딩

	const auto& elements = layout.GetVector();

	unsigned int offset = 0;
	for (int i = 0; i < elements.size(); i++)
	{
		const auto& element = elements[i];
		GLCall(glEnableVertexAttribArray(i)); //기존에는 0번만 존재했으나, position/normal/color등 여러 attribute가 생기면, 여러 attribute를 enable해야함
		GLCall(glVertexAttribPointer(i, element.count, element.type, element.normalized, layout.GetStride(), (const void*)offset)); //layout별로 데이터를 어떻게 읽어와야하는지를 element구조체로 가지고 있을 예정. 이를 활용함.
		offset += element.count * VertexBufferElement::GetSizeOfType(element.type);


	}

}


void VAO::Bind() const
{

	GLCall(glBindVertexArray(m_RendererID));
}

void VAO::Unbind() const
{
	GLCall(glBindVertexArray(0));
}

void VAO::Delete() const
{
	Unbind();
	GLCall(glDeleteVertexArrays(1, &m_RendererID));

}
