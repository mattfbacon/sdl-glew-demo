#pragma once

#include <stdexcept>

namespace SDL {

/**
 * An error relating to SDL or GLEW.
 * Stores error codes from those libraries in their native form.
 */
struct Error : public std::exception {
	enum class Category {
		sdl,
		glew,
	} category;
	union Code {
		// for Category::glew
		unsigned int uint;
		// for Category::sdl
		// non-owning
		char const* charptr;
	} error_code;
	Error(Category category, Code error_code) : category(category), error_code(error_code) {}
	/**
	 * Returns the message.
	 * For SDL errors it returns `error_code.charptr`.
	 * For GLEW it looks up the message and returns that.
	 */
	char const* what() const noexcept override;
};

}  // namespace SDL
