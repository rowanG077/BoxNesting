#include <BoxNesting/Algorithm.hpp>
#include <catch2/catch.hpp>

#define CATCH_CONFIG_MAIN

SCENARIO("Running the 'graph creation from a set of boxes' function")
{
	BoxNesting::Algorithm boxNestingAlgorithm;

	GIVEN("A set of boxes")
	{
		std::vector<BoxNesting::Box> boxes{BoxNesting::Box({0.6f, 0.6f, 0.6f}), BoxNesting::Box({0.7f, 0.7f, 0.7f}),
			BoxNesting::Box({0.8f, 0.8f, 0.8f})};

		WHEN("Creating a graph from the set of boxes")
		{
			const auto graph = boxNestingAlgorithm.createGraphFromBoxes(boxes);

			THEN("There can only be edges from vertex a to b if a nests inside b")
			{
				const auto& lv = graph.getLeftVertices();
				const auto& rv = graph.getRightVertices();
				for (uint16_t i = 0; i < lv.size(); ++i) {
					for (uint16_t j = 0; j < rv.size(); ++j) {
						if (graph.isEdgeBetween(i, j)) {
							auto& v1 = lv.at(i);
							auto& v2 = rv.at(j);

							auto isNestable = v1.getContent().isNestable(v2.getContent())
								|| v2.getContent().isNestable(v1.getContent());

							REQUIRE(isNestable);
						}
					}
				}
			}
		}
	}

	GIVEN("A set of boxes where every box except for one can nest inside another")
	{
		std::vector<BoxNesting::Box> boxes{BoxNesting::Box({0.9f, 0.9f, 0.9f}), BoxNesting::Box({0.8f, 0.8f, 0.8f}),
			BoxNesting::Box({0.7f, 0.7f, 0.7f}), BoxNesting::Box({0.6f, 0.6f, 0.6f})};

		THEN("Only one visible box remains after nesting")
		{
			auto result = boxNestingAlgorithm.runAlgorithm(boxes);
			REQUIRE(result == 1);
		}
	}

	GIVEN("A set of boxes where only one box can nest inside another")
	{
		std::vector<BoxNesting::Box> boxes1{BoxNesting::Box({0.6f, 0.6f, 0.6f}), BoxNesting::Box({0.75f, 0.75f, 0.75f}),
			BoxNesting::Box({0.9f, 0.7f, 0.7f})};

		std::vector<BoxNesting::Box> boxes2{BoxNesting::Box({0.75f, 0.75f, 0.75f}),
			BoxNesting::Box({0.80f, 0.70f, 0.74f}), BoxNesting::Box({0.73f, 0.65f, 0.85f}),
			BoxNesting::Box({0.60f, 0.90f, 0.72f}), BoxNesting::Box({0.95f, 0.55f, 0.71f}),
			BoxNesting::Box({0.52f, 0.98f, 0.70f}), BoxNesting::Box({0.70f, 0.75f, 0.69f})};

		THEN("One less box is visible after nesting")
		{
			auto result1 = boxNestingAlgorithm.runAlgorithm(boxes1);
			REQUIRE(result1 == (boxes1.size() - 1));
			auto result2 = boxNestingAlgorithm.runAlgorithm(boxes2);
			REQUIRE(result2 == (boxes2.size() - 1));
		}
	}

	GIVEN("A set of 5000 boxes which can all nest eachother except for one")
	{
		std::vector<BoxNesting::Box> boxes;
		for (uint16_t i = 0; i < 5000; ++i) {
			auto length = 0.50001f + (0.00009f * i);
			boxes.emplace_back(BoxNesting::Box({length, length, length}));
		}

		THEN("Only one visible box remains after nesting")
		{
			auto result = boxNestingAlgorithm.runAlgorithm(boxes);
			REQUIRE(result == 1);
		}
	}

	GIVEN("A set of 5000 boxes where none can nest inside eachother")
	{
		std::vector<BoxNesting::Box> boxes;
		for (uint16_t i = 0; i < 5000; ++i) {
			auto length = 0.50001f;
			boxes.emplace_back(BoxNesting::Box({length, length, length}));
		}

		THEN("Only one visible box remains after nesting")
		{
			auto result = boxNestingAlgorithm.runAlgorithm(boxes);
			REQUIRE(result == boxes.size());
		}
	}
}