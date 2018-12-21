#ifndef _KDR_MATH_HPP
#define _KDR_MATH_HPP

#include "vec.hpp"
#include "mat4.hpp"

#define _USE_MATH_DEFINES
#include <math.h>

namespace kdr {
	inline float to_radians(float degrees) {
		return (float)(degrees * (M_PI / 180));
	}
}

#endif // hi :)