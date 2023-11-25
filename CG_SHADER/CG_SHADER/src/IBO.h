#pragma once
class IBO
{

public:
	IBO(const unsigned int* data, unsigned int count); //index는 (대부분) unsigned int* 타입. count는 갯수(size와 다름)
	~IBO();

	void Bind() const;
	void Unbind() const;
	void Delete() const;

	const int GetID() { return m_RendererID; }
	inline unsigned int GetCount() const { return m_Count; }

private:
	unsigned int m_RendererID;
	unsigned int m_Count;
};
