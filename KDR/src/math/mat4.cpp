#include "mat4.hpp"

namespace kdr {
	mat4::mat4() {
		memset(elements, 0.0f, 16);
		return;
	}

	mat4::mat4(float diagonal) {
		for (unsigned int y = 0; y < 4; ++y)
			for (unsigned int x = 0; x < 4; ++x)
				(x != y) ? elements[x + y * 4] = 0 : elements[x + y * 4] = diagonal;
		return;
	}

	mat4 mat4::identity() {
		return 1.0f;
	}

	mat4 mat4::ortho(const float left, float right, float top, float bottom, float near, float far) {
		mat4 result(1.0f);

		// for semantic purposes, ignore the * 4 to make it easier to understand the positions

		// start diagonal from element 0 in column major
		result.elements[0 + 0 * 4] = 2.0f / (right - left);
		result.elements[1 + 1 * 4] = 2.0f / (top - bottom);
		result.elements[2 + 2 * 4] = 2.0f / (near - far);
		// end diagonal

		// start up to down in last column to the 2nd last element
		result.elements[0 + 3 * 4] = (left + right) / (left - right);
		result.elements[1 + 3 * 4] = (bottom + top) / (bottom - top);
		result.elements[2 + 3 * 4] = (far + near) / (far - near);
		// end up to down
		return result;
	}

	mat4 mat4::persp(float fov, float aspect_ratio, float near, float far) {
		mat4 result(1.0f);

		// for semantic purposes, ignore the * 4 to make it easier to understand the positions

		// variables for setting elements;
		float q = tan(to_radians(0.5f * fov));
		float a = q / aspect_ratio;
		float b = (near + far) / (near - far);
		float c = (2.0f * near * far) / (near - far);

		// start diagonal from element 0 to element 3, column 3 in column major
		result.elements[0 + 0 * 4] = a;
		result.elements[1 + 1 * 4] = q;
		result.elements[2 + 2 * 4] = b;
		// end diagonal

		// element 4 column 3
		result.elements[3 + 2 * 4] = -1.0f;
		// element 3 column 4
		result.elements[2 + 3 * 4] = c;

		// may be wrong
		// last element
		result.elements[15] = 0;
		
		return result;
	}

	mat4 mat4::trans(const vec3& translation) {
		mat4 result(1.0f);

		// for semantic purposes, ignore the * 4 to make it easier to understand the positions

		// start up to down in column 4 to element 3
		result.elements[0 + 3 * 4] = translation.x;
		result.elements[1 + 3 * 4] = translation.y;
		result.elements[2 + 3 * 4] = translation.z;

		return result;
	}

	mat4 mat4::scale(const vec3& scale) {
		mat4 result(1.0f);

		// for semantic purposes, ignore the * 4 to make it easier to understand the positions

		// start element 0 diagonal 3 times
		result.elements[0 + 0 * 4] = scale.x;
		result.elements[1 + 1 * 4] = scale.y;
		result.elements[2 + 2 * 4] = scale.z;

		return result;
	}

	mat4 mat4::rotation(float angle, const vec3& axis) {
		mat4 result(1.0f);

		// for semantic purposes, ignore the * 4 to make it easier to understand the positions

		// variables for setting elements
		float r = to_radians(angle);
		float c = cos(r);
		float s = sin(r);
		float omc = 1.0f - c;

		// start up to down in column one to element 3
		result.elements[0 + 0 * 4] = axis.x * axis.x * omc + c;
		result.elements[0 + 1 * 4] = axis.y * axis.x * omc + axis.z * s;
		result.elements[0 + 2 * 4] = axis.x * axis.z * omc - axis.y * s;
		// end up to down in column 1

		// start up to down in column 2 to element 3
		result.elements[1 + 0 * 4] = axis.x * axis.y * omc - axis.z * s;
		result.elements[1 + 1 * 4] = axis.y * axis.y * omc + c;
		result.elements[1 + 2 * 4] = axis.y * axis.z * omc + axis.x * s;
		// end up to down in column 2

		// start up to down in column 3 to element 3
		result.elements[2 + 0 * 4] = axis.x * axis.z * omc + axis.y * s;
		result.elements[2 + 1 * 4] = axis.y * axis.z * omc - axis.x * s;
		result.elements[2 + 2 * 4] = axis.z * axis.z * omc + c;
		// end up to down in column 3

		return result;
	}

	mat4& mat4::multiply(const mat4& other)
	{
		float data[16];
		for(unsigned int y = 0; y < 4; ++y)
			for (unsigned int x = 0; x < 4; ++x) {
				float sum = 0.0f;
				for (unsigned int e = 0; e < 4; ++e)
					sum += elements[x + e * 4] * other.elements[e + y * 4];

				data[x + y * 4] = sum;
			}
		// elements are of type floats, meaning they are POD
		// so memcpy works fine and faster than a for loop
		memcpy(elements, data, 16 * 4);
		return *this;
	}

	vec3 mat4::multiply(const vec3& other) const {
		return vec3 (
					// x
					columns[0].x * other.x + columns[1].x * other.y + columns[2].x * other.z + columns[3].x, // * 1
					// y
					columns[0].y * other.x + columns[1].y * other.y + columns[2].y * other.z + columns[3].y, // * 1
					// z
					columns[0].z * other.x + columns[1].z * other.y + columns[2].z * other.z + columns[3].z  // * 1
		);
	}

	vec4 mat4::multiply(const vec4& other) const {
		return vec4 (
					// x
					columns[0].x * other.x + columns[1].x * other.y + columns[2].x * other.z + columns[3].x * other.w,
					// y
					columns[0].y * other.x + columns[1].y * other.y + columns[2].y * other.z + columns[3].y * other.w,
					// z
					columns[0].z * other.x + columns[1].z * other.y + columns[2].z * other.z + columns[3].z * other.w,
					// w
					columns[0].w * other.x + columns[1].w * other.y + columns[2].w * other.z + columns[3].w * other.w
		);
	}

	mat4 operator*(const mat4& left, const mat4& right) {
		return mat4(left).multiply(right);
	}

	vec3 operator*(const mat4& left, const vec3& right) {
		return mat4(left).multiply(right);
	}

	vec4 operator*(const mat4& left, const vec4& right) {
		return mat4(left).multiply(right);
	}

	mat4& mat4::operator=(const mat4& other) {
		mat4 result;
		// elements are of type floats, meaning they are POD
		// so memset works fine and faster than a for loop
		memset(result.elements, *other.elements, 16);
		return *this;
	}

	mat4& mat4::operator*=(const mat4& other) {
		return multiply(other);
	}

	bool operator==(const mat4& left, const mat4& right) {
		for (int i = 0; i < 16; i++)
			if (left.elements[i] != right.elements[i])
				return false;
		return true;
	}

	bool operator!=(const mat4& left, const mat4& right) {
		return !(left == right);
	}
}
