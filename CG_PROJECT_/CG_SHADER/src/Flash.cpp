#include "pch.h"
#include "Flash.h"
#include "Player.h"

Flash::Flash(Model& model):Object(ObjectType::FLASH)
{
	_center = model.GetCenter();
	_size = model.GetSize();
	_first_center = _center;
	_model = &model;
}

Flash::~Flash()
{
}

void Flash::Init()
{
	Super::Init();
}

void Flash::Update()
{

	Super::Update();


}

void Flash::MatrixUpdate(Player* player)
{
	glm::vec3 cameraFront = GET_SINGLE(CameraManager)->m_cameraFront;
	glm::vec4 flachloc = { player->GetCenter_x() + cameraFront.x , player->GetCenter_y() + cameraFront.y + 6.5f, player->GetCenter_z() + cameraFront.z, 1.0f };
	glm::mat4 transMat = matrix::GetInstance()->GetTranslation(flachloc.x, flachloc.y, flachloc.z);

	glm::mat4 yawMat = matrix::GetInstance()->GetRotate(GET_SINGLE(CameraManager)->m_cameraYaw, 0, 1, 0);
	glm::mat4 pitchMat = matrix::GetInstance()->GetRotate(GET_SINGLE(CameraManager)->m_cameraPitch, 1, 0, 0);

	_matrix = transMat * yawMat * pitchMat;
}


void Flash::Render(Shader& shader)
{
	if (lighton)
	{
		
		shader.SetUniform3f("control_color", 0, 0, 0);
		shader.SetUniformMat4f("u_model", _matrix);
		_model->RenderModel(shader);
	}
}
