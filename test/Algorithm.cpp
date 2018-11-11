#include <BoxNesting/Algorithm.hpp>
#include <catch2/catch.hpp>

#define CATCH_CONFIG_MAIN

SCENARIO("Running the 'graph creation from a set of boxes' function")
{
	GIVEN("A set of boxes")
	{
		std::vector<BoxNesting::Box> boxes;

		boxes.emplace_back(BoxNesting::Box({0.6, 0.6, 0.6}));
		boxes.emplace_back(BoxNesting::Box({0.7, 0.7, 0.7}));
		boxes.emplace_back(BoxNesting::Box({0.8, 0.8, 0.8}));

		BoxNesting::Algorithm boxNestingAlgorithm;

		WHEN("Creating a graph from the set of boxes")
		{
			const auto graph = boxNestingAlgorithm.createGraphFromBoxes(boxes);

			THEN("There can only be edges from vertex a to b if a nests inside b")
			{
				for (const auto& list1 : graph.getAdjacencyList()) {
					for (const auto& list2 : graph.getAdjacencyList()) {
						// An edge means the box is nestable
						auto& v1 = list1.vertex;
						auto& v2 = list2.vertex;
						if (graph.isEdgeBetween(v1, v2)) {
							auto isNestable = v1.getContent().isNestable(v2.getContent())
								|| v2.getContent().isNestable(v1.getContent());

							REQUIRE(isNestable);
						}
					}
				}
			}
		}
	}
}