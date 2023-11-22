#include "pch.h"
#include "Shader.h"


Shader::Shader(const std::string& filepath, const std::string& filepath2)
	:m_FilePath_vs{ filepath }, m_FilePath_fs{ filepath2 }, m_RendererID{ 0 }
{
	string vs = ParseShader(filepath);
	string fs = ParseShader(filepath2);

	m_RendererID = CreateShader(vs, fs);
}

Shader::~Shader()
{
	GLCall(glDeleteProgram(m_RendererID));
}

std::string Shader::ParseShader(const std::string& filepath)
{
	std::ifstream fin(filepath);

	if (!fin.is_open())
	{
		std::cerr << "Failed to open file: " << filepath << std::endl;
		exit(1); // 파일 열기 실패 시 빈 문자열 반환
	}

	std::stringstream ss;
	std::string line;

	while (getline(fin, line))
	{
		ss << line << '\n'; // 각 줄을 문자열에 추가하고 줄 바꿈 문자를 포함시킴
	}


	return ss.str(); // 파일 내용을 문자열로 반환
}


unsigned int Shader::CompileShader(unsigned int type, const std::string& source)
{
	unsigned int id = glCreateShader(type); //셰이더 객체 생성(마찬가지)
	const char* src = source.c_str();
	glShaderSource(id, 1, &src, nullptr); // 셰이더의 소스 코드 명시
	glCompileShader(id); // id에 해당하는 셰이더 컴파일

	// Error Handling(없으면 셰이더 프로그래밍할때 괴롭다...)
	int result;
	glGetShaderiv(id, GL_COMPILE_STATUS, &result); //셰이더 프로그램으로부터 컴파일 결과(log)를 얻어옴
	if (result == GL_FALSE) //컴파일에 실패한 경우
	{
		int length;
		glGetShaderiv(id, GL_INFO_LOG_LENGTH, &length); //log의 길이를 얻어옴
		char message[1024];
		glGetShaderInfoLog(id, length, &length, message); //길이만큼 log를 얻어옴
		std::cout << "셰이더 컴파일 실패! " << (type == GL_VERTEX_SHADER ? "vertex" : "fragment") << std::endl;
		std::cout << message << std::endl;
		glDeleteShader(id); //컴파일 실패한 경우 셰이더 삭제
		return 0;
	}

	return id;
}

unsigned int Shader::CreateShader(const std::string& vertexShader, const std::string& fragShader)
{
	unsigned int program = glCreateProgram(); //셰이더 프로그램 객체 생성(int에 저장되는 것은 id)
	unsigned int vs = CompileShader(GL_VERTEX_SHADER, vertexShader);
	unsigned int fs = CompileShader(GL_FRAGMENT_SHADER, fragShader);

	//컴파일된 셰이더 코드를 program에 추가하고 링크
	glAttachShader(program, vs);
	glAttachShader(program, fs);
	glLinkProgram(program);
	glValidateProgram(program);

	//셰이더 프로그램을 생성했으므로 vs, fs 개별 프로그램은 더이상 필요 없음
	glDeleteShader(vs);
	glDeleteShader(fs);

	return program;
}

void Shader::Bind() const
{
	GLCall(glUseProgram(m_RendererID));
}

void Shader::Unbind() const
{
	GLCall(glUseProgram(0));
}

void Shader::SetUniform3f(const std::string& name, float v0, float v1, float v2)
{
	GLCall(glUniform3f(GetUniformLocation(name), v0, v1, v2));
}

void Shader::SetUniform4f(const std::string& name, float v0, float v1, float v2, float v3)
{
	GLCall(glUniform4f(GetUniformLocation(name), v0, v1, v2, v3));
}


void Shader::SetUniform1i(const std::string& name, int value)
{
	glUniform1i(GetUniformLocation(name), value);
}

void Shader::SetUniform1f(const std::string& name, float value)
{
	GLCall(glUniform1f(GetUniformLocation(name), value));
}


void Shader::SetUniformMat4f(const std::string& name, const glm::mat4& matrix)
{
	(glUniformMatrix4fv(GetUniformLocation(name), //v가 붙으면 배열을 의미
		1, //전달할 행렬의 갯수
		GL_FALSE, //transpose 할것인지(row-major order로 저장하는 경우도 많아서)
		glm::value_ptr(matrix))); //첫 인자의 주소값 전달
}

unsigned int Shader::Getid()
{
	return m_RendererID;
}

int Shader::GetUniformLocation(const std::string& name)
{
	//반복해서 uniform을 찾지 않고 map에 저장해둠
	if (m_UniformLocationCache.find(name) != m_UniformLocationCache.end())
		return m_UniformLocationCache[name];

	GLCall(int location = glGetUniformLocation(m_RendererID, name.c_str()));
	if (location == -1)
	{
		std::cout << "Warning: unform '" << name << "' doesn't exist!\n";
	}

	m_UniformLocationCache[name] = location;

	return location;
}