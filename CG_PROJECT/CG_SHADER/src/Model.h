#pragma once



class Model
{
public:
	Model(const std::string& fileName);
	~Model();

	void LoadModel(const std::string& fileName);
	void ClearModel();

	void RenderModel(Shader& shader);

	void PrintInfo(); // 중심점 , 사이즈 출력 하는 함수
	glm::vec3 GetCenter() {return _center;} 
	glm::vec3 GetSize() { return _size; }


private:
	void LoadNode(aiNode* node, const aiScene* scene);
	void LoadMesh(aiMesh* mesh, const aiScene* scene);
	void LoadMaterials(const aiScene* scene);

	std::vector<VAO*> VAOs;
	std::vector<VBO*> VBOs;
	std::vector<IBO*> IBOs;
	std::vector<Texture*> m_TextureList;
	std::vector<unsigned int> m_MeshToTex;

	glm::vec3 _size;
	glm::vec3 _center;
	string _fileName;


};