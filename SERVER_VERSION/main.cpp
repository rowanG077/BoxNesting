#include "Algorithm.hpp"
#include "Parser.hpp"

#include <cstdlib>
#include <iostream>

int main(int argc, char** argv)
{	
	// Because ptr arithmatic is not allowed but we need it here
	// to access program arguments we exclude no lint here
	//std::vector<std::string> arguments(argv, argv + argc); // NOLINT

	const auto boxes = BoxNesting::Parser::getBoxes(std::cin);

	BoxNesting::Algorithm boxNestingAlgorithm;

	std::cout << boxNestingAlgorithm.runAlgorithm(boxes) << std::endl;
}
