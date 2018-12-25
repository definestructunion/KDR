#include "batchrenderer.hpp"
#include <string.h>

namespace kdr {
	BatchRenderer::BatchRenderer(TileData tile_info)
	: Renderer(tile_info) {
		// reserve this vector by how many slots are allowed to be bound to OpenGL
		// allows push_back to not have to copy the vector over and over
		shader_tex_ids.reserve(RENDERER_MAX_TEXTURES);

		// generate 1 vertex array
		glGenVertexArrays(1, &vao);
		// generate 1 vbo
		glGenBuffers(1, &vbo);

		// bind the vertex array and VBO to allow the following
		// shitstorm of macros to effect the VAO and VBO
		glBindVertexArray(vao);
		glBindBuffer(GL_ARRAY_BUFFER, vbo);

		// tell OpenGL the details of our buffer data (VertexData*)
		// it's an array
		// it's the size of RENDERER_BUFFER_SIZE
		// the data is currently 0 (NULL)
		// the buffer is going to be changing so it's
		// going to be a dynamic draw
		glBufferData(GL_ARRAY_BUFFER, RENDERER_BUFFER_SIZE, NULL, GL_DYNAMIC_DRAW);

		// tell OpenGL that:
		// our vertices are at index      0 (SHADER_VERTEX_INDEX)
		// our UVs are at index           1 (SHADER_UV_INDEX    )
		// our texture IDs are at index   2 (SHADER_TID_INDEX   )
		// our colors are at index        3 (SHADER_COLOR_INDEX )
		glEnableVertexAttribArray(SHADER_VERTEX_INDEX);
		glEnableVertexAttribArray(SHADER_UV_INDEX);
		glEnableVertexAttribArray(SHADER_TID_INDEX);
		glEnableVertexAttribArray(SHADER_COLOR_INDEX);

		// now that we've enabled these variables and told OpenGL where to look for them
		// in the shader
		// we tell OpenGL what this data means
		// aka, OpenGL data interpretation

		// our vertices are vec3's which are
		// 3 floats (3, GL_FLOAT)
		// are not normalized between 0 and 1
		// contained in VertexData (sizeof(VertexData))
		// at offset 0 (they're the first variable so there's 0 offset)
		glVertexAttribPointer(SHADER_VERTEX_INDEX, 3, GL_FLOAT, GL_FALSE, VERTEXDATA_SIZE, (const GLvoid*)0);

		// our UVs are vec2's which are
		// 2 floats (2, GL_FLOAT)
		// are not normalized between 0 and 1
		// contained in VertexData (sizeof(VertexData))
		// with an offset of where our UV is stored in VertexData
		glVertexAttribPointer(SHADER_UV_INDEX, 2, GL_FLOAT, GL_FALSE, VERTEXDATA_SIZE, (const GLvoid*)(offsetof(VertexData, VertexData::uv)));

		// our texture IDS are floats which is
		// 1 float (1, GL_FLOAT)
		// are not normalized between 0 and 1
		// contained in VertexData (sizeof(VertexData))
		// with an offset of where our TID is stored in VertexData
		glVertexAttribPointer(SHADER_TID_INDEX, 1, GL_FLOAT, GL_FALSE, VERTEXDATA_SIZE, (const GLvoid*)(offsetof(VertexData, VertexData::tid)));

		// our color is an unsigned int which is
		// 1 unsigned int, but since there are 4 channels
		// it's 1 byte (256) x 4 channels,
		// which is 4 bytes, the size of an unsigned int
		// is normalized between 0 and 1
		// contained in VertexData (sizeof(VertexData))
		// with an offset of where our color is stored in VertexData
		glVertexAttribPointer(SHADER_COLOR_INDEX, 4, GL_UNSIGNED_BYTE, GL_TRUE, VERTEXDATA_SIZE, (const GLvoid*)(offsetof(VertexData, VertexData::color)));

		// now that we've given all the information we've needed
		// to give, we can unbind it
		glBindBuffer(GL_ARRAY_BUFFER, NULL);

		// we need to set our IBO to all the correct indices
		// 2 triangles is 6 vertices, but since we're drawing
		// squares in our BatchRenderer, two triangles have 2
		// redundant vertices, so we're setting our IBO
		// to have 4 vertices per Square rather than 6
		
		GLushort indices[RENDERER_INDICES_SIZE];

		// offset starts at 0 and is incremented by 4 for each
		// 6 vertices we set
		int offset = 0;

		// i += 6 is done so that we're setting each vertices for
		// 2 triangles, which is 6, but we're setting the values
		// of 2 of them equal to eachother, so that we effictively
		// have 4 indices per square (2 triangles)
		for (int i = 0; i < RENDERER_INDICES_SIZE; i += RENDERER_INDEX_COUNT) {

			//  0
			//   0   1   2
			//   | \     |
			//   |   \   |
			//   |     \ |
			//   2   3   0
			//            0
			//   
			//   2 redundant vertices
			//   see from this nice graph
			//   I made? :)

			indices[  i  ] = offset;
			indices[i + 1] = offset + 1;
			indices[i + 2] = offset + 2;

			indices[i + 3] = offset + 2;
			indices[i + 4] = offset + 3;
			indices[i + 5] = offset;

			offset += 4;
		}

		// now set our IBO to our indices we just
		// made with the amount of indices in our indices
		ibo = new IndexBuffer(indices, RENDERER_INDICES_SIZE);

		// now that we've done all we need to do with our
		// vertex array, unbind it from OpenGL
		glBindVertexArray(NULL);
		return;
	}

	BatchRenderer::~BatchRenderer() {
		// delete our IBO since it's a pointer
		delete ibo;
		// since we're getting rid of our
		// BatchRenderer, we need to also
		// unbind our VBO from OpenGL
		glDeleteBuffers(1, &vbo);
		glDeleteVertexArrays(1, &vao);
		delete[] buffer;
		return;
	}

	void BatchRenderer::begin() {
		// bind the VBO to OpenGL with the
		// data we fed through to OpenGL
		// when creating the BatchRenderer
		glBindBuffer(GL_ARRAY_BUFFER, vbo);
		// begin mapping the buffer as an array buffer
		// since OpenGL doesn't need to read this memory
		// at all, set it to write only so it can optimize
		// this code slightly
		buffer = (VertexData*)glMapBuffer(GL_ARRAY_BUFFER, GL_WRITE_ONLY);
		return;
	}

	void BatchRenderer::end() {
		// unmap the buffer from OpenGL
		// to allow drawing
		glUnmapBuffer(GL_ARRAY_BUFFER);
		// unbind the buffer we bound
		// when beginning the mapping
		glBindBuffer(GL_ARRAY_BUFFER, NULL);
		return;
	}

	void BatchRenderer::draw(const Texture* texture, const int x, const int y, const unsigned int color) {
		// we are submitting 6 vertices (4 being renderered)
		// so we put in RENDERER_INDEX_COUNT (6)
		flushIfNeeded(RENDERER_INDEX_COUNT);
		const int pos_x = (x * tiles.tile_size) + (tiles.offset_x * tiles.tile_size);
		const int pos_y = (y * tiles.tile_size) + (tiles.offset_y * tiles.tile_size);
		const unsigned int& slot = getSlot(texture->getID());

		fillBuffer(*transforms_back * vec3(pos_x, pos_y, 0), uv[0], slot, color);
		fillBuffer(*transforms_back * vec3(pos_x, pos_y + tiles.tile_size, 0), uv[1], slot, color);
		fillBuffer(*transforms_back * vec3(pos_x + tiles.tile_size, pos_y + tiles.tile_size, 0), uv[2], slot, color);
		fillBuffer(*transforms_back * vec3(pos_x + tiles.tile_size, pos_y, 0), uv[3], slot, color);
		index_count += RENDERER_INDEX_COUNT;

		return;
	}

	void BatchRenderer::draw(const unsigned int color, const int x, const int y) {
		flushIfNeeded(RENDERER_INDEX_COUNT);
		const int pos_x = (x * tiles.tile_size) + (tiles.offset_x * tiles.tile_size);
		const int pos_y = (y * tiles.tile_size) + (tiles.offset_y * tiles.tile_size);
		const unsigned int& slot = getSlot(0.0f);

		fillBuffer(*transforms_back * vec3(pos_x, pos_y, 0), uv[0], slot, color);
		fillBuffer(*transforms_back * vec3(pos_x, pos_y + tiles.tile_size, 0), uv[1], slot, color);
		fillBuffer(*transforms_back * vec3(pos_x + tiles.tile_size, pos_y + tiles.tile_size, 0), uv[2], slot, color);
		fillBuffer(*transforms_back * vec3(pos_x + tiles.tile_size, pos_y, 0), uv[3], slot, color);
		index_count += RENDERER_INDEX_COUNT;

		return;
	}

	void BatchRenderer::draw(const Texture* texture, const vec3& position, const vec2& scale, const unsigned int color) {

		return;
	}

	void BatchRenderer::drawString(const char* text, const Font& font, const int x, const int y) {

		return;
	}

	void BatchRenderer::drawString(const char* text, const Font& font, const vec3& position) {

		return;
	}

	void BatchRenderer::flush() {
		for (int i = 0; i < shader_tex_ids.size(); ++i) {
			// bind the texture to OpenGL
			// then set the active texture to the bound texture
			// GL_TEXTURE0 - GL_TEXTURE31 are sequencial
			glBindTexture(GL_TEXTURE_2D, shader_tex_ids[i]);
			glActiveTexture(GL_TEXTURE0 + i);
		}

		// bind our vertex array and IBO
		glBindVertexArray(vao);
		ibo->bind();

		// draw all of our elements
		// as triangles
		// with the size of index_count
		// with type GLuint (unsigned int)
		// we don't need to specify any indices
		// since we've already bound our IBO
		glDrawElements(GL_TRIANGLES, index_count, GL_UNSIGNED_SHORT, NULL);

		// unbind our IBO once we're done drawing the elements
		ibo->unbind();
		// unbind our VAO from OpenGL
		glBindVertexArray(NULL);

		index_count = 0;
		return;
	}

	void BatchRenderer::fillBuffer(const vec3& vertex, const vec2& uv, const float tid, const unsigned int color) {
		buffer->vertex = vertex;
		buffer->uv = uv;
		buffer->tid = tid;
		buffer->color = color;
		++buffer;
		return;
	}

	void BatchRenderer::flushIfNeeded(int expected_indices_count) {
		if (index_count + expected_indices_count >= RENDERER_INDICES_SIZE) {
			// unmap the buffer, flush the submitted data
			// then begin again
			end();
			flush();
			begin();
			// we don't want to reset the texture
			// slots because they aren't the reason
			// we're flushing
		}

		else if (shader_tex_ids.size() >= RENDERER_MAX_TEXTURES) {
			end();
			flush();
			begin();
			// we'll need to clear it so new textures can
			// be used
			shader_tex_ids.clear();
			// we're reserving so that it's faster
			// to push_back
			shader_tex_ids.reserve(RENDERER_MAX_TEXTURES);
		}
		return;
	}

	float BatchRenderer::getSlot(const float texture_id) {
		// if the texture ID is 0
		// then it's considered a non
		// textured draw, therefor return 0
		if (texture_id == 0.0f)
			return 0.0f;

		float slot = 0.0f;
		// if the slot wasn't found
		// as well, if getFound returns true
		// it sets our slot to the correct texture slot
		// anyways
		if (!getFound(texture_id, slot)) {
			// push back our texture ID
			shader_tex_ids.push_back(texture_id);
			// make the slot equal to the back of the vector
			slot = (float)(shader_tex_ids.size());
		}
		return slot;
	}

	float BatchRenderer::getSlotString(const float texture_id) {
		// for text, we don't want to return if the texture_id
		// equals 0 or else the text glyphs will show as a box
		// for 1 frame at the start
		float slot = 0.0f;
		// if the slot wasn't found
		// as well, if getFound returns true
		// it sets our slot to the correct texture slot
		// anyways
		if (!getFound(texture_id, slot)) {
			// push back our texture ID
			shader_tex_ids.push_back(texture_id);
			// make the slot equal to the back of the vector
			slot = (float)(shader_tex_ids.size());
		}
		return slot;
	}

	bool BatchRenderer::getFound(const float texture_id, float& slot) {
		for (unsigned int i = 0; i < shader_tex_ids.size(); ++i)
			// if the texture_ids are equal to eachother
			if (shader_tex_ids[i] == texture_id) {
				// set the slot to i + 1
				slot = (float)(i + 1);
				return true;
			}
		return false;
	}

}