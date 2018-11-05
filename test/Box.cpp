#include <box_nesting/Box.hpp>
#include <catch2/catch.hpp>

#include <memory>

SCENARIO("Boxes can nest inside another if their dimensions allow it", "[Box]")
{
	GIVEN("a set of boxes")
	{
		BoxNesting::Box a(0.6, 0.6, 0.6);
		BoxNesting::Box b(0.6, 0.6, 0.5);
		BoxNesting::Box c(0.6, 0.5, 0.6);
		BoxNesting::Box d(0.5, 0.6, 0.6);
		BoxNesting::Box e(0.5, 0.5, 0.5);
		BoxNesting::Box f(0.4, 0.4, 0.4);

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
