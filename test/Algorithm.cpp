#include <BoxNesting/Algorithm.hpp>
#include <catch2/catch.hpp>

#define CATCH_CONFIG_MAIN

SCENARIO("Running the 'graph creation from a set of boxes' function")
{
	GIVEN("A set of boxes")
	{
		std::vector<BoxNesting::Box> boxes{BoxNesting::Box({0.6f, 0.6f, 0.6f}), BoxNesting::Box({0.7f, 0.7f, 0.7f}),
			BoxNesting::Box({0.8f, 0.8f, 0.8f})};

		BoxNesting::Algorithm boxNestingAlgorithm;

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
}