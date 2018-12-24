#ifndef _KDR_INDEXBUFFER_HPP
#define _KDR_INDEXBUFFER_HPP

typedef unsigned int   GLuint;
typedef unsigned short GLushort;
typedef int            GLsizei;

namespace kdr {
	/*
	 Allows the ability to reduce vertices and improve performance
	 by having less bound vertices
	 */
	class IndexBuffer {
	private:
		/*
		 OpenGL's ID for this buffer for
		 binding and unbinding
		 */
		GLuint buffer_id;

		/*
		 The amount of vertices in this buffer
		 */
		GLuint count;

	public:
		/*
		 Allows the ability to reduce vertices and improve performance
		 by having less bound vertices
		 @param data: the vertices being fed into
		 this indexbuffer
		 @param count: the amount of vertices being fed itno
		 this indexbuffer
		 */
		IndexBuffer(GLushort* data, GLsizei count);

		/*
		 Allows the ability to reduce vertices and improve performance
		 by having less bound vertices
		 @param data: the vertices being fed into
		 this indexbuffer
		 @param count: the amount of vertices being fed itno
		 this indexbuffer
		 */
		IndexBuffer(GLuint* data, GLsizei count);

		/*
		 Deletes the vertex buffer object from OpenGL
		 */
		~IndexBuffer();

		/*
		 Binds the IndexBuffer to OpenGL
		 */
		void bind() const;

		/*
		 Unbinds the IndexBuffer from OpenGL
		 */
		void unbind() const;

		/*
		 Gets the amount of vertices in the IndexBuffer
		 */
		const GLuint getCount() const;

	};
}

#endif // hi :)