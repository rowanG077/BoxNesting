#include <box_nesting/Parser.hpp>
#include <catch2/catch.hpp>

#include <sstream>

SCENARIO("Parsing box specifcations from inputStream")
{
	GIVEN("an input stream")
	{
		WHEN("parsing 5 correct specification")
		{
			std::stringstream stream;
			stream << "5\n"
				<< "0.52 0.53 0.51\n"
				<< "0.62 0.63 0.61\n"
				<< "0.72 0.73 0.71\n"
				<< "0.82 0.83 0.81\n"
				<< "0.92 0.93 0.91\n";

			const auto boxes = BoxNesting::Parser::getBoxes(stream);

			THEN("5 boxes are obtained with correct ordered lengths")
			{
				REQUIRE(boxes.size() == 5);
				for (std::size_t i = 0; i < boxes.size(); ++i)
				{
					const auto& l = boxes.at(i).getSideLengths();
					auto offset = static_cast<double>(i) * 0.10;
					REQUIRE(l.at(0) == Approx(0.51 + offset));
					REQUIRE(l.at(1) == Approx(0.52 + offset));
					REQUIRE(l.at(2) == Approx(0.53 + offset));
				}
			}
		}

		WHEN("parsing the first line and negative number is present")
		{
			std::stringstream stream;
			stream << "-1\n";
			THEN("a ParserError is thrown")
			{
				REQUIRE_THROWS_AS(BoxNesting::Parser::getBoxes(stream), BoxNesting::ParserError);
			}
		}

		WHEN("parsing the first line and a very very large number is present")
		{
			std::stringstream stream;
			stream << "99999999999999999999999999999999999999\n";
			THEN("a ParserError is thrown")
			{
				REQUIRE_THROWS_AS(BoxNesting::Parser::getBoxes(stream), BoxNesting::ParserError);
			}
		}

		WHEN("parsing a specification which is not within 0.5 - 1 side length range")
		{
			std::stringstream stream;
			stream << "1\n"
				<< "0.50 0.51 0.51\n";
			
			THEN("a std::invalid_argument is thrown")
			{
				REQUIRE_THROWS_AS(BoxNesting::Parser::getBoxes(stream), std::invalid_argument);
			}
		}

		WHEN("parsing a specification which is not of the correct format")
		{
			std::stringstream stream;
			stream << "1\n"
				<< "0.50 0.51 dsd\n";
			
			THEN("a ParserError is thrown")
			{
				REQUIRE_THROWS_AS(BoxNesting::Parser::getBoxes(stream), BoxNesting::ParserError);
			}
		}

	}
}
