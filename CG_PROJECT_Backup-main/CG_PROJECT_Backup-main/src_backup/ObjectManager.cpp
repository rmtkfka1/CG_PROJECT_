#include "pch.h"
#include "ObjectManager.h"

void ObjectManager::AddShader(Shader* shader)
{

	if (shader == nullptr)
	{
		return;
	}

	v_shader.push_back(shader);

}
