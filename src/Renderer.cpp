#include <GL/glew.h>
#include <SDL2/SDL.h>

#include "Renderer.hpp"
#include "SDLError.hpp"
#include "SDLShaderProgram.hpp"
#include "SDLWindow.hpp"

char const* Renderer::POSITION_ATTRIBUTE_NAME = "coord2d";
char const* Renderer::TIME_ATTRIBUTE_NAME = "u_time";
char const* Renderer::RESOLUTION_ATTRIBUTE_NAME = "u_resolution";

Renderer::Renderer(SDL::Window& window, SDL::ShaderProgram& program) : window(window), program(program) {
	position_attribute_location = program.get_attrib_location(POSITION_ATTRIBUTE_NAME);
	time_uniform_location = program.get_uniform_location(TIME_ATTRIBUTE_NAME);
	resolution_uniform_location = program.get_uniform_location(RESOLUTION_ATTRIBUTE_NAME);
}

std::array<GLfloat, 3 * Renderer::DIMENSIONS> const Renderer::vertices{
	0.0,  0.8,  // 1
	-0.8, -0.8,  // 2
	0.8,  -0.8,  // 3
};

void Renderer::render() {
	// white
	glClearColor(1.0, 1.0, 1.0, 1.0);
	glClear(GL_COLOR_BUFFER_BIT);

	program.use();
	glUniform1f(time_uniform_location, current_time);
	glUniform2f(resolution_uniform_location, window.width(), window.height());
	glEnableVertexAttribArray(position_attribute_location);
	glVertexAttribPointer(position_attribute_location, DIMENSIONS, GL_FLOAT, GL_FALSE, 0, vertices.data());
	glDrawArrays(GL_TRIANGLES, 0, vertices.size() / DIMENSIONS);
	glDisableVertexAttribArray(position_attribute_location);

	window.swap();

	current_time += 0.01;
}
