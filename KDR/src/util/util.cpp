#include "util.hpp"
#include "GL/glew.h"
#include <iostream>
#include <iomanip>

void gl_clear_errors()
{
	while (glGetError() != GL_NO_ERROR); // while there are still errors, this also clears errors
}

void gl_check_errors()
{
	while (GLenum error = glGetError())
		//std::cout << "[OpenGL Error] " << std::hex << error << std::endl;
		std::cout << std::hex << std::showbase << error << std::endl;
}

bool gl_log_call(const char* function, const char* file, int line)
{
	while (GLenum error = glGetError())
	{
		std::cout << "[OpenGL Error] " << std::hex << std::showbase << error << "\nFunction: " << function << "\nFile: " << file << std::dec << std::noshowbase << "\nLine: " << line << std::endl;

		return false;
	}

	return true;
}