#pragma once

#include <span>

/**
 * A RAII wrapper around a file that has been mapped by `mmap`.
 */
class MappedFile {
public:
	/**
	 * Opens the file and `mmap`s it
	 */
	MappedFile(char const* const filename);
	MappedFile(MappedFile const&) = delete;
	MappedFile(MappedFile&&) = delete;
	/**
	 * `munmap`s the file and closes it
	 */
	~MappedFile();
public:
	/**
	 * Get the file data as a `span` of `char`s
	 */
	std::span<char const> span() const {
		return std::span<char const>{ data_ptr, file_size };
	}
protected:
	char const* data_ptr;
	size_t file_size;
	int fd;
};
