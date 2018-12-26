#ifndef _KDR_RECTANGLE_HPP
#define _KDR_RECTANGLE_HPP

#include "../math/vec.hpp"

namespace kdr {
	/*
	 Data type that represents
	 an x, y, width, and height
	 */
	struct Rectangle {
		float x, y, width, height;
		/*
		 Creates a rectangle and defaults
		 every variable to 0.0f
		 */
		Rectangle();
		/*
		 Creates a rectangle with corresponding
		 x and y values
		 Width and height defaulted to 0.0f
		 */
		Rectangle(float x, float y);
		/*
		 Creates a rectangle with corresponding
		 x, y, width, and height values
		 */
		Rectangle(float x, float y, float width, float height);
		/*
		 Returns true if pos is within the bounds of the
		 rectangle's x, y, width, and height
		 */
		bool contains(vec2 pos);
		/*
		 Returns true if x and y is within the bounds of the
		 rectangle's x, y, width, and height
		 */
		bool contains(float x_pos, float y_pos);
	};
}

#endif // hi :)