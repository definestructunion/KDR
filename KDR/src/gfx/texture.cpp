#include "../util/util.hpp"
#include "texture.hpp"
#define STB_IMAGE_IMPLEMENTATION
#include "../../ext/stb_image/stb_image.h"

namespace kdr {
	Texture::Texture(const char* file_path) {
		load(file_path);
		return;
	}

	Texture::~Texture() {
		// free the memory from OpenGL
		glDeleteTextures(1, &texture_id);
		return;
	}

	void Texture::load(const char* file_path) {
		// flip the image upwards
		stbi_set_flip_vertically_on_load(true);
		// load the local_buffer with the texture data
		// and set the width, height, and bits_per_pixel
		// and set the texture to 4 channels
		local_buffer = stbi_load(file_path, &width, &height, &bits_per_pixel, 4);

		// generate a new texture in OpenGL
		glGenTextures(1, &texture_id);
		// bind the texture so we can edit some details
		glBindTexture(GL_TEXTURE_2D, texture_id);

		// these textures are 2D
		// the texture will have a minifying filter
		// and a magnification filter
		// and wrap the texture on the x and y axis
		// and clamp the textures to the edge
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE);

		// this texture uses RGBA8 with each channel having an unsigned byte
		glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA8, width, height, 0, GL_RGBA, GL_UNSIGNED_BYTE, local_buffer);
		// unbind the texture now that we're done with it
		glBindTexture(GL_TEXTURE_2D, NULL);

		// if the local buffer isn't nullptr
		if (local_buffer)
			// free it
			stbi_image_free(local_buffer);
		return;
	}

	void Texture::bind() const {
		// bind this texture to OpenGL
		glBindTexture(GL_TEXTURE_2D, texture_id);
		return;
	}

	void Texture::unbind() const {
		// unbind this texture from OpenGL
		glBindTexture(GL_TEXTURE_2D, NULL);
		return;
	}
}