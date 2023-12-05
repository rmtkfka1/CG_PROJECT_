#pragma once

class p14_world;
class Shader;
class ObjectManager
{

public:
	static ObjectManager* GetInstance()
	{
		static ObjectManager OM;
		return &OM;
	}

	void AddShader(Shader *shader);


	vector<Shader*>& Get_Shader() { return v_shader; } //외부 CPP,헤더파일에서 벡터가져오기//



private:
	vector<Shader*> v_shader;
};

