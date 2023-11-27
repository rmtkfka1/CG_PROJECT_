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


	vector<Model*>& Get_Model() { return v_model; } //�ܺ� CPP,������Ͽ��� ���Ͱ�������//



private:
	vector<Model*> v_model;
};

