#pragma once

#include <GL/glew.h>
#include <span>
#include <stdexcept>
#include <vector>

namespace SDL {

class ShaderProgram;

/**
 * An RAII wrapper around a GLEW shader.
 * Its only use is within a \c ShaderProgram.
 */
class Shader {
	friend class ShaderProgram;
public:
	enum class Type : GLenum {
		compute = GL_COMPUTE_SHADER,
		vertex = GL_VERTEX_SHADER,
		tess_control = GL_TESS_CONTROL_SHADER,
		tess_evaluation = GL_TESS_EVALUATION_SHADER,
		geometry = GL_GEOMETRY_SHADER,
		fragment = GL_FRAGMENT_SHADER,
	};
	struct CompilationError : public std::exception {
		/**
		 * Initialized with a null byte to make conversions to char* result in valid C-strings.
		 */
		std::vector<char> log{ '\0' };
		char const* what() const noexcept override {
			return log.data();
		}
	};
public:
	Shader(Type type, std::span<char const> source);
	Shader() = default;
	Shader(Shader const&) = delete;
	Shader(Shader&&) = default;
	~Shader();
protected:
	static constexpr GLuint INVALID_HANDLE = 0;
	GLuint handle = INVALID_HANDLE;
};

}  // namespace SDL
