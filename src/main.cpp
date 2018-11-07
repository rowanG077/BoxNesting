#include <box_nesting/Box.hpp>
#include <box_nesting/Parser.hpp>
#include <box_nesting/version.hpp>

#include <cstdlib>
#include <iostream>

int main([[maybe_unused]] int argc, [[maybe_unused]] char** argv)
{
	const auto boxes = BoxNesting::Parser::getBoxes(std::cin);

	return EXIT_SUCCESS;
}
