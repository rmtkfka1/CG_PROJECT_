#pragma once


class Scene;

class SceneManager
{


public:

	static SceneManager* GetInstance()
	{
		static SceneManager mg;
		return &mg;
	}



public:
	void Init();
	void Update();
	void Render();
	void Clear();
	void ChangeScene(SceneType sceneType);

private:
	Scene* _scene; //���� �����ϰ��ִ� ��
	SceneType _sceneType = SceneType::NONE; //��Ÿ��(STAGE1,STAGE2,STAGE3)
};

