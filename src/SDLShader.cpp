#include "SDLError.hpp"
#include "SDLShader.hpp"

namespace SDL {

Shader::Shader(Type const type, std::span<char const> const source) {
	GLint status = GL_FALSE;
	handle = glCreateShader(static_cast<GLenum>(type));
	if (handle == INVALID_HANDLE) {
		throw Error{ Error::Category::glew, { .uint = glGetError() } };
	}
	{
		char const* data_ptr[1]{ source.data() };
		int const data_size[1]{ static_cast<int>(source.size()) };
		glShaderSource(handle, 1, data_ptr, data_size);
	}
	glCompileShader(handle);
	glGetShaderiv(handle, GL_COMPILE_STATUS, &status);
	if (status == GL_FALSE) {
		CompilationError error;
		GLint log_length;
		glGetShaderiv(handle, GL_INFO_LOG_LENGTH, &log_length);
		error.log.reserve(log_length);
		glGetShaderInfoLog(handle, log_length, &log_length, error.log.data());
		throw error;
	}
}

Shader::~Shader() {
	// checks validity
	glDeleteShader(handle);
	handle = INVALID_HANDLE;
}

}  // namespace SDL
