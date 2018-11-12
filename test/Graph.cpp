#include <BoxNesting/Box.hpp>
#include <Graph/Graph.hpp>
#include <catch2/catch.hpp>

SCENARIO("A graph of boxes add edged and check if no vertex has an edge to itsself", "[Graph]")
{
	GIVEN("A basic set of boxes")
	{
		Graph::Graph<BoxNesting::Box> graph;

		auto a = Graph::Vertex(BoxNesting::Box({0.6f, 0.6f, 0.61f}));
		auto b = Graph::Vertex(BoxNesting::Box({0.6f, 0.6f, 0.51f}));
		auto c = Graph::Vertex(BoxNesting::Box({0.6f, 0.51f, 0.6f}));

		graph.addVertex(a);
		graph.addVertex(b);
		graph.addVertex(c);

		WHEN("Adding some edges")
		{
			graph.addEdge(a, b);
			graph.addEdge(b, c);

			THEN("Existing edges indeed exist")
			{
				REQUIRE(graph.isEdgeBetween(a, b) == true);
				REQUIRE(graph.isEdgeBetween(b, a) == true);
				REQUIRE(graph.isEdgeBetween(b, c) == true);
				REQUIRE(graph.isEdgeBetween(c, b) == true);
				REQUIRE(graph.isEdgeBetween(a, c) == false);
				REQUIRE(graph.isEdgeBetween(c, a) == false);
			}

			THEN("A vertex does not have an edge to itsself")
			{
				REQUIRE(graph.isEdgeBetween(a, a) == false);
				REQUIRE(graph.isEdgeBetween(b, b) == false);
				REQUIRE(graph.isEdgeBetween(c, c) == false);
			}
		}
	}
}