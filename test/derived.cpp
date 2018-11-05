#include <catch2/catch.hpp>
#include <box_nesting/derived.hpp>

#include <memory>

SCENARIO("polymorphic classes", "[derived]")
{
	GIVEN("one class that derives from an abstract base")
	{
		auto der = std::make_shared<::derived>();
		REQUIRE(der);

		WHEN("derived class is cast to base")
		{
			auto base = std::dynamic_pointer_cast<::base>(der);

			THEN("the abstract base can be used")
			{
				REQUIRE(base);
				base->init();
			}
		}
	}
}
