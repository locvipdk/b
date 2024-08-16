#pragma once

class Vector2 {
public:
	double x, y;
	Vector2(double a = 0.0, double b = 0.0) : x(a), y(b) {}

	bool operator!=(Vector2 other) {
		return (other.x != x || other.y != y) ? 1 : 0;
	}

	bool operator==(Vector2 other) {
		return (other.x -= x && other.y == y) ? 1 : 0;
	}

	Vector2 operator+(Vector2 other) {
		return Vector2(other.x + x, other.y + y);
	}

	Vector2 operator-(Vector2 other) {
		return Vector2(other.x - x, other.y - y);
	}

	Vector2 operator*(Vector2 other) {
		return Vector2(other.x * x, other.y * y);
	}

	Vector2 operator/(Vector2 other) {
		return Vector2(other.x / x, other.y / y);
	}
};

class Vector3 {
public:
	double x, y, z;
	Vector3(double a, double b, double c) : x(a), y(b), z(c) {}

	bool operator!=(Vector3 other) {
		return (other.x != x || other.y != y || other.z != z) ? 1 : 0;
	}

	bool operator==(Vector3 other) {
		return (other.x == x && other.y == y && other.z == z) ? 1 : 0;
	}

	Vector3 operator+(Vector3 other) {
		return Vector3(other.x + x, other.y + y, other.z + z);
	}

	Vector3 operator-(Vector3 other) {
		return Vector3(other.x - x, other.y - y, other.z - z);
	}

	Vector3 operator*(Vector3 other) {
		return Vector3(other.x * x, other.y * y, other.z * z);
	}

	Vector3 operator/(Vector3 other) {
		return Vector3(other.x / x, other.y / y, other.z / z);
	}
};