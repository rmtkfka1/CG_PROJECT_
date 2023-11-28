#pragma once

class Texture
{
public:
	Texture(const std::string& path);
	~Texture();

	void Bind(unsigned int slot = 0); //텍스처를 바인딩할 슬롯. GPU에 따라 숫자 제한이 있음
	void Unbind() const;
	inline int GetWidth() const { return m_Width; }
	inline int GetHeight() const { return m_Height; }

	int GetSlot() { return m_slot; }

private:
	unsigned int m_RendererID; //이전과 마찬가지로 텍스처 객체에 대한 ID 저장
	std::string m_FilePath;    //텍스처(이미지) 파일 경로
	unsigned char* m_LocalBuffer; //텍스처 데이터
	int m_Width, m_Height, m_BPP; //텍스처 정보, BPP(bits per channel)
	int m_slot;

};