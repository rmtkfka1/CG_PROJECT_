#include "pch.h"
#include "FakeFlash.h"
#include "BoxCollider.h"
#include "Light2.h"
#include "Flash.h"

FakeFlash::FakeFlash(Model& model):Object(ObjectType::FAKE_FLASH)
{
	_center = model.GetCenter();
	_size.x = model.GetSize().x+20;
	_size.z = model.GetSize().z+10;
	_first_center = _center;
	_model = &model;

}

FakeFlash::~FakeFlash()
{
}

void FakeFlash::Init()
{
	Super::Init();
}

void FakeFlash::Update()
{

	Super::Update();

	

}

void FakeFlash::UpdateFlash(Light2* light, Flash* flash)
{
	if (KeyManager::GetInstance()->GetbuttonDown(KeyType::R))
	{
		spotoff = !spotoff;
	}


	if (collision) //충돌중일때 
	{
		if (KeyManager::GetInstance()->GetbuttonDown(KeyType::F))
		{

			draw = false;
		}	

	}

	if (draw == false)
	{
		flash->SetLighton();
		light->point_light.diffuse = glm::vec3(1.0f, 0, 0);
		if (spotoff == false)
		{
			light->Spot_light.distance = 1000.0f;			
		}

		else 
		{
			light->Spot_light.distance = 0.1f;
		}
	}
	
}

void FakeFlash::Render(Shader& shader)
{
	
	if (draw)
	{
		
		Super::Render(shader); 

		shader.SetUniform3f("control_color", 0, 0, 0);
		shader.SetUniformMat4f("u_model", _matrix);
		_model->RenderModel(shader);
	}
}

void FakeFlash::OnComponentBeginOverlap(Collider* collider, Collider* other)
{

	if (other->GetOwner()->GetObjectType() == ObjectType::PLAYER)
	{
		collision = true;
	}
}

void FakeFlash::OnComponentEndOverlap(Collider* collider, Collider* other)
{
	if (other->GetOwner()->GetObjectType() == ObjectType::PLAYER)
	{
		collision = false;
	}

}
