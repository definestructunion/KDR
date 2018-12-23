#ifndef _KDR_SHADER_HPP
#define _KDR_SHADER_HPP

#include "../math/vec.hpp"
#include "../math/mat4.hpp"

namespace kdr {
	/*
	 An unsigned int to mimic OpenGL API
	 */
	typedef unsigned int GLuint;

	/*
	 Program ran on the GPU
	 KDR uses fragment and vertex shaders
	 */
	class Shader {
	private:
		/*
		 OpenGL's ID for this shader program
		 NULL is an unbound program
		 */
		GLuint shader_id;

		/*
		 Loads the shader and links the program to OpenGL
		 @param file: the string/path of the file
		 @param is_file: determines if it's read from
		 a file or if file is read as a string
		 @return the shader's ID
		 */
		GLuint load(const char* file, bool is_file, const char* type_identifier, const char* vertex_name, const char* fragment_name) const;

		/*
		Looks in the string for "name"
		Returns the layout index of "name"
		*/
		int getUniformLocation(const char* name);

	public:
		/*
		 Creates the KDR default shader
		 which sets the projection matrix
		 to the dimensions of the screen
		 */
		Shader();

		/*
		 Reads a shader from either a string
		 or a file
		 @param file: the string/path of the file
		 @param is_file: determines if it's read from
		 a file or if file is read as a string
		 */
		Shader(const char* file, bool is_file, const char* type_identifier, const char* vertex_name, const char* fragment_name);

		/*
		 Deletes the shader from OpenGL
		 */
		~Shader();
		
		/*
		 Binds the shader to OpenGL
		 */
		void bind() const;

		/*
		 Unbinds the shader from OpenGL
		 */
		void unbind() const;

		/*
		Sets the variable of name to 1 float value
		*/
		void setUniform1f(const char* name, float value);
		/*
		Sets the variable of name to an array of floats
		*/
		void setUniform1fv(const char* name, float* value, int count);
		/*
		Sets the variable of name to an array of ints
		*/
		void setUniform1iv(const char* name, int* value, int count);
		/*
		Sets the variable of name to 1 int value
		*/
		void setUniform1i(const char* name, int value);
		/*
		Sets the variable of name to 2 float values
		*/
		void setUniform2f(const char* name, const vec2& vector);
		/*
		Sets the variable of name to 3 float values
		*/
		void setUniform3f(const char* name, const vec3& vector);
		/*
		Sets the variable of name to 4 float values
		*/
		void setUniform4f(const char* name, const vec4& vector);
		/*
		Sets the variable of name to a matrix
		*/
		void setUniformMat4(const char* name, const mat4& matrix);

		/*
		 Returns the ID of the shader
		 as a program in OpenGL
		 */
		GLuint getID() const;
	};
}

#endif // hi :)