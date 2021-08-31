#pragma once

#include <SDL2/SDL.h>
#include <string>

#include "Region.hpp"

namespace SDL {

/**
 * An RAII wrapper around an SDL Window.
 */
class Window {
public:
	using Flags = uint32_t;
public:
	Window(std::string const& name, Region region = { SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, 640, 480 }, Flags flags = SDL_WINDOW_RESIZABLE | SDL_WINDOW_ALLOW_HIGHDPI);
	Window(Window const&) = delete;
	Window(Window&&) = default;
	~Window();
	/**
	 * Swap the buffers in the window
	 */
	void swap() {
		SDL_GL_SwapWindow(window);
	}
	/**
	 * Get the width of the window.
	 */
	int width();
	/**
	 * Get the height of the window.
	 */
	int height();
protected:
	SDL_Window* window = nullptr;
	SDL_GLContext gl_context = nullptr;
};

}  // namespace SDL
