#ifndef _KDR_VEC_HPP
#define _KDR_VEC_HPP

#include <ostream>

namespace kdr {
	struct vec2
	{
		float x, y;

		vec2() = default;
		vec2(const float& x, const float& y);

		vec2& add(const vec2& other);
		vec2& subtract(const vec2& other);
		vec2& multiply(const vec2& other);
		vec2& divide(const vec2& other);
		vec2& set(const vec2& other);

		friend vec2 operator+(const vec2& right, const vec2& left);
		friend vec2 operator-(const vec2& right, const vec2& left);
		friend vec2 operator*(const vec2& right, const vec2& left);
		friend vec2 operator/(const vec2& right, const vec2& left);

		vec2& operator+=(const vec2& other);
		vec2& operator-=(const vec2& other);
		vec2& operator/=(const vec2& other);
		vec2& operator*=(const vec2& other);
		vec2& operator=(const vec2& other);
		bool operator==(const vec2& other);
		bool operator!=(const vec2& other);

		friend std::ostream& operator<< (std::ostream& stream, const vec2& vec);
	};

	struct vec3
	{
		float x, y, z;

		vec3() = default;
		vec3(const float& x, const float& y, const float& z);

		vec3& add(const vec3& other);
		vec3& subtract(const vec3& other);
		vec3& multiply(const vec3& other);
		vec3& divide(const vec3& other);
		vec3& set(const vec3& other);
		vec3 dotProduct(const vec3& v);
		vec3 rotate(vec3& axis, float Angle);

		friend vec3 operator+(const vec3& right, const vec3& left);
		friend vec3 operator-(const vec3& right, const vec3& left);
		friend vec3 operator*(const vec3& right, const vec3& left);
		friend vec3 operator/(const vec3& right, const vec3& left);

		vec3& operator*(float val);
		vec3& operator+=(const vec3& other);
		vec3& operator-=(const vec3& other);
		vec3& operator/=(const vec3& other);
		vec3& operator*=(const vec3& other);
		vec3& operator=(const vec3& other);
		bool operator==(const vec3& other);
		bool operator!=(const vec3& other);

		friend std::ostream& operator<< (std::ostream& stream, const vec3& vec);
	};

	struct vec4
	{
		float x, y, z, w;
		
		vec4() = default;
		vec4(const float& x, const float& y, const float& z, const float& w);

		vec4& add(const vec4& other);
		vec4& subtract(const vec4& other);
		vec4& multiply(const vec4& other);
		vec4& divide(const vec4& other);
		vec4& set(const vec4& other);
		/*
		 Converts values from 4 floats to
		 unsigned int
		 This assumes all values are between 0 and 1
		 */
		unsigned int toColor1();
		/*
		 Converts values from 4 floats to
		 unsigned int
		 This assumed all values are between 0 and 256
		 Converts the values to ints but doesn't change the
		 values of the actual vector
		 */
		unsigned int toColor256();

		friend vec4 operator+(const vec4& right, const vec4& left);
		friend vec4 operator-(const vec4& right, const vec4& left);
		friend vec4 operator*(const vec4& right, const vec4& left);
		friend vec4 operator/(const vec4& right, const vec4& left);

		vec4& operator+=(const vec4& other);
		vec4& operator-=(const vec4& other);
		vec4& operator/=(const vec4& other);
		vec4& operator*=(const vec4& other);
		vec4& operator=(const vec4& other);
		bool operator==(const vec4& other);
		bool operator!=(const vec4& other);

		friend std::ostream& operator<< (std::ostream& stream, const vec4& vec);
	};
}

#endif // hi :)