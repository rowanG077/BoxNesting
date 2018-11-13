#include "Parser.hpp"

#include <cstdint>
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

	uint16_t boxCount = 0;
	static const auto max = std::numeric_limits<std::uint16_t>::max();
	try {
		auto tmp = std::stoi(inputLine);
		if (tmp <= 0 || tmp > max) {
			std::stringstream ss;
			ss << "Amount of boxes is smaller then 1 or too large max allowed: " << max << ". Got: \"" << tmp << "\"";
			throw ParserError(ss.str());
		}
		boxCount = static_cast<uint16_t>(tmp);
	} catch (const std::invalid_argument& e) {
		std::stringstream ss;
		ss << "Expected number to indicate amount of boxes to take from input. Got: \"" << inputLine << "\"";
		throw ParserError(ss.str(), e);
	} catch (const std::out_of_range& e) {
		std::stringstream ss;
		ss << "Number of boxes is too large to handle for this program, max allowed: " << max;
		throw ParserError(ss.str(), e);
	}

	auto boxes = std::vector<Box>();
	for (std::size_t i = 0; i < boxCount; ++i) {
		boxes.emplace_back(parseBoxSpecification(inputStream));
	}

	return boxes;
}

Box Parser::parseBoxSpecification(std::istream& inputStream)
{
	std::string inputLine;
	std::getline(inputStream, inputLine);

	static const std::regex boxRegex(R"(\s*(\d*.\d+)\s+(\d*.\d+)\s+(\d*.\d+))");
	std::smatch match;

	if (!std::regex_match(inputLine, match, boxRegex)) {
		std::stringstream ss;
		ss << R"(Expected a box specification in the form of "x.x y.y z.z". Got: ")" << inputLine << "\"";
		throw ParserError(ss.str());
	}

	float x = 0;
	float y = 0;
	float z = 0;

	try {
		x = std::stof(match[1].str());
		y = std::stof(match[2].str());
		z = std::stof(match[3].str());
	} catch (const std::out_of_range& e) {
		std::stringstream ss;
		ss << "x, y or z length of box is out of range of floats range, got x: " << match[1].str()
		   << ", y: " << match[2].str() << ", z: " << match[3].str();
		throw ParserError(ss.str(), e);
	}

	return Box({x, y, z});
}

} // BoxNesting