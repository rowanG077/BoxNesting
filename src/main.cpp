#include "Algorithm.hpp"
#include "Parser.hpp"
#include "version.hpp"

#include <cstdlib>
#include <iostream>
#include <sstream>

void printVersion()
{
	std::cout << "program info:" << std::endl
			  << "\tname: " << BOXNESTING_NAME << std::endl
			  << "\tdescription: " << BOXNESTING_DESCRIPTION << std::endl
			  << "\tauthor: " << BOXNESTING_AUTHOR << std::endl
			  << "\tversion: " << BOXNESTING_VERSION << std::endl
			  << "\tmail: " << BOXNESTING_MAIL << std::endl
			  << "\tcopyright: " << BOXNESTING_COPYRIGHT << std::endl;
}

void printHelp(const std::string& progName)
{
	std::cout
		<< "usage: " << progName << " [options]" << std::endl
		<< "  basic user options: " << std::endl
		<< "    -h --help   \tshow this message" << std::endl
		<< "    -v --version\tshow version" << std::endl
		<< std::endl
		<< "when no options are specified program waits for input of boxes on stdin in the following format: "
		<< std::endl
		<< std::endl
		<< "<n>" << std::endl
		<< "<length of first side of first box> <length of second side of first box> "
		<< "<length of third side of first box>" << std::endl
		<< "<length of first side of second box> <length of second side of second box> "
		<< "<length of third side of second box>" << std::endl
		<< "..." << std::endl
		<< "<length of first side of nth box> <length of second side of nth box> "
		<< "<length of third side of nth box>" << std::endl
		<< std::endl
		<< "where n is positive integer and the lengths are decimal numbers between " << BoxNesting::Box::minLength
		<< " and " << BoxNesting::Box::maxLength << std::endl
		<< std::endl
		<< "Example:" << std::endl
		<< "4" << std::endl
		<< "0.9 0.9 0.9" << std::endl
		<< "0.8 0.8 0.8" << std::endl
		<< "0.7 0.7 0.7" << std::endl
		<< "0.6 0.6 0.6" << std::endl
		<< std::endl
		<< "once specifications are given program will calculate the most efficient way to stack those boxes and write "
		<< "the amount of visible boxes to stdout as a single number" << std::endl
		<< std::endl;

	printVersion();
}

int main(int argc, char** argv)
{
	// Because ptr arithmatic is not allowed but we need it here
	// to access program arguments we exclude no lint here
	std::vector<std::string> arguments(argv, argv + argc); // NOLINT

	if (arguments.size() >= 2) {
		if (arguments.at(1) == "--version" || arguments.at(1) == "-v") {
			printVersion();
		} else if (arguments.at(1) == "--help" || arguments.at(1) == "-h") {
			printHelp(arguments.at(0));
		} else {
			std::cout << "unknown options: \"" << arguments.at(1) << "\"" << std::endl << std::endl;
			printHelp(arguments.at(0));
			return EXIT_FAILURE;
		}
		return EXIT_SUCCESS;
	}

	BoxNesting::Algorithm boxNestingAlgorithm(BoxNesting::Parser::getBoxes(std::cin));

	std::cout << boxNestingAlgorithm.runAlgorithm() << std::endl;

	return EXIT_SUCCESS;
}
