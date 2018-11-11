#include <BoxNesting/Box.hpp>
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
					BoxNesting::Box({minLength, minLength + 0.01, minLength + 0.01}), std::invalid_argument);
				REQUIRE_THROWS_AS(
					BoxNesting::Box({minLength + 0.01, minLength, minLength + 0.01}), std::invalid_argument);
				REQUIRE_THROWS_AS(
					BoxNesting::Box({minLength + 0.01, minLength + 0.01, minLength}), std::invalid_argument);
				REQUIRE_THROWS_AS(BoxNesting::Box({minLength, minLength, minLength}), std::invalid_argument);
			}
		}

		WHEN("constructing box with all sides between between the minimum and maximum length")
		{
			THEN("box is constructed")
			{
				REQUIRE_NOTHROW(BoxNesting::Box({maxLength - 0.01, maxLength - 0.01, maxLength - 0.01}));
				REQUIRE_NOTHROW(BoxNesting::Box({validLength, validLength, validLength}));
				REQUIRE_NOTHROW(BoxNesting::Box({validLength, validLength, minLength + 0.01}));
				REQUIRE_NOTHROW(BoxNesting::Box({validLength, minLength + 0.01, validLength}));
				REQUIRE_NOTHROW(BoxNesting::Box({minLength + 0.01, minLength + 0.01, minLength + 0.01}));
			}

			THEN("box lengths are ordered from small to large")
			{
				const auto l1 = minLength + 0.01;
				const auto l2 = minLength + 0.02;
				const auto l3 = minLength + 0.03;

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
					BoxNesting::Box({maxLength, maxLength - 0.01, maxLength - 0.01}), std::invalid_argument);
				REQUIRE_THROWS_AS(
					BoxNesting::Box({maxLength - 0.01, maxLength, maxLength - 0.01}), std::invalid_argument);
				REQUIRE_THROWS_AS(
					BoxNesting::Box({maxLength - 0.01, maxLength - 0.01, maxLength}), std::invalid_argument);
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
		BoxNesting::Box b({validLength, validLength, minLength + 0.01});
		BoxNesting::Box c({validLength, minLength + 0.01, validLength});
		BoxNesting::Box d({validLength - 0.01, validLength, validLength});
		BoxNesting::Box e({validLength - 0.01, validLength - 0.01, validLength - 0.01});
		BoxNesting::Box f({minLength + 0.01, minLength + 0.01, minLength + 0.01});

		THEN("they can nest inside eachother if their dimensions allow it")
		{
			REQUIRE(e.isNestable(a) == true);
		}

		THEN("a box cannot nest inside itself")
		{
			REQUIRE(a.isNestable(a) == false);
			REQUIRE(b.isNestable(b) == false);
			REQUIRE(c.isNestable(c) == false);
			REQUIRE(d.isNestable(d) == false);
			REQUIRE(e.isNestable(e) == false);
		}

		THEN("a larger box cannot nest inside a smaller box")
		{
			REQUIRE(e.isNestable(d) == false);
			REQUIRE(e.isNestable(c) == false);
			REQUIRE(e.isNestable(b) == false);
		}

		WHEN("a box a can nest inside a box b and box b can nest inside box c")
		{
			REQUIRE(f.isNestable(e) == true);
			REQUIRE(e.isNestable(a) == true);

			THEN("box a can nest iniside box c")
			{
				REQUIRE(f.isNestable(a) == true);
			}
		}
	}
}
