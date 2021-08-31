#pragma once

#include <GL/glew.h>
#include <SDL2/SDL.h>

#include "SDLError.hpp"

namespace SDL {

/**
 * RAII wrapper for SDL library initialization.
 * An instance must be defined somewhere in the program, ideally in `main` before anything else since the order of static initializers in separate translation units is undefined.
 */
struct Init {
	Init() {
		auto const sdl_status = SDL_Init(SDL_INIT_VIDEO);
		if (sdl_status < 0) {
			throw Error{ Error::Category::sdl, { .charptr = SDL_GetError() } };
		}
	}
	Init(Init const&) = delete;
	Init(Init&&) = delete;
	~Init() {
		SDL_Quit();
	}
};

}  // namespace SDL
