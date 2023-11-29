#pragma once


class VertexBufferLayout;
class VBO;

class VAO
{

public:
	VAO();
	~VAO();


	void AddBuffer(const VBO& vb, const VertexBufferLayout& layout);

	void Bind() const;
	void Unbind() const;
	void Delete() const;

	const unsigned int GetID() { return m_RendererID; }


private:
	unsigned int m_RendererID{};


};