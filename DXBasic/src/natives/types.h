#pragma once
#include <cstdint>

class Vector2 {
public:
	Vector2() : x(0.f), y(0.f) {}
	Vector2(float x, float y) : x(x), y(y) {}
public:
	alignas(sizeof(double)) float x, y;
public:
	Vector2 operator*(const float amount) {
		return { x * amount, y * amount };
	}
	Vector2 operator*(const Vector2 vec) {
		return { x * vec.x, y * vec.y };
	}
	Vector2 operator+(const float amount) {
		return { x + amount, y + amount };
	}
	Vector2 operator+(const Vector2 vec) {
		return { x + vec.x, y + vec.y };
	}
	Vector2 operator-(const float amount) {
		return { x - amount, y - amount };
	}
	Vector2 operator-(const Vector2 vec) {
		return { x - vec.x, y - vec.y };
	}
};
class Vector3 {
public:
	Vector3() : x(0.f), y(0.f), z(0.f) {}
	Vector3(float x, float y, float z) : x(x), y(y), z(z) {}
public:
	alignas(sizeof(double)) float x, y, z;
public:
	Vector3 operator*(const float amount) {
		return { x * amount, y * amount, z * amount };
	}
	Vector3 operator*(const Vector3 vec) {
		return { x * vec.x, y * vec.y, z * vec.z };
	}
	Vector3 operator+(const float amount) {
		return { x + amount, y + amount, z + amount };
	}
	Vector3 operator+(const Vector3 vec) {
		return { x + vec.x, y + vec.y, z + vec.z };
	}
	Vector3 operator-(const float amount) {
		return { x - amount, y - amount, z - amount };
	}
	Vector3 operator-(const Vector3 vec) {
		return { x - vec.x, y - vec.y, z - vec.z };
	}
};
class Vector4 {
public:
	Vector4() = default;
	Vector4(float x, float y, float z, float w) : x(x), y(y), z(z), w(w) {}
public:
	alignas(sizeof(double)) float x, y, z, w;
public:
	Vector4 operator*(const float amount) {
		return { x * amount, y * amount, z * amount, w * amount };
	}
	Vector4 operator*(const Vector4 vec) {
		return { x * vec.x, y * vec.y, z * vec.z, w * vec.w };
	}
	Vector4 operator+(const float amount) {
		return { x + amount, y + amount, z + amount, w + amount };
	}
	Vector4 operator+(const Vector4 vec) {
		return { x + vec.x, y + vec.y, z + vec.z, w + vec.z };
	}
	Vector4 operator-(const float amount) {
		return { x - amount, y - amount, z - amount, w - amount };
	}
	Vector4 operator-(const Vector4 vec) {
		return { x - vec.x, y - vec.y, z - vec.z, w - vec.z };
	}
};

using Void = void;
using Any = uint32_t;
using Hash = uint32_t;
using Entity = int32_t;
using Player = int32_t;
using FireId = int32_t;
using Interior = int32_t;
using Ped = Entity;
using Vehicle = Entity;
using Cam = int32_t;
using Object = Entity;
using Pickup = Object;
using Blip = int32_t;
using Camera = Entity;
using ScrHandle = Entity;