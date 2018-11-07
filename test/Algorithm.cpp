#include <box_nesting/Algorithm.hpp>
#include <catch2/catch.hpp>

SCENARIO("Running the 'graph creation from a set of boxes' function")
{
	GIVEN("A set of boxes")
	{
		std::vector<BoxNesting::Box> boxes;

		BoxNesting::Box a({0.6, 0.6, 0.6});
		BoxNesting::Box b({0.7, 0.7, 0.7});
		BoxNesting::Box c({0.8, 0.8, 0.8});

		boxes.emplace_back(a);
		boxes.emplace_back(b);
		boxes.emplace_back(c);

		BoxNesting::Algorithm boxNestingAlgorithm;

		WHEN("Creating a graph from the set of boxes")
		{
			auto graph = boxNestingAlgorithm.createGraphFromBoxes(boxes);

			THEN("There can only be edges from vertex a to b if a nests inside b")
			{
				for (const auto& vertex : graph.getVertices()) {
					for (const auto& cVertex : graph.getVertices()) {
						// An edge means the box is nestable
						if (graph.isEdgeBetween(vertex, cVertex)) {
							REQUIRE(vertex.getInfo().isNestable(cVertex.getInfo()) == true);
						}
						// No edge means the box is not nestable
						else {
							REQUIRE(vertex.getInfo().isNestable(cVertex.getInfo()) == false);
						}
					}
				}
			}
		}
	}
}