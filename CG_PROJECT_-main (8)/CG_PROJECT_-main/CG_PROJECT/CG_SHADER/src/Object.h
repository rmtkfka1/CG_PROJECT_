#pragma once

class Component;
class Texture;
class Model;
class Shader;
class Collider;
class Model;

class Object
{

public:

	Object(ObjectType type);
	virtual ~Object();

	virtual void Init();
	virtual void Update();
	virtual void Render(Shader& shader);



	void SetRotate(float radian, float x, float y, float z);
	glm::mat4 GetScale(float dx,float dy, float dz); // 크기조절 자동화(mat4 뱉어줌 행렬식 조합해서 사용할떄 사용)
	void SetTransPose(float dx, float dy, float dz); // 크기조절 자동화(mat4 뱉어줌 행렬식 조합해서 사용할떄 사용)


	void PrintInfo();
	
	void AddComponent(Component* component);
	void RemoveComponent(Component* component);
	ObjectType GetObjectType() { return _type; }

	virtual void OnComponentBeginOverlap(Collider* collider, Collider* other);
	virtual void OnComponentEndOverlap(Collider* collider, Collider* other);


	//임시용
	glm::vec3 GetCenter() { return _center; }
	glm::vec3 GetSize() { return _size; }
	void SetSize(glm::vec3 size) { _size = size; }

	void SetCenter(glm::vec3 temp) { _center = temp; }
	void SetCenter_x(float x) { _center.x = x; }
	void SetCenter_y(float y) { _center.y = y; }
	void SetCenter_z(float z) { _center.z = z; }

	float GetCenter_x() { return _center.x; }
	float GetCenter_y() { return _center.y; }
	float GetCenter_z() { return _center.z; }

	float GetFirstCenter_x() { return _first_center.x; }
	float GetFirstCenter_y() { return _first_center.y; }
	float GetFirstCenter_z() { return _first_center.z; }

	

protected:


	vector<Component*> v_component;

	glm::vec3 _first_center{}; 
	glm::vec3 _center{};
	glm::vec3 _size{};
	ObjectType _type=ObjectType::NONE;

	Model* _model = nullptr;
public:
	glm::mat4 _matrix = glm::mat4(1.0f);
	glm::vec3 _debug_color = { 1,0,0 };

	float _dx{}, _dy{}, _dz{};
};

