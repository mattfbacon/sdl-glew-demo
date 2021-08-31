#pragma once

#include <span>

#include "SDLShader.hpp"

namespace SDL {

/**
 * An RAII wrapper around a GLEW Program.
 * Allows the creation of a shader program with vertex and fragment shaders.
 */
class ShaderProgram {
public:
	struct LinkerError : public std::exception {
		/**
		 * Initialized with a null byte to make conversions to char* result in valid C-strings.
		 */
		std::vector<char> log{ '\0' };
		char const* what() const noexcept override {
			return log.data();
		}
	};
public:
	ShaderProgram(std::span<char const> vertex_source, std::span<char const> fragment_source);
	ShaderProgram(ShaderProgram const&) = delete;
	ShaderProgram(ShaderProgram&&) = default;
	~ShaderProgram();
	/**
	 * Make the program the current one, so it can be used for rendering
	 */
	void use() {
		glUseProgram(handle);
	}
	/**
	 * Get the location/handle of an attribute
	 */
	GLint get_attrib_location(char const* name);
	/**
	 * Get the location/handle of a uniform
	 */
	GLint get_uniform_location(char const* name);
protected:
	static constexpr GLint INVALID_ATTRIB_LOCATION = -1;
	static constexpr GLuint INVALID_HANDLE = 0;
	GLuint handle = INVALID_HANDLE;
	/**
	 * Reserve two slots for vertex and fragment
	 */
	std::vector<Shader> shaders{ 2 };
};
}  // namespace SDL
