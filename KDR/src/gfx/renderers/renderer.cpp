#include "renderer.hpp"

namespace kdr {
	TileData::TileData(unsigned char tile_size, unsigned short offset_x, unsigned short offset_y)
	: tile_size(tile_size), offset_x(offset_x), offset_y(offset_y) {
		return;
	}

	Renderer::Renderer(TileData tile_info)
	: tiles(tile_info), transforms(std::vector<mat4>()) {
		transforms.push_back(mat4::identity());
		transforms_back = &transforms.back();
		return;
	}

	void Renderer::push(const mat4& matrix) {
		transforms.push_back(*transforms_back * matrix);
		transforms_back = &transforms.back();
		return;
	}

	void Renderer::pushOverride(const mat4& matrix) {
		transforms.push_back(matrix);
		transforms_back = &transforms.back();
		return;
	}

	void Renderer::pop() {
		// we don't want to pop the default
		// identity matrix
		if (transforms.size() > 1)
			transforms.pop_back();
		transforms_back = &transforms.back();
		return;
	}
}