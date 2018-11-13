#include <BipartiteGraph.hpp>
#include <Box.hpp>
#include <catch2/catch.hpp>

SCENARIO("A graph of boxes add edged and check if no vertex has an edge to itsself", "[Graph]")
{
	GIVEN("A basic set of boxes")
	{
		std::vector<Graph::Vertex<BoxNesting::Box>> leftVertices{
			Graph::Vertex<BoxNesting::Box>(BoxNesting::Box({0.6f, 0.6f, 0.61f})),
			Graph::Vertex<BoxNesting::Box>(BoxNesting::Box({0.6f, 0.6f, 0.51f})),
			Graph::Vertex<BoxNesting::Box>(BoxNesting::Box({0.6f, 0.51f, 0.6f}))};

		std::vector<Graph::Vertex<BoxNesting::Box>> rightVertices{
			Graph::Vertex<BoxNesting::Box>(BoxNesting::Box({0.6f, 0.6f, 0.61f})),
			Graph::Vertex<BoxNesting::Box>(BoxNesting::Box({0.6f, 0.6f, 0.51f})),
			Graph::Vertex<BoxNesting::Box>(BoxNesting::Box({0.6f, 0.51f, 0.6f}))};

		Graph::BipartiteGraph<BoxNesting::Box> graph(leftVertices, rightVertices);

		WHEN("Adding some edges")
		{
			graph.addEdge(0, 1);
			graph.addEdge(1, 2);

			THEN("Existing edges indeed exist")
			{
				REQUIRE(graph.isEdgeBetween(0, 1) == true);
				REQUIRE(graph.isEdgeBetween(1, 2) == true);
				REQUIRE(graph.isEdgeBetween(0, 2) == false);
				REQUIRE(graph.isEdgeBetween(2, 0) == false);
			}

			THEN("A vertex does not have an edge to itself")
			{
				REQUIRE(graph.isEdgeBetween(0, 0) == false);
				REQUIRE(graph.isEdgeBetween(1, 1) == false);
				REQUIRE(graph.isEdgeBetween(1, 1) == false);
			}
		}
	}
}