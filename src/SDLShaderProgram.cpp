#include "SDLError.hpp"
#include "SDLShaderProgram.hpp"

namespace SDL {

ShaderProgram::ShaderProgram(std::span<char const> const vertex_source, std::span<char const> const fragment_source) {
	GLint status = GL_FALSE;

	shaders.emplace_back(Shader::Type::vertex, vertex_source);
	shaders.emplace_back(Shader::Type::fragment, fragment_source);
	handle = glCreateProgram();
	if (handle == INVALID_HANDLE) {
		throw Error{ Error::Category::glew, { .uint = glGetError() } };
	}
	for (auto const& shader : shaders) {
		// FIXME: is there a way to check for errors here?
		glAttachShader(handle, shader.handle);
	}
	glLinkProgram(handle);
	glGetProgramiv(handle, GL_LINK_STATUS, &status);
	if (status == GL_FALSE) {
		LinkerError error;
		GLint log_length;
		glGetShaderiv(handle, GL_INFO_LOG_LENGTH, &log_length);
		error.log.reserve(log_length);
		glGetShaderInfoLog(handle, log_length, &log_length, error.log.data());
		throw error;
	}
}

ShaderProgram::~ShaderProgram() {
	// checks validity
	glDeleteProgram(handle);
	handle = INVALID_HANDLE;
}

GLint ShaderProgram::get_attrib_location(char const* const name) {
	auto const ret = glGetAttribLocation(handle, name);
	return ret;
}
GLint ShaderProgram::get_uniform_location(char const* const name) {
	auto const ret = glGetUniformLocation(handle, name);
	return ret;
}

}  // namespace SDL
