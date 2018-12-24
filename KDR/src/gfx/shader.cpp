#include "shader.hpp"
#include "../util/utilfiles.hpp"

#include <GL/glew.h>
#include <iostream>
#include <string>

namespace kdr {
	const char* kdr_standard =
	"#shader vertex\n"
	"#version 330 core\n"
	"layout(location = 0) in vec4 position;\n"
	"layout(location = 1) in vec2 uv;\n"
	"layout(location = 2) in float tid;\n"
	"layout(location = 3) in vec4 color;\n"

	"uniform mat4 pr_matrix;\n"
	"uniform mat4 vw_matrix = mat4(1.0);\n"
	"uniform mat4 ml_matrix = mat4(1.0);\n"

	"out DATA {\n"
	"	vec4 position;\n"
	"	vec2 uv;\n"
	"	float tid;\n"
	"	vec4 color;\n"
	"} vs_out;\n"

	"void main() {\n"
	"	gl_Position = pr_matrix * vw_matrix * ml_matrix * position;\n"
	"	vs_out.position = ml_matrix * position;\n"
	"	vs_out.uv = uv;\n"
	"	vs_out.tid = tid;\n"
	"	vs_out.color = color;\n"
	"}\n"

	"#shader fragment\n"
	"#version 330 core\n"

	"layout(location = 0) out vec4 color;\n"

	"uniform vec4 colour;\n"
	"uniform vec2 light_pos;\n"

	"in DATA\n"
	"{\n"
	"	vec4 position;\n"
	"	vec2 uv;\n"
	"	float tid;\n"
	"	vec4 color;\n"
	"} fs_in;\n"

	"uniform sampler2D textures[32];\n"

	"void main() {\n"
	"	vec4 texColor = fs_in.color;\n"
	"	if (fs_in.tid > 0.0) {\n"
	"		int tid = int(fs_in.tid - 0.5);\n"
	"		texColor = fs_in.color * texture(textures[tid], fs_in.uv);\n"
	"	}\n"
	"	color = texColor;\n"
	"}";

	Shader::Shader() {
		shader_id = load(kdr_standard, false, "#shader", "vertex", "fragment");
		return;
	}

	Shader::Shader(const char* file, bool is_file, const char* type_identifier, const char* vertex_name, const char* fragment_name) {
		shader_id = load(file, is_file, type_identifier, vertex_name, fragment_name);
		return;
	}

	GLuint Shader::load(const char* file, bool is_file, const char* type_identifier, const char* vertex_name, const char* fragment_name) const {
		// program will become our shader_id
		GLuint program = glCreateProgram();
		// create shaders using OpenGL and specify 
		// that our shaders will be fragment and vertex
		// shaders
		GLuint vertex   = glCreateShader(GL_VERTEX_SHADER);
		GLuint fragment = glCreateShader(GL_FRAGMENT_SHADER);

		std::string* sources = is_file ? KDR_ReadShaderFile(file, type_identifier, vertex_name, fragment_name)
									   : KDR_ReadShaderString(file, type_identifier, vertex_name, fragment_name);

		const char* vertex_source = sources[0].c_str();
		const char* fragment_source = sources[1].c_str();

		// give OpenGL the vertex source as it will be compiled first
		// and once it's done compiling, get the result of the compilation
		// and print any errors that happened while compiling
		glShaderSource(vertex, 1, &vertex_source, NULL);
		glCompileShader(vertex);

		// get the compiling status
		// GL_FALSE for failed compilation
		// GL_TRUE for successful compilation
		int result = GL_FALSE;
		glGetShaderiv(vertex, GL_COMPILE_STATUS, &result);
		
		if (result == GL_FALSE) {
			// length of the log message
			int length = 0;
			glGetShaderiv(vertex, GL_INFO_LOG_LENGTH, &length);
			// we need to dynamically allocate
			// since the size of the error is
			// not compile time compliant
			char* error = new char[length];

			// set the characters in error with the
			// compilation error message
			// and print it out the terminal
			glGetShaderInfoLog(vertex, length, &length, &error[0]);
			std::cout << "Vertex shader:\n" << &error[0] << std::endl;
			// delete the vertex shader from OpenGL
			glDeleteShader(vertex);

			// delete the error message
			delete[] error;

			// return an unbindable shader ID
			return NULL;
		}
		
		// repeat the same process but with the fragment shader
		
		glShaderSource(fragment, 1, &fragment_source, NULL);
		glCompileShader(fragment);
		glGetShaderiv(fragment, GL_COMPILE_STATUS, &result);

		if (result == GL_FALSE) {
			int length = 0;
			glGetShaderiv(fragment, GL_INFO_LOG_LENGTH, &length);
			char* error = new char[length];
			glGetShaderInfoLog(fragment, length, &length, &error[0]);
			std::cout << "Fragment shader:\n" << &error[0] << std::endl;
			glDeleteShader(fragment);
			delete[] error;
			return NULL;
		}

		// attach the shaders to this
		// shader, our program
		glAttachShader(program, vertex);
		glAttachShader(program, fragment);

		// link our program to OpenGL
		// and ensure the program
		// can run in the current OpenGL
		// state
		glLinkProgram(program);
		glValidateProgram(program);

		// now we delete our old shaders from OpenGL
		// including our sources
		glDeleteShader(vertex);
		glDeleteShader(fragment);
		delete[] sources;
		// return the program AKA shader ID
		return program;
	}

	Shader::~Shader() {
		glDeleteProgram(shader_id);
		return;
	}

	void Shader::bind() const {
		glUseProgram(shader_id);
		return;
	}

	void Shader::unbind() const {
		glUseProgram(NULL);
		return;
	}

	int Shader::getUniformLocation(const char* name) {
		return glGetUniformLocation(shader_id, name);
	}

	void Shader::setUniform1f(const char* name, float value) {
		glUniform1f(getUniformLocation(name), value);
		return;
	}

	void Shader::setUniform1fv(const char* name, float* value, int count) {
		glUniform1fv(getUniformLocation(name), count, value);
		return;
	}

	void Shader::setUniform1i(const char* name, int value) {
		glUniform1i(getUniformLocation(name), value);
		return;
	}

	void Shader::setUniform1iv(const char* name, int* value, int count) {
		glUniform1iv(getUniformLocation(name), count, value);
		return;
	}

	void Shader::setUniform2f(const char* name, const vec2& vector) {
		glUniform2f(getUniformLocation(name), vector.x, vector.y);
		return;
	}

	void Shader::setUniform3f(const char* name, const vec3& vector) {
		glUniform3f(getUniformLocation(name), vector.x, vector.y, vector.z);
		return;
	}

	void Shader::setUniform4f(const char* name, const vec4& vector) {
		glUniform4f(getUniformLocation(name), vector.x, vector.y, vector.z, vector.w);
		return;
	}

	void Shader::setUniformMat4(const char* name, const mat4& matrix) {
		glUniformMatrix4fv(getUniformLocation(name), 1, GL_FALSE, matrix.elements);
		return;
	}

	GLuint Shader::getID() const {
		return shader_id;
	}
}