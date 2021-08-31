#include <GL/glew.h>

#include "SDLError.hpp"

namespace SDL {
char const* Error::what() const noexcept {
	switch (category) {
		case Category::sdl:
			return error_code.charptr;
		case Category::glew:
			return reinterpret_cast<char const*>(glewGetErrorString(error_code.uint));
		default:
			__builtin_unreachable();
	}
}
}  // namespace SDL
