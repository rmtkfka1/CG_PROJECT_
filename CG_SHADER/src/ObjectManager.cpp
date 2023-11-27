#include "pch.h"
#include "ObjectManager.h"
#include "Model.h"


void ObjectManager::AddModel(Model* model)
{
	if (model == nullptr)
	{
		return;
	}

	v_model.push_back(model);

}
