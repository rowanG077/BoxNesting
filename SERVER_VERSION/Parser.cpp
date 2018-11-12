#include "Parser.hpp"

#include <limits>
#include <regex>
#include <sstream>
#include <string>

namespace BoxNesting
{
std::vector<Box> Parser::getBoxes(std::istream& inputStream)
{
	std::string inputLine;
	std::getline(inputStream, inputLine);

	std::uint16_t boxCount = 0;

	auto tmp = std::stoi(inputLine);
	boxCount = static_cast<std::uint16_t>(tmp);

	auto boxes = std::vector<Box>();
	for (std::size_t i = 0; i < boxCount; ++i) {
		boxes.emplace_back(parseBoxSpecification(inputStream));
	}
	return boxes;
}

Box Parser::parseBoxSpecification(std::istream& inputStream)
{
	float x = 0;
	float y = 0;
	float z = 0;

	inputStream >> x;
	inputStream >> y;
	inputStream >> z;

	return Box({x, y, z});
}

} // BoxNesting