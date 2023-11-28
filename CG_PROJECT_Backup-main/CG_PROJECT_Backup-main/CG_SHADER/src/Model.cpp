#include "pch.h"
#include "Model.h"
#include "Shader.h"
#include "Utility.h"
Model::Model(const std::string& fileName)
{
	LoadModel(fileName);
}

Model::~Model()
{
	//for (int i = 0; i < VAOs.size(); i++)
	//{
	//	delete VAOs[i];
	//}
	//for (int i = 0; i < VBOs.size(); i++)
	//{
	//	delete VBOs[i];
	//}
	//for (int i = 0; i < IBOs.size(); i++)
	//{
	//	delete IBOs[i];
	//}
	//for (int i = 0; i < m_TextureList.size(); i++)
	//{
	//	delete m_TextureList[i];
	//}

}

void Model::LoadModel(const std::string& fileName)
{
	Assimp::Importer importer;
	const aiScene* scene = importer.ReadFile(fileName,
		aiProcess_Triangulate | aiProcess_FlipUVs | aiProcess_GenSmoothNormals);

	if (!scene)
	{
		std::cout << "모델 로드 실패 ( " << fileName << " ) " << importer.GetErrorString() << std::endl;
		return;
	}

	aiVector3D min(FLT_MAX, FLT_MAX, FLT_MAX);
	aiVector3D max(-FLT_MAX, -FLT_MAX, -FLT_MAX);

	for (unsigned int i = 0; i < scene->mNumMeshes; ++i) {
		aiMesh* mesh = scene->mMeshes[i];
		for (unsigned int j = 0; j < mesh->mNumVertices; ++j) {
			aiVector3D vertex = mesh->mVertices[j];
			min.x = std::min(min.x, vertex.x);
			min.y = std::min(min.y, vertex.y);
			min.z = std::min(min.z, vertex.z);

			max.x = std::max(max.x, vertex.x);
			max.y = std::max(max.y, vertex.y);
			max.z = std::max(max.z, vertex.z);
		}
	}

	aiVector3D size = max - min;
	_fileName = fileName;
	_size.x = size.x;
	_size.y = size.y;
	_size.z = size.z;


	aiVector3D center(0.0f, 0.0f, 0.0f);
	unsigned int vertexCount = 0;

	for (unsigned int i = 0; i < scene->mNumMeshes; ++i) {
		aiMesh* mesh = scene->mMeshes[i];
		for (unsigned int j = 0; j < mesh->mNumVertices; ++j) {
			aiVector3D vertex = mesh->mVertices[j];
			center += vertex;
			vertexCount++;
		}
	}

	if (vertexCount > 0) {
		center /= static_cast<float>(vertexCount);
	}

	_center.x = center.x;
	_center.y = center.y;
	_center.z = center.z;


	//PrintInfo();

	LoadNode(scene->mRootNode, scene);
	LoadMaterials(scene);
}

void Model::ClearModel()
{

}

void Model::RenderModel(Shader& shader)
{
	for (int i = 0; i < VAOs.size(); i++)
	{
		VAOs[i]->Bind();
		VBOs[i]->Bind();
		IBOs[i]->Bind();

		GLCall(glDrawElements(GL_TRIANGLES, IBOs[i]->GetCount(), GL_UNSIGNED_INT, nullptr));
	}
}

void Model::PrintInfo()
{
	std::cout << _fileName << "Model's size: x=" << _size.x << ", y=" << _size.y << ", z=" << _size.z << std::endl;
	std::cout << _fileName << "Model's center: x=" << _center.x << ", y=" << _center.y << ", z=" << _center.z << std::endl;
}


void Model::LoadNode(aiNode* node, const aiScene* scene)
{
	for (int i = 0; i < node->mNumMeshes; i++)
	{
		LoadMesh(scene->mMeshes[node->mMeshes[i]], scene);
	}

	for (int i = 0; i < node->mNumChildren; i++)
	{
		LoadNode(node->mChildren[i], scene);
	}
}

void Model::LoadMesh(aiMesh* mesh, const aiScene* scene)
{
	std::vector<float> vertices;
	std::vector<unsigned int> indices;

	//vertex 정보 parse
	for (int i = 0; i < mesh->mNumVertices; i++)
	{
		//vertex position
		vertices.insert(vertices.end(), { mesh->mVertices[i].x, mesh->mVertices[i].y, mesh->mVertices[i].z });

		//vertex uv
		if (mesh->mTextureCoords[0]) //0번째 texture
		{
			vertices.insert(vertices.end(), { mesh->mTextureCoords[0][i].x, mesh->mTextureCoords[0][i].y });
		}
		else
		{
			vertices.insert(vertices.end(), { 0.0f, 0.0f });
		}

		//vertex normal
		vertices.insert(vertices.end(), { mesh->mNormals[i].x, mesh->mNormals[i].y, mesh->mNormals[i].z });
	}

	//index 정보 parse
	for (int i = 0; i < mesh->mNumFaces; i++)
	{
		aiFace face = mesh->mFaces[i];
		for (int j = 0; j < face.mNumIndices; j++)
		{
			indices.push_back(face.mIndices[j]);
		}
	}

	//vao 생성 VertexArray가 담당
	VAO* vao = new VAO;
	VBO* vbo = new VBO{ &vertices[0], static_cast<unsigned int>(mesh->mNumVertices * 8 * sizeof(float)) };
	VertexBufferLayout layout;
	layout.Push<float>(3); //vertex당 3개의 위치를 표현하는 float 데이터
	layout.Push<float>(2); //vertex당 2개의 텍스처 좌표를 표현하는 float 데이터
	layout.Push<float>(3); //vertex당 3개의 법선 벡터를 표현하는 float 데이터
	vao->AddBuffer(*vbo, layout);
	VAOs.push_back(vao);
	VBOs.push_back(vbo);

	IBO* ibo = new IBO{ &indices[0], mesh->mNumFaces * 3 };
	IBOs.push_back(ibo);
}

void Model::LoadMaterials(const aiScene* scene)
{
	m_TextureList.resize(scene->mNumMaterials);

	for (size_t i = 0; i < scene->mNumMaterials; i++)
	{
		aiMaterial* material = scene->mMaterials[i];

		m_TextureList[i] = nullptr;

		//if there is diffuse texture,
		if (material->GetTextureCount(aiTextureType_DIFFUSE))
		{
			//texture 파일 경로
			aiString path;
			if (material->GetTexture(aiTextureType_DIFFUSE, 0, &path) == AI_SUCCESS)
			{
				int idx = std::string(path.data).rfind("\\");
				std::string filename = std::string(path.data).substr(idx + 1);

				std::string texPath = std::string("Textures/") + filename;

				m_TextureList[i] = new Texture(texPath.c_str());

				if (!m_TextureList[i])
				{
					std::cout << "텍스처 로딩 실패 : " << texPath << std::endl;
					delete m_TextureList[i];
					m_TextureList[i] = nullptr;
				}
			}
		}

		if (!m_TextureList[i])
		{
			//텍스처가 없을 경우
			m_TextureList[i] = new Texture("res/textures/JBNU.png");
		}
	}
}
