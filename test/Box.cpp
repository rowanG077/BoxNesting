#include <box_nesting/Box.hpp>
#include <catch2/catch.hpp>

SCENARIO("Box construction and valid sizes")
{
	GIVEN("a contructor for a box")
	{
		WHEN("constructing box with a side less then 0.5")
		{
			THEN("std::invalid_argument is thrown")
			{
				REQUIRE_THROWS_AS(BoxNesting::Box({0.50, 0.51, 0.51}), std::invalid_argument);
				REQUIRE_THROWS_AS(BoxNesting::Box({0.51, 0.50, 0.51}), std::invalid_argument);
				REQUIRE_THROWS_AS(BoxNesting::Box({0.51, 0.51, 0.50}), std::invalid_argument);
				REQUIRE_THROWS_AS(BoxNesting::Box({0.50, 0.50, 0.50}), std::invalid_argument);
			}
		}

		WHEN("constructing box with all sides between between 0.5 and 1.0")
		{
			THEN("box is constructed")
			{
				REQUIRE_NOTHROW(BoxNesting::Box({0.99, 0.99, 0.99}));
				REQUIRE_NOTHROW(BoxNesting::Box({0.6, 0.6, 0.6}));
				REQUIRE_NOTHROW(BoxNesting::Box({0.6, 0.6, 0.51}));
				REQUIRE_NOTHROW(BoxNesting::Box({0.6, 0.51, 0.6}));
				REQUIRE_NOTHROW(BoxNesting::Box({0.55, 0.6, 0.6}));
				REQUIRE_NOTHROW(BoxNesting::Box({0.55, 0.55, 0.55}));
				REQUIRE_NOTHROW(BoxNesting::Box({0.51, 0.51, 0.51}));
			}

			THEN("box lengths are ordered from small to large")
			{
				const BoxNesting::Box a({0.53, 0.51, 0.52});
				const BoxNesting::Box b({0.65, 0.66, 0.66});

				REQUIRE(a.getSideLengths().at(0) == Approx(0.51));
				REQUIRE(a.getSideLengths().at(1) == Approx(0.52));
				REQUIRE(a.getSideLengths().at(2) == Approx(0.53));

				REQUIRE(b.getSideLengths().at(0) == Approx(0.65));
				REQUIRE(b.getSideLengths().at(1) == Approx(0.66));
				REQUIRE(b.getSideLengths().at(2) == Approx(0.66));
			}
		}

		WHEN("constructing box with a side more then or equal 1.0")
		{
			THEN("std::invalid_argument is thrown")
			{
				REQUIRE_THROWS_AS(BoxNesting::Box({1.00, 0.99, 0.99}), std::invalid_argument);
				REQUIRE_THROWS_AS(BoxNesting::Box({0.99, 1.00, 0.99}), std::invalid_argument);
				REQUIRE_THROWS_AS(BoxNesting::Box({0.99, 0.99, 1.00}), std::invalid_argument);
				REQUIRE_THROWS_AS(BoxNesting::Box({1.00, 1.00, 1.00}), std::invalid_argument);
			}
		}
	}
}

SCENARIO("Boxes can nest inside another if their dimensions allow it", "[Box]")
{
	GIVEN("a set of boxes")
	{
		BoxNesting::Box a({0.6, 0.6, 0.6});
		BoxNesting::Box b({0.6, 0.6, 0.51});
		BoxNesting::Box c({0.6, 0.51, 0.6});
		BoxNesting::Box d({0.55, 0.6, 0.6});
		BoxNesting::Box e({0.55, 0.55, 0.55});
		BoxNesting::Box f({0.51, 0.51, 0.51});

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
