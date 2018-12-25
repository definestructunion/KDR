#ifndef _KDR_BATCHRENDERER_HPP
#define _KDR_BATCHRENDERER_HPP

#include "renderer.hpp"
#include "indexbuffer.hpp"
#include "vertexdata.hpp"

/*
The amount of indices in a sprite
*/
#define RENDERER_INDEX_COUNT  (6)

/*
 The maximum amount of sprites
 allowed to be submitted before
 being forced to flush
 */
#define RENDERER_MAX_SPRITES (16002)

/*
 The size of a sprite as
 4 VertexDatas
 */
#define RENDERER_SPRITE_SIZE (VERTEXDATA_SIZE * 4)

/*
 The size of the buffer data to be submitted
 to OpenGL
 */
#define RENDERER_BUFFER_SIZE (RENDERER_SPRITE_SIZE * RENDERER_MAX_SPRITES)

/*
 The amount of indices in the buffer
 Although we're using IndexBuffer to only draw
 4 indices per sprite, there's still 6 indices in a square
 since it's drawn as 2 triangles
 */
#define RENDERER_INDICES_SIZE (RENDERER_MAX_SPRITES * RENDERER_INDEX_COUNT)

 /*
  The max amount of textures a BatchRenderer
  can hold without having to flush
  OpenGL can have 32 max textures at once
  however, 0 is reserved for a non textured
  object
  */
#define RENDERER_MAX_TEXTURES   31
 /*
  The layout index for each vertex
  */
#define SHADER_VERTEX_INDEX     0
 /*
  The layout index for each UV
  */
#define SHADER_UV_INDEX		    1
 /*
  The layour index for each texture ID
  */
#define SHADER_TID_INDEX	    2
 /*
  The layour index for each color of a vertex
  */
#define SHADER_COLOR_INDEX	    3

namespace kdr {
	class BatchRenderer : public Renderer {
	private:
		/*
		 Vertex array object
		 Stores memory about our
		 completed objects
		 (ID, vertices ect...)
		 */
		GLuint vao;

		/*
		 Vertex buffer object
		 Holds memory about our vertices
		 */
		GLuint vbo;

		/*
		 Since we draw triangles
		 we can reduce how many indices
		 have to be drawn by sharing
		 the same indices with the triangles
		 Lowers the amount of vertices
		 that need to be accounted for
		 and stored
		 */
		IndexBuffer* ibo;

		/*
		 The amount of indices our
		 BatchRenderer is holding
		 */
		GLsizei index_count;

		/*
		 Struct that stores
		 all the needed information
		 for each vertex
		 */
		VertexData* buffer;

		/*
		 The textures currently bound
		 to our BatchRenderer
		 When it reaches RENDERER_MAX_TEXTURES (31)
		 it flushes all the current submitted data
		 */
		std::vector<GLuint> shader_tex_ids;

		/*
		 Fills our buffer (VertexData*) with the required
		 information and then increments the pointer
		 to be filled again if needed
		 */
		void fillBuffer(const vec3& vertex, const vec2& uv, const float tid, const unsigned int color);

		/*
		 If the BatchRenderer needs to be flushed, it
		 flushes all the data stored so far
		 @param expected_indices_count: the amount of
		 indices the submitted data will yield
		 Text will be 6 indices per glyph
		 */
		void flushIfNeeded(const int expected_indices_count);

		/*
		 Returns the texture slot index in our shader_tex_ids
		 */
		float getSlot(const float texture_id);

		/*
		 Returns the texture slot index in our shader_tex_ids
		 If you call getSlot when drawing a string, it will flicker
		 every glyph as a box because the texture_id is 0 by default
		 */
		float getSlotString(const float texture_id);

		/*
		 Returns true if the texture_id is present in
		 the shader_tex_ids
		 If false, pushes back the texture_id and changes
		 slot to the end of the vector size
		 */
		bool getFound(const float texture_id, float& slot);

	public:
		/*
		 An efficient renderer that batches textures
		 and vertices together
		 */
		BatchRenderer(TileData tile_info);
		/*
		 An efficient renderer that batches textures
		 and vertices together
		 */
		~BatchRenderer();

		/*
		 Begins the BatchRenderer
		 for accepting submitted data
		 */
		void begin() override;

		/*
		 Ends the BatchRenderer
		 allowing it to draw all
		 the submitted data
		 */
		void end() override;

		/*
		 Draws a textured square to a tile according to the
		 x and y values
		 */
		void draw(const Texture* texture, const int x, const int y, const unsigned int color) override;

		/*
		 Draws a colored square to a tile according to the
		 x and y values
		 */
		void draw(const unsigned int color, const int x, const int y) override;

		/*
		 Draws a texture to the screen without tiled restrictions
		 */
		void draw(const Texture* texture, const vec3& position, const vec2& scale, const unsigned int color) override;
		
		/*
		 Draws a message to the screen according to the
		 x and y values
		 */
		void drawString(const char* text, const Font& font, const int x, const int y) override;
		

		/*
		 Draws a message to the screen without tile restrictions
		 */
		void drawString(const char* text, const Font& font, const vec3& position) override;

		/*
		 Sends all the data to OpenGL
		 and displays all the submitted
		 data onto the screen
		 */
		void flush() override;
	};
}

#endif // hi :)