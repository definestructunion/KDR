#ifndef _KDR_UTILFILES_HPP
#define _KDR_UTILFILES_HPP

#include <string>
#include <sstream>
#include <fstream>
#include <vcruntime_exception.h>
#include <iostream>

namespace kdr {

	/*
	 Reads a shader file that contains both a vertex and fragment shader
	 Returns vertex at slot 0 and fragment at slot 1
	 @param type_identifier: the name of the shader token
	 that allows the stream to know which shader it's reading from
	 @param vertex_name: name of the vertex shader
	 @param fragment_name: name of the fragment shader
	 @return pointer to array of size 2. Recommended to call delete
	 once done linking the shader to OpenGL
	 */
	inline std::string* KDR_ReadShaderFile(const char* file_path, const char* type_identifier = "#shader", const char* vertex_name = "vertex", const char* fragment_name = "fragment") {
		enum Shader {
			None = -1,
			Vertex = 0,
			Fragment = 1
		};

		std::ifstream stream = std::ifstream(file_path);
		std::stringstream ss[2];

		// the shader file being read from and
		// written to
		Shader shader = Shader::None;

		// current shader line
		std::string line;

		// while there are still lines to be read from
		// keep looping through and setting line
		// equal to the file's line
		while (getline(stream, line)) {
			// if the line contains the shader identifier
			// then check whether or not the name is equal to
			// vertex_name or fragment_name
			// if neither name could be found
			// thro
			if (line.find(type_identifier) != std::string::npos) {
				// if the line has identified the vertex shader
				// then we set the shader type to vertex
				if (line.find(vertex_name) != std::string::npos)
					shader = Shader::Vertex;
				// if the line has identified the fragment shader
				// then we set the shader type to fragment
				else if (line.find(fragment_name) != std::string::npos)
					shader = Shader::Fragment;
				else {
					// it's upon the user to ensure they sent in the correct names
					// for the vertex and fragment shader
					// if none of the shader names match
					// throw a runtime error informing the user
					// that they have invalid shader names
					// then throw an error to stop execution
					std::runtime_error error = std::runtime_error("Unable to read shader file:\nInvalid shader name type");
					std::cout << error.what() << std::endl;
					throw error;
				}
			}

			// we're using else to avoid
			// adding #shader vertex/fragment shader
			// since OpenGL will try to compile it
			else
				// we can implicitely cast Shader to int
				// and only Shader::None is out of bounds

				// since we are reading line by line
				// add '\n' at the end of the line
				// as adding line by default doesn't add
				// '\n' to the stringstream
				// and compiling shaders
				// is very dependent on lines
				ss[shader] << line << '\n';
		}

		return new std::string[2] { ss[0].str(), ss[1].str() };
	}

	/*
	 Reads a shader string that contains a vertex and/or fragment shader
	 Returns vertex at slot 0 and fragment at slot 1
	 @param type_identifier: the name of the shader token
	 that allows the stream to know which shader it's reading from
	 @param vertex_name: name of the vertex shader
	 @param fragment_name: name of the fragment shader
	 @return pointer to array of size 2. Recommended to call delete
	 once done linking the shader to OpenGL
	 */
	inline std::string* KDR_ReadShaderString(const char* shader_string, const char* type_identifier = "#shader", const char* vertex_name = "vertex", const char* fragment_name = "fragment") {
		enum Shader {
			None = -1,
			Vertex = 0,
			Fragment = 1
		};
		
		std::istringstream string(shader_string);
		std::stringstream ss[2];

		// the shader file being read from and
		// written to
		Shader shader = Shader::None;

		// current shader line
		std::string line;

		// while there are still lines to be read from
		// keep looping through and setting line
		// equal to the file's line
		while (getline(string, line, '\n')) {
			// if the line contains the shader identifier
			// then check whether or not the name is equal to
			// vertex_name or fragment_name
			// if neither name could be found
			// thro
			if (line.find(type_identifier) != line.npos) {
				// if the line has identified the vertex shader
				// then we set the shader type to vertex
				if (line.find(vertex_name) != line.npos)
					shader = Shader::Vertex;
				// if the line has identified the fragment shader
				// then we set the shader type to fragment
				else if (line.find(fragment_name) != line.npos)
					shader = Shader::Fragment;
				else {
					// it's upon the user to ensure they sent in the correct names
					// for the vertex and fragment shader
					// if none of the shader names match
					// throw a runtime error informing the user
					// that they have invalid shader names
					// then throw an error to stop execution
					std::runtime_error error = std::runtime_error("Unable to read shader file:\nInvalid shader name type");
					std::cout << error.what() << std::endl;
					throw error;
				}
			}

			// we're using else to avoid
			// adding #shader vertex/fragment shader
			// since OpenGL will try to compile it
			else
				// we can implicitely cast Shader to int
				// and only Shader::None is out of bounds
				ss[shader] << line << '\n';
		}

		return new std::string[2]{ ss[0].str(), ss[1].str() };
	}
}

#endif // hi :)