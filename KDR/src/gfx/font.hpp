#ifndef _KDR_FONT_HPP
#define _KDR_FONT_HPP

#define ATLAS_WIDTH    (512)
#define ATLAS_HEIGHT   (512)
#define ATLAS_CHANNELS (2)

#include "../ext/freetype-gl/freetype-gl.h"

namespace kdr {
	/*
	 Wrapper class which contains information for
	 glyph rendering
	 */
	class Font {
	private:
		/*
		 The atlas where glyphs get
		 packed onto
		 */
		ftgl::texture_atlas_t* atlas;
		/*
		 The actual font being used for rendering
		 */
		ftgl::texture_font_t* ftFont;

		/*
		 A reference name for accessing if there is
		 texture management
		 */
		const char* ref_name;

		/*
		 Size of the font
		 */
		GLuint size;

	public:
		/*
		 Wrapper class which contains information for
		 glyph rendering
		 @param ref_name: the name of reference for future lookup
		 @param file_path: the path to the TTF file
		 @param size: size of the font
		 */
		Font(const char* ref_name, const char* file_path, GLuint size);
		/*
		 Deletes the texture atlas and the ftgl font
		 */
		~Font();

		/*
		 Returns the texture ID of the font's atlas
		 */
		inline const GLuint getID() const {
			return atlas->id;
		}

		/*
		 Returns the ftgl font that this font is using
		 */
		inline const ftgl::texture_font_t* getFTFont() const {
			return ftFont;
		}

		/*
		 Returns the size of the font
		 */
		inline const GLuint getSize() const {
			return size;
		}

		inline const char* getName() const {
			return ref_name;
		}
	};

	/*
	 Adds a font pointer to a super secret vector
	 of Fonts
	 Returns the added font if you want to add and get
	 the Font
	 */
	Font* KDR_AddFont(Font* font);
	/*
	 Gets a font pointer from a super secret vector
	 of Fonts
	 Returns the font based on the name specified
	 Throws a runtime error if the font can't be found
	 */
	Font* KDR_GetFont(const char* name);
	/*
	 Gets a font pointer from a super secret vector
	 of Fonts
	 Returns the font based on the name and size specified
	 Throws a runtime error if the font can't be found
	 */
	Font* KDR_GetFont(const char* name, GLuint size);
	/*
	 Deletes every font pointer from the
	 super secret vector of Fonts
	 */
	void KDR_CleanFonts();
}

#endif // hi :)