#ifndef _KDR_MAT4_HPP
#define _KDR_MAT4_HPP

#include "math.hpp"

namespace kdr {
	struct mat4 {
		union {
			float elements[16]; // 4 * 4
			vec4 columns[4];    // 4 columns * 4 elements
		};

		mat4();
		mat4(float diagonal);

		static mat4 identity();
		
		static mat4 ortho(const float left, float right, float top, float bottom, float near, float far);
		static mat4 persp(float fov, float aspect_ratio, float near, float far);
		static mat4 trans(const vec3& translation);
		static mat4 rotation(float angle, const vec3& axis);
		static mat4 scale(const vec3& scale);

		mat4& multiply(const mat4& other);
		vec3 multiply(const vec3& other) const;
		vec4 multiply(const vec4& other) const;

		friend mat4 operator*(const mat4& left, const mat4& right);
		friend vec3 operator*(const mat4& left, const vec3& right);
		friend vec4 operator*(const mat4& left, const vec4& right);
		mat4& operator=(const mat4& other);

		mat4& operator*=(const mat4& other);
		friend bool operator==(const mat4& left, const mat4& right);
		friend bool operator!=(const mat4& left, const mat4& right);
	};
} 

#endif // hi :)