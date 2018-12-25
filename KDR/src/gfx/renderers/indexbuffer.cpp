#include "indexbuffer.hpp"

namespace kdr {
	IndexBuffer::IndexBuffer(GLushort* data, GLsizei count)
	: count(count) {
		// generates a buffer and we're going
		// to retrieve the ID from the generation
		// and give it to our IndexBuffer's ID
		glGenBuffers(1, &buffer_id);
		// bind the buf
		glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, buffer_id);
		// our buffer is an array buffer
		// with size of the count (amount of elements)
		// multiplied by the size of a unsigned short
		
		// since the index buffer is designed to be used over and over
		// without changing the indices in the data
		// the ordering of how we're drawing rectangles never changes
		// therefor, we should do GL_STATIC_DRAW as GL_DYNAMIC_DRAW
		// expects data to be changed
		glBufferData(GL_ELEMENT_ARRAY_BUFFER, count * sizeof(GLushort), data, GL_STATIC_DRAW);
		// unbind the index buffer from OpenGL
		// once we are done setting the data
		// for the buffer
		glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);
		return;
	}

	IndexBuffer::IndexBuffer(GLuint* data, GLsizei count)
	: count(count) {
		// generates a buffer and we're going
		// to retrieve the ID from the generation
		// and give it to our IndexBuffer's ID
		glGenBuffers(1, &buffer_id);
		// bind the buf
		glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, buffer_id);
		// our buffer is an array buffer
		// with size of the count (amount of elements)
		// multiplied by the size of a unsigned short

		// since the index buffer is designed to be used over and over
		// without changing the indices in the data
		// the ordering of how we're drawing rectangles never changes
		// therefor, we should do GL_STATIC_DRAW as GL_DYNAMIC_DRAW
		// expects data to be changed
		glBufferData(GL_ELEMENT_ARRAY_BUFFER, count * sizeof(GLuint), data, GL_STATIC_DRAW);
		// unbind the index buffer from OpenGL
		// once we are done setting the data
		// for the buffer
		glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);
		return;
	}

	IndexBuffer::~IndexBuffer() {
		// we're deleting 1 buffer (this buffer)
		// and this buffer is stored as buffer_id
		// so we're deleting that buffer from OpenGL
		glDeleteBuffers(1, &buffer_id);
		return;
	}

	void IndexBuffer::bind() const {
		// bind this buffer to OpenGL
		// as an array buffer
		glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, buffer_id);
		return;
	}

	void IndexBuffer::unbind() const {
		// unbind this buffer from OpenGL
		// as an array buffer
		// 0 is considered an invalid buffer ID
		glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);
		return;
	}

	const GLuint IndexBuffer::getCount() const {
		return count;
	}
}