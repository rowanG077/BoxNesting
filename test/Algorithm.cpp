#include <box_nesting/Algorithm.hpp>
#include <catch2/catch.hpp>
#include <iostream>
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
				for (const auto& vertex : graph.getAdjacencyList()) {
					for (const auto& cVertex : graph.getAdjacencyList()) {
						// An edge means the box is nestable
						if (graph.isEdgeBetween(vertex.first, cVertex.first)) {
							REQUIRE((vertex.first.getContent().isNestable(cVertex.first.getContent())
										|| cVertex.first.getContent().isNestable(vertex.first.getContent()))
								== true);
						}
						// No edge means the box is not nestable
						else {
							REQUIRE((vertex.first.getContent().isNestable(cVertex.first.getContent())
										&& cVertex.first.getContent().isNestable(vertex.first.getContent()))
								== false);
						}
					}
				}
			}
		}
	}
}