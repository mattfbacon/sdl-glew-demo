#pragma once

#include <GL/glew.h>
#include <array>

namespace SDL {
class Window;
class ShaderProgram;
}  // namespace SDL

/**
 * User-defined class to render the shader program.
 * It gets the locations of attributes and uniforms in order to set them in \c render.
 * It also includes the vertex data of the shapes drawn by the vertex shader.
 */
class Renderer {
public:
	Renderer(SDL::Window& window, SDL::ShaderProgram& program);
	Renderer(Renderer const&) = delete;
	Renderer(Renderer&&) = default;
	/**
	 * Render the shader program to the window. Sets uniforms and attributes accordingly.
	 */
	void render();
protected:
	SDL::Window& window;
	SDL::ShaderProgram& program;
protected:
	static char const* POSITION_ATTRIBUTE_NAME;
	static char const* TIME_ATTRIBUTE_NAME;
	static char const* RESOLUTION_ATTRIBUTE_NAME;
	GLint position_attribute_location;
	GLint time_uniform_location;
	GLint resolution_uniform_location;
protected:
	/**
	 * Incremented every time \c render is called.
	 */
	float current_time = 0.0;
	static constexpr GLint DIMENSIONS = 2;
	static std::array<GLfloat, 3 * DIMENSIONS> const vertices;
};
