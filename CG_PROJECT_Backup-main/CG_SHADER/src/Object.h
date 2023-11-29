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



	glm::mat4 GetRotate(float radian, float x, float y, float z);
	glm::mat4 GetScale(float dx,float dy, float dz); // 크기조절 자동화(mat4 뱉어줌 행렬식 조합해서 사용할떄 사용)
	glm::mat4 GetTransPose(float dx, float dy, float dz); // 크기조절 자동화(mat4 뱉어줌 행렬식 조합해서 사용할떄 사용)


	void PrintInfo();
	
	void AddComponent(Component* component);
	void RemoveComponent(Component* component);
	ObjectType GetObjectType() { return _type; }

	// OnCollisionEnter2D / OnCollisionExit2D
	virtual void OnComponentBeginOverlap(Collider* collider, Collider* other);
	virtual void OnComponentEndOverlap(Collider* collider, Collider* other);


	//임시용
	glm::vec3 GetCenter() { return _center; }
	glm::vec3 GetSize() { return _size; }

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
	glm::mat4 _matrix = glm::mat4(1.0f);
	Model* _model = nullptr;
public:
	glm::vec3 _debug_color = { 1,0,0 };
};

