#pragma once

class Model;

class ObjectManager
{

public:
	static ObjectManager* GetInstance()
	{
		static ObjectManager OM;
		return &OM;
	}

	void AddModel(Model *model);


	vector<Model*>& Get_Model() { return v_model; } //외부 CPP,헤더파일에서 벡터가져오기//



private:
	vector<Model*> v_model;
};

