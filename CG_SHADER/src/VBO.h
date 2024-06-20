#pragma once
class VBO
{

public:

	VBO(const void* data, unsigned int size); //size는 byte 사이즈, 데이터의 타입은 모르기 때문에 void*로.
	~VBO();


	void Bind() const;
	void Unbind() const;
	void Delete() const;
	
	const unsigned int GetID() { return m_RendererID; }
private:

	unsigned int m_RendererID{};

};

