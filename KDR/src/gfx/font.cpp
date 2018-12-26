#include "font.hpp"
#include <vector>
#include <vcruntime_exception.h>
#include <iostream>

namespace kdr {
	Font::Font(const char* ref_name, const char* file_path, GLuint size)
	: ref_name(ref_name), size(size) {
		atlas  = ftgl::texture_atlas_new(ATLAS_WIDTH, ATLAS_HEIGHT, ATLAS_CHANNELS);
		ftFont = ftgl::texture_font_new_from_file(atlas, size, file_path);
		texture_atlas_upload(atlas);
		//texture_atlas_upload(atlas);
		return;
	}

	Font::~Font() {
		ftgl::texture_atlas_delete(atlas);
		ftgl::texture_font_delete(ftFont);
		return;
	}

	std::vector<Font*> fonts = std::vector<Font*>();

	Font* KDR_AddFont(Font* font) {
		fonts.push_back(font);
		return fonts.back();
	}

	Font* KDR_GetFont(const char* name) {
		for (Font* font : fonts) {
			if (font->getName() == name)
				return font;
		}
		std::runtime_error error = std::runtime_error("Could not find font in KDR_GetFont(const char* message). name = ");
		std::cout << error.what() << ' ' << name << std::endl;
		return nullptr;
	}

	Font* KDR_GetFont(const char* name, GLuint size) {
		for (Font* font : fonts) {
			if (font->getName() == name && font->getSize() == size)
				return font;
		}
		std::runtime_error error = std::runtime_error("Could not find font in KDR_GetFont(const char* message, GLuint size). name and size = ");
		std::cout << error.what() << ' ' << name << ' ' << size << std::endl;
		return nullptr;
	}

	void KDR_CleanFonts() {
		for (int i = 0; i < fonts.size(); ++i)
			delete fonts[i];
		fonts.clear();
		return;
	}
}