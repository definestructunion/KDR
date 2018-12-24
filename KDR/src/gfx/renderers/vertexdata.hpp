#ifndef _KDR_VERTEXDATA_HPP
#define _KDR_VERTEXDATA_HPP

#include "../../math/math.hpp"

namespace kdr {
	typedef struct {
		vec3 vertex;
		vec2 uv;
		float tid;
		unsigned int color;
	} VertexData;
}

#define VERTEXDATA_SIZE (sizeof(VertexData))

#endif // hi :)