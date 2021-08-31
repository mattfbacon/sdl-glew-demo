#include <fcntl.h>
#include <stdexcept>
#include <sys/mman.h>
#include <sys/stat.h>
#include <system_error>
#include <unistd.h>

#include "MappedFile.hpp"

MappedFile::MappedFile(char const* const filename) {
	fd = open(filename, O_RDONLY);
	if (fd == -1) {
		throw std::system_error{ errno, std::system_category() };
	}
	{
		struct stat stat;
		fstat(fd, &stat);
		file_size = stat.st_size;
	}
	data_ptr = reinterpret_cast<char*>(mmap(nullptr, file_size, PROT_READ, MAP_SHARED | MAP_FILE, fd, 0));
	if (data_ptr == MAP_FAILED) {
		throw std::system_error{ errno, std::system_category() };
	}
}

MappedFile::~MappedFile() {
	munmap(reinterpret_cast<void*>(const_cast<char*>(data_ptr)), file_size);
	data_ptr = nullptr;
	close(fd);
	fd = -1;
}
