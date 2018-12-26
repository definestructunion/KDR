#ifndef _KDR_RENDERER_HPP
#define _KDR_RENDERER_HPP

#include "../rectangle.hpp"
#include "../../math/math.hpp"
#include "../texture.hpp"
#include "../font.hpp"
#include <vector>

namespace kdr {
	/*
	 Stores information about tiles
	 */
	struct TileData {
		/*
		 Size of the x and y
		 dimensions of a tile
		 */
		unsigned char tile_size;
		/*
		 How far the renderer is offset
		 from the window's origin
		 */
		unsigned short offset_x, offset_y;

		/*
		 Stores information about tiles
		 */
		TileData(unsigned char tile_size, unsigned short offset_x, unsigned short offset_y);
	};


	/*
	 Base class for rendering objects to a window
	 Includes basic functions that every renderer should need
	 Has transform stacks that allow GUI to push in a transform
	 Submit all the data with that pushed transform
	 then pop it out once all the data is submitted
	 Does not have it's own drawing functions as each renderer
	 will handle it differently
	 */
	class Renderer abstract {
	protected:
		/*
		 The texture coordinates of the
		 sprite
		 */
		vec2 uv[4] = {
			vec2(0, 0),
			vec2(0, 1),
			vec2(1, 1),
			vec2(1, 0)
		};

		/*
		 The transforms of the Renderer
		 */
		std::vector<mat4> transforms;
		/*
		 The backmost transform currently in use
		 by the Renderer
		 */
		const mat4* transforms_back;

		/*
		 This renderer's information about tile
		 drawing
		 */
		const TileData tiles;

		/*
		 Adds a matrix identity to the back of the transforms vector
		 */
		Renderer(TileData tile_info);

	public:
		/*
		 Pushes a matrix to the back of the vector
		 Renderer always uses the backmost matrix
		 @param matrix: the matrix being pushed back and multiplied
		 by the previous back of the vector
		 */
		void push(const mat4& matrix);

		/*
		 Pushes a matrix to the back of a vector
		 Renderer always uses the backmost matrix
		 Does not multiply the already backmost matrix
		 with the newly added matrix
		 @param matrix: the matrix being pushed back
		 */
		void pushOverride(const mat4& matrix);

		/*
		 Removes the last matrix from the matrix vector
		 */
		void pop();

		/*
		 Begins the process of submitting
		 data to the Renderer
		 */
		virtual void begin() = 0;

		/*
		 End the process of submitting
		 data to the Renderer
		 */
		virtual void end() = 0;

		/*
		 Flushes all the data added
		 to the Renderer and
		 removes it from the Renderer
		 */
		virtual void flush() = 0;

		/*
		 Draws a textured square to a tile according to the
		 x and y values
		 */
		virtual void draw(const Texture* texture, const int x, const int y, const unsigned int color) = 0;

		/*
		 Draws a colored square to a tile according to the
		 x and y values
		 */
		virtual void draw(const unsigned int color, const int x, const int y) = 0;

		/*
		 Draws a texture to the screen without tiled restrictions
		 */
		virtual void draw(const Texture* texture, const vec3& position, const vec2& scale, const unsigned int color) = 0;

		/*
		 Draws a texture to the screen without tiled restrictions
		 */
		virtual void draw(const Texture* texture, const Rectangle& rect, const unsigned int color) = 0;

		/*
		 Draws a message to the screen according to the
		 x and y values
		 */
		virtual void drawString(const char* text, const Font& font, const int x, const int y, const unsigned int color) = 0;

		/*
		 Draws a message to the screen without tile restrictions
		 */
		virtual void drawString(const char* text, const Font& font, const vec3& position, const unsigned int color) = 0;
	};
}

#endif // hi :)