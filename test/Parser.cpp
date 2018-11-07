#include <box_nesting/Parser.hpp>
#include <catch2/catch.hpp>

#include <sstream>

SCENARIO("Parsing box specifcations from inputStream")
{
	const auto minLength = BoxNesting::Box::minLength;
	const auto maxLength = BoxNesting::Box::maxLength;
	const auto validLength = (minLength + maxLength) / 2;

	GIVEN("an input stream")
	{
		WHEN("parsing 5 correct specification")
		{
			std::stringstream stream;
			stream << "5" << std::endl
				   << (minLength + 0.01) << " " << (minLength + 0.02) << " " << (minLength + 0.03) << std::endl
				   << (minLength + 0.04) << " " << (minLength + 0.05) << " " << (minLength + 0.06) << std::endl
				   << (minLength + 0.07) << " " << (minLength + 0.08) << " " << (minLength + 0.09) << std::endl
				   << (minLength + 0.10) << " " << (minLength + 0.11) << " " << (minLength + 0.12) << std::endl
				   << (minLength + 0.13) << " " << (minLength + 0.14) << " " << (minLength + 0.15) << std::endl;

			const auto boxes = BoxNesting::Parser::getBoxes(stream);

			THEN("5 boxes are obtained with correct ordered lengths")
			{
				REQUIRE(boxes.size() == 5);
				for (std::size_t i = 0; i < boxes.size(); ++i) {
					const auto& l = boxes.at(i).getSideLengths();
					auto offset = static_cast<double>(i) * 0.03;
					REQUIRE(l.at(0) == Approx(minLength + offset + 0.01));
					REQUIRE(l.at(1) == Approx(minLength + offset + 0.02));
					REQUIRE(l.at(2) == Approx(minLength + offset + 0.03));
				}
			}
		}

		WHEN("parsing the first line and negative number is present")
		{
			std::stringstream stream;
			stream << "-1" << std::endl;
			THEN("a ParserError is thrown")
			{
				REQUIRE_THROWS_AS(BoxNesting::Parser::getBoxes(stream), BoxNesting::ParserError);
			}
		}

		WHEN("parsing the first line and a very very large number is present")
		{
			std::stringstream stream;
			stream << "99999999999999999999999999999999999999" << std::endl;
			THEN("a ParserError is thrown")
			{
				REQUIRE_THROWS_AS(BoxNesting::Parser::getBoxes(stream), BoxNesting::ParserError);
			}
		}

		WHEN("parsing a specification which is not within allowed side length range")
		{
			std::stringstream stream;
			stream << "1" << std::endl << minLength << " " << validLength << " " << validLength << std::endl;

			THEN("a std::invalid_argument is thrown")
			{
				REQUIRE_THROWS_AS(BoxNesting::Parser::getBoxes(stream), std::invalid_argument);
			}
		}

		WHEN("parsing a specification which is not of the correct format")
		{
			std::stringstream stream;
			stream << "1" << std::endl << "foobar " << validLength << " " << validLength << std::endl;

			THEN("a ParserError is thrown")
			{
				REQUIRE_THROWS_AS(BoxNesting::Parser::getBoxes(stream), BoxNesting::ParserError);
			}
		}
	}
}
