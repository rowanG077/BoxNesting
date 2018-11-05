#include <box_nesting/Box.hpp>
#include <box_nesting/version.hpp>

#include <cstdlib>
#include <iostream>

int main(int argc, char** argv)
{
	std::cout << "argc: " << argc << '\n';
	for (int i = 0; i < argc; ++i) {
		std::cout << "argv[" << i << "]: ";
		// clang-tidy: avoid pointer arithmetic in c++
		std::cout << argv[i]; // NOLINT
		std::cout << '\n';
	}

	std::cout << std::flush;

	std::cout << "project info:\n"
			  << "\tname: " << BOX_NESTING_NAME << '\n'
			  << "\tdesc: " << BOX_NESTING_DESCRIPTION << '\n'
			  << "\tauthor: " << BOX_NESTING_AUTHOR << '\n'
			  << "\tversion: " << BOX_NESTING_VERSION << '\n'
			  << "\tmail: " << BOX_NESTING_MAIL << '\n'
			  << "\tcopyright: " << BOX_NESTING_COPYRIGHT << std::endl;

	return EXIT_SUCCESS;
}
