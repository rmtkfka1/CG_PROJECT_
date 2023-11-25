#include "pch.h"
#include "Scene.h"
#include "SceneManager.h"
#include "Stage1.h"

void SceneManager::Init()
{

}

void SceneManager::Update()
{
	if (_scene)
	{
		_scene->Update();
	
	}
	

}

void SceneManager::Render()
{

	if (_scene)
	{
		_scene->Render();
	}

}


void SceneManager::Clear()
{
	if (_scene)
	{
		delete _scene;
		_scene = nullptr;
	}
}

void SceneManager::ChangeScene(SceneType sceneType)
{
	if (_sceneType == sceneType)
		return;

	Scene* newScene = nullptr;

	switch (sceneType)
	{
	case SceneType::NONE:
		break;
	case SceneType::Stage1:
		newScene = new Stage1();
		break;
	default:
		break;
	}

	//이미씬이 존재하는 경우 씬삭제
	if (_scene)
	{

		delete _scene;
		_scene = nullptr;

	}

	_scene = newScene;
	_sceneType = sceneType;


	newScene->Init();
}
