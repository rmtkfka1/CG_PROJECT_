#pragma once

using int8 = __int8;
using int16 = __int16;
using int32 = __int32;
using int64 = __int64;
using uint8 = unsigned __int8;
using uint16 = unsigned __int16;
using uint32 = unsigned __int32;
using uint64 = unsigned __int64;


#define DECLARE_SINGLE(classname)                   \
public:											    \
	classname(){}									\
													\
public:												\
													\
	static classname* GetInstance()					\
	{												\
		static classname s_Insatance;				\
		return &s_Insatance;						\
	}												

#define GET_SINGLE(classname) classname::GetInstance() 





struct vec2 {
	float x;
	float y;


	vec2 operator+(const vec2& other) {
		vec2 temp;
		temp.x = this->x + other.x;
		temp.y = this->y + other.y;
		return temp;
	}

	vec2 operator-(const vec2& other) {
		vec2 temp;
		temp.x = this->x - other.x;
		temp.y = this->y - other.y;
		return temp;
	}

	vec2 operator*(const float r) {
		vec2 temp;
		temp.x = this->x * r;
		temp.y = this->y * r;
		return temp;
	}


	void operator-=(const vec2& p) {
		this->x -= p.x;
		this->y -= p.y;
	}
	void operator+=(const vec2& p) {
		this->x += p.x;
		this->y += p.y;
	}

	bool operator!=(const vec2& p) {
		return (x != p.x || y != p.y);
	}
	bool operator==(const vec2& p) {
		return (x == p.x && y == p.y);
	}
};

struct vec3 {
	float x;
	float y;
	float z;


	vec3 operator+(const vec3& other) {
		vec3 temp;
		temp.x = this->x + other.x;
		temp.y = this->y + other.y;
		temp.z = this->z + other.z;
		return temp;
	}

	vec3 operator-(const vec3& other) {
		vec3 temp;
		temp.x = this->x - other.x;
		temp.y = this->y - other.y;
		temp.z = this->z - other.z;
		return temp;
	}

	vec3 operator*(const float r) {
		vec3 temp;
		temp.x = this->x * r;
		temp.y = this->y * r;
		temp.z = this->z * r;
		return temp;
	}


	void operator-=(const vec3& p) {
		this->x -= p.x;
		this->y -= p.y;
		this->z -= p.z;
	}
	void operator+=(const vec3& p) {
		this->x += p.x;
		this->y += p.y;
		this->z += p.z;
	}

	bool operator!=(const vec3& p) {
		return (x != p.x || y != p.y || z != p.z);
	}
	bool operator==(const vec3& p) {
		return (x == p.x && y == p.y && z != p.z);
	}
};



enum class ObjectType
{
	NONE,
	PLAYER,
	WALL
};

enum class SceneType
{
	NONE,
	Stage1
};