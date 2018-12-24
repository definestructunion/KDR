#ifndef _KDR_TEXTURE_HPP
#define _KDR_TEXTURE_HPP

typedef unsigned int GLuint;

namespace kdr {
	/*
	Basic texture for OpenGL
	*/
	class Texture
	{
	private:
		/*
		The ID for the texture
		*/
		GLuint texture_id;
		/*
		The information for the texture
		*/
		unsigned char* local_buffer;
		/*
		Dimensions of the texture
		*/
		int width, height;
		/*
		The BPP of the texture
		*/
		int bits_per_pixel;

		/*
		Loads the texture into memory
		*/
		void load(const char* file_path);

	public:
		/*
		Basic texture for OpenGL
		*/
		Texture(const char* file_path);

		/*
		Deletes the texture from OpenGL
		*/
		~Texture();

		/*
		Binds the texture to OpenGL
		*/
		void bind() const;

		/*
		Unbinds the texture from OpenGL
		*/
		void unbind() const;

		/*
		Returns the texture's width
		*/
		inline int getWidth() const { return width; }

		/*
		Returns the texture's height
		*/
		inline int getHeight() const { return height; }

		/*
		Returns the ID of the texture
		*/
		inline GLuint getID() const { return texture_id; }
	};
}

#endif // hi :)
