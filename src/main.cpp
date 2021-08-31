#include <SDL2/SDL.h>
#include <cstdlib>
#include <fstream>
#include <iostream>
#include <stdexcept>

#include "MappedFile.hpp"
#include "Renderer.hpp"
#include "SDLInit.hpp"
#include "SDLShaderProgram.hpp"
#include "SDLWindow.hpp"

#if 0
char const* vertex_source
	= "#version 120\n"
		"attribute vec2 coord2d;"
		"uniform vec2 u_resolution;"
		"void main(void) {"
		"gl_Position = vec4(coord2d.xy / u_resolution.xy, 0.0, 1.0);"
		"}";
char const* fragment_source
	= "#version 120\n"
		"uniform float u_time;"
		"void main(void) {"
		"/* gl_FragColor[0] = abs(sin(u_time + gl_FragCoord.x));"
		"gl_FragColor[1] = abs(sin((u_time * 1.5) + gl_FragCoord.y));"
		"gl_FragColor[2] = abs(sin((u_time * 0.7) + ((gl_FragCoord.x + gl_FragCoord.y) / 2)));"
		"*/ gl_FragColor.xyz = vec3(1.0, 0.5, 0.0);"
		"}";
#endif

int main() {
	SDL::Init init;

	MappedFile vertex_source{ "vertex.glsl" };
	MappedFile fragment_source{ "fragment.glsl" };

	SDL::Window window{ "My first triangle" };
	SDL::ShaderProgram program{ vertex_source.span(), fragment_source.span() };
	Renderer renderer{ window, program };
	while (true) {
		SDL_Event event;
		while (SDL_PollEvent(&event)) {
			if (event.type == SDL_QUIT) {
				goto exit_render_loop;
			}
		}
		renderer.render();
	}
exit_render_loop:;
	return EXIT_SUCCESS;
}
