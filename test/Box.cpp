#include <Box.hpp>
#include <catch2/catch.hpp>

SCENARIO("Box construction and valid side lengths")
{
	const auto minLength = BoxNesting::Box::minLength;
	const auto maxLength = BoxNesting::Box::maxLength;
	const auto validLength = (minLength + maxLength) / 2;

	GIVEN("a contructor for a box")
	{
		WHEN("constructing box with a side less then or equal to the minimum length")
		{
			THEN("std::invalid_argument is thrown")
			{
				REQUIRE_THROWS_AS(
					BoxNesting::Box({minLength, minLength + 0.01f, minLength + 0.01f}), std::invalid_argument);
				REQUIRE_THROWS_AS(
					BoxNesting::Box({minLength + 0.01f, minLength, minLength + 0.01f}), std::invalid_argument);
				REQUIRE_THROWS_AS(
					BoxNesting::Box({minLength + 0.01f, minLength + 0.01f, minLength}), std::invalid_argument);
				REQUIRE_THROWS_AS(BoxNesting::Box({minLength, minLength, minLength}), std::invalid_argument);
			}
		}

		WHEN("constructing box with all sides between between the minimum and maximum length")
		{
			THEN("box is constructed")
			{
				REQUIRE_NOTHROW(BoxNesting::Box({maxLength - 0.01f, maxLength - 0.01f, maxLength - 0.01f}));
				REQUIRE_NOTHROW(BoxNesting::Box({validLength, validLength, validLength}));
				REQUIRE_NOTHROW(BoxNesting::Box({validLength, validLength, minLength + 0.01f}));
				REQUIRE_NOTHROW(BoxNesting::Box({validLength, minLength + 0.01f, validLength}));
				REQUIRE_NOTHROW(BoxNesting::Box({minLength + 0.01f, minLength + 0.01f, minLength + 0.01f}));
			}

			THEN("box lengths are ordered from small to large")
			{
				const auto l1 = minLength + 0.01f;
				const auto l2 = minLength + 0.02f;
				const auto l3 = minLength + 0.03f;

				const BoxNesting::Box a({l1, l2, l3});
				const BoxNesting::Box b({l2, l3, l1});

				REQUIRE(a.getSideLengths().at(0) == Approx(l1));
				REQUIRE(a.getSideLengths().at(1) == Approx(l2));
				REQUIRE(a.getSideLengths().at(2) == Approx(l3));

				REQUIRE(b.getSideLengths().at(0) == Approx(l1));
				REQUIRE(b.getSideLengths().at(1) == Approx(l2));
				REQUIRE(b.getSideLengths().at(2) == Approx(l3));
			}
		}

		WHEN("constructing box with a side more then or equal to the maximum length")
		{
			THEN("std::invalid_argument is thrown")
			{
				REQUIRE_THROWS_AS(
					BoxNesting::Box({maxLength, maxLength - 0.01f, maxLength - 0.01f}), std::invalid_argument);
				REQUIRE_THROWS_AS(
					BoxNesting::Box({maxLength - 0.01f, maxLength, maxLength - 0.01f}), std::invalid_argument);
				REQUIRE_THROWS_AS(
					BoxNesting::Box({maxLength - 0.01f, maxLength - 0.01f, maxLength}), std::invalid_argument);
				REQUIRE_THROWS_AS(BoxNesting::Box({maxLength, maxLength, maxLength}), std::invalid_argument);
			}
		}
	}
}

SCENARIO("Boxes can nest inside another if their dimensions allow it", "[Box]")
{
	const auto minLength = BoxNesting::Box::minLength;
	const auto maxLength = BoxNesting::Box::maxLength;
	const auto validLength = (minLength + maxLength) / 2;

	GIVEN("a set of boxes")
	{
		BoxNesting::Box a({validLength, validLength, validLength});
		BoxNesting::Box b({validLength, validLength, minLength + 0.01f});
		BoxNesting::Box c({validLength, minLength + 0.01f, validLength});
		BoxNesting::Box d({validLength - 0.01f, validLength, validLength});
		BoxNesting::Box e({validLength - 0.01f, validLength - 0.01f, validLength - 0.01f});
		BoxNesting::Box f({minLength + 0.01f, minLength + 0.01f, minLength + 0.01f});

		THEN("they can nest inside eachother if their dimensions allow it")
		{
			REQUIRE((e < a) == true);
		}

		THEN("a box cannot nest inside itself")
		{
			REQUIRE((a < a) == false);
			REQUIRE((b < b) == false);
			REQUIRE((c < c) == false);
			REQUIRE((d < d) == false);
			REQUIRE((e < e) == false);
		}

		THEN("a larger box cannot nest inside a smaller box")
		{
			REQUIRE((e < d) == false);
			REQUIRE((e < c) == false);
			REQUIRE((e < b) == false);
		}

		WHEN("a box a can nest inside a box b and box b can nest inside box c")
		{
			REQUIRE((f < e) == true);
			REQUIRE((e < a) == true);

			THEN("box a can nest iniside box c")
			{
				REQUIRE((f < a) == true);
			}
		}
	}
}
