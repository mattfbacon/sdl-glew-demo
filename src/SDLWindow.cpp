#include <GL/glew.h>
#include <SDL2/SDL.h>

#include "SDLError.hpp"
#include "SDLWindow.hpp"

namespace SDL {

Window::Window(std::string const& name, Region region, Window::Flags flags) {
	window = SDL_CreateWindow(name.data(), region.x, region.y, region.w, region.h, flags | SDL_WINDOW_OPENGL);
	if (window == nullptr) {
		throw Error{ Error::Category::sdl, { .charptr = SDL_GetError() } };
	}
	gl_context = SDL_GL_CreateContext(window);
	if (gl_context == nullptr) {
		throw Error{ Error::Category::sdl, { .charptr = SDL_GetError() } };
	}
	auto const glew_status = glewInit();
	if (glew_status != GLEW_OK) {
		throw Error{ Error::Category::glew, { .uint = glew_status } };
	}
}

Window::~Window() {
	if (gl_context != nullptr) {
		SDL_GL_DeleteContext(gl_context);
		gl_context = nullptr;
	}
	if (window != nullptr) {
		SDL_DestroyWindow(window);
		window = nullptr;
	}
}

int Window::width() {
	int ret;
	SDL_GetWindowSize(window, &ret, nullptr);
	return ret;
}
int Window::height() {
	int ret;
	SDL_GetWindowSize(window, nullptr, &ret);
	return ret;
}

}  // namespace SDL
