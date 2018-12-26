#include "rectangle.hpp"

namespace kdr {
	Rectangle::Rectangle()
	: x(0.0f), y(0.0f), width(0.0f), height(0.0f) {
		return;
	}

	Rectangle::Rectangle(float x, float y)
	: x(x), y(y), width(0.0f), height(0.0f) {
		return;
	}

	Rectangle::Rectangle(float x, float y, float width, float height) 
	: x(x), y(y), width(width), height(height) {
		return;
	}

	bool Rectangle::contains(vec2 pos) {
		return ((pos.x >= x && pos.x <= width) && (pos.y >= y && pos.y <= height));
	}

	bool Rectangle::contains(float x_pos, float y_pos) {
		return ((x_pos >= x && x_pos <= width) && (y_pos >= y && y_pos <= height));
	}
}