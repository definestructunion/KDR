#include "vec.hpp"

namespace kdr {
	vec2::vec2(const float& x, const float& y) : x(x), y(y) {
		return;
	}

	vec2& vec2::add(const vec2& other) {
		x += other.x;
		y += other.y;
		return *this;
	}

	vec2& vec2::subtract(const vec2& other) {
		x -= other.x;
		y -= other.y;
		return *this;
	}

	vec2& vec2::multiply(const vec2& other) {
		x *= other.x;
		y *= other.y;
		return *this;
	}

	vec2& vec2::divide(const vec2& other) {
		x /= other.x;
		y /= other.y;
		return *this;
	}

	vec2& vec2::set(const vec2& other) {
		x = other.x;
		y = other.y;
		return *this;
	}

	vec2 operator+(const vec2& right, const vec2& left) {
		return vec2(right).add(left);
	}

	vec2 operator-(const vec2& right, const vec2& left) {
		return vec2(right).subtract(left);
	}

	vec2 operator*(const vec2& right, const vec2& left) {
		return vec2(right).multiply(left);
	}

	vec2 operator/(const vec2& right, const vec2& left) {
		return vec2(right).divide(left);
	}

	std::ostream& operator<< (std::ostream& stream, const vec2& vec) {
		return (stream << "vec2<" << vec.x << "," << vec.y << ">");
	}

	vec2& vec2::operator+=(const vec2& other) {
		return add(other);
	}

	vec2& vec2::operator-=(const vec2& other) {
		return subtract(other);
	}

	vec2& vec2::operator*=(const vec2& other) {
		return multiply(other);
	}

	vec2& vec2::operator/=(const vec2& other) {
		return divide(other);
	}

	vec2& vec2::operator=(const vec2& other) {
		return this->set(other);
	}

	bool vec2::operator==(const vec2& other) {
		return x == other.x && y == other.y;
	}

	bool vec2::operator!=(const vec2& other) {
		return !(*this == other);
	}



	vec3::vec3(const float& x, const float& y, const float& z) : x(x), y(y), z(z) {
		return;
	}

	vec3& vec3::add(const vec3& other) {
		x += other.x;
		y += other.y;
		z += other.z;
		return *this;
	}

	vec3& vec3::subtract(const vec3& other) {
		x -= other.x;
		y -= other.y;
		z -= other.z;
		return *this;
	}

	vec3& vec3::multiply(const vec3& other) {
		x *= other.x;
		y *= other.y;
		z *= other.z;
		return *this;
	}

	vec3& vec3::divide(const vec3& other) {
		x /= other.x;
		y /= other.y;
		z /= other.z;
		return *this;
	}

	vec3& vec3::set(const vec3& other) {
		x = other.x;
		y = other.y;
		z = other.z;
		return *this;
	}

	vec3 vec3::dotProduct(const vec3& v) {
		double k1 = (y * v.z) - (z * v.y);
		double k2 = (z * v.x) - (x * v.z);
		double k3 = (x * v.y) - (y * v.x);

		return vec3(k1, k2, k3);
	}

	vec3 vec3::rotate(vec3& axis, float angle) {
		vec3 v = *this;
		return ((v - axis * (axis * v)) * cos(angle)) + (axis.dotProduct(v) * sin(angle)) + (axis * (axis * v));
	}

	vec3& vec3::operator*(float val) {
		x *= val;
		y *= val;
		z *= val;
		return *this;
	}

	vec3 operator+(const vec3& right, const vec3& left) {
		return vec3(right).add(left);
	}

	vec3 operator-(const vec3& right, const vec3& left) {
		return vec3(right).subtract(left);
	}

	vec3 operator*(const vec3& right, const vec3& left) {
		return vec3(right).multiply(left);
	}

	vec3 operator/(const vec3& right, const vec3& left) {
		return vec3(right).divide(left);
	}

	std::ostream& operator<< (std::ostream& stream, const vec3& vec) {
		return (stream << "vec3<" << vec.x << "," << vec.y << "," << vec.z << ">");
	}

	vec3& vec3::operator+=(const vec3& other) {
		return add(other);
	}

	vec3& vec3::operator-=(const vec3& other) {
		return subtract(other);
	}

	vec3& vec3::operator*=(const vec3& other) {
		return multiply(other);
	}

	vec3& vec3::operator/=(const vec3& other) {
		return divide(other);
	}

	vec3& vec3::operator=(const vec3& other) {
		return this->set(other);
	}

	bool vec3::operator==(const vec3& other) {
		return x == other.x && y == other.y && z == other.z;
	}

	bool vec3::operator!=(const vec3& other) {
		return !(*this == other);
	}



	vec4::vec4(const float& x, const float& y, const float& z, const float& w) : x(x), y(y), z(z), w(w) {
		return;
	}

	vec4& vec4::add(const vec4& other) {
		x += other.x;
		y += other.y;
		z += other.z;
		w += other.w;
		return *this;
	}

	vec4& vec4::subtract(const vec4& other) {
		x -= other.x;
		y -= other.y;
		z -= other.z;
		w -= other.w;
		return *this;
	}

	vec4& vec4::multiply(const vec4& other) {
		x *= other.x;
		y *= other.y;
		z *= other.z;
		w *= other.w;
		return *this;
	}

	vec4& vec4::divide(const vec4& other) {
		x /= other.x;
		y /= other.y;
		z /= other.z;
		w /= other.w;
		return *this;
	}

	vec4& vec4::set(const vec4& other) {
		x = other.x;
		y = other.y;
		z = other.z;
		w = other.w;
		return *this;
	}

	unsigned int vec4::toColor1() {
		return (int)(w * 255) << 0x0018 | (int)(z * 255) << 0x0010 | (int)(y * 255) << 0x0008 | (int)(x * 255);
	}

	unsigned int vec4::toColor256() {
		return ((int)w << 0x0018 | (int)z << 0x0010 | (int)y << 0x0008 | (int)x);
	}

	vec4 operator+(const vec4& right, const vec4& left) {
		return vec4(right).add(left);
	}

	vec4 operator-(const vec4& right, const vec4& left) {
		return vec4(right).subtract(left);
	}

	vec4 operator*(const vec4& right, const vec4& left) {
		return vec4(right).multiply(right);
	}

	vec4 operator/(const vec4& right, const vec4& left) {
		return vec4(right).divide(left);
	}

	std::ostream& operator<< (std::ostream& stream, const vec4& vec) {

		return (stream << "vec4<" << vec.x << "," << vec.y << "," << vec.z << "," << vec.w << ">");
	}

	vec4& vec4::operator+=(const vec4& other) {
		return add(other);
	}

	vec4& vec4::operator-=(const vec4& other) {
		return subtract(other);
	}

	vec4& vec4::operator*=(const vec4& other) {
		return multiply(other);
	}

	vec4& vec4::operator/=(const vec4& other) {
		return divide(other);
	}

	vec4& vec4::operator=(const vec4& other) {
		return this->set(other);
	}

	bool vec4::operator==(const vec4& other) {
		return x == other.x && y == other.y && z == other.z && w == other.w;
	}

	bool vec4::operator!=(const vec4& other) {
		return !(*this == other);
	}
}