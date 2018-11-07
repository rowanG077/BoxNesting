#include <box_nesting/Box.hpp>
#include <catch2/catch.hpp>
#include <graph/Graph.hpp>

SCENARIO(
    "A graph of boxes add edged and check if no vertex has an edge to itsself",
    "[Graph]") {
  GIVEN("A basic set of boxes") {

    Graph::Graph<BoxNesting::Box> graph;

    BoxNesting::Box a({0.6, 0.6, 0.6});
    BoxNesting::Box b({0.6, 0.6, 0.51});
    BoxNesting::Box c({0.6, 0.51, 0.6});

    graph.addVertex(a);
    graph.addVertex(b);
    graph.addVertex(c);

    WHEN("Checking is edges exist") {
      graph.addEdge(graph.getVertices()[0], graph.getVertices()[1], 5);
      graph.addEdge(graph.getVertices()[1], graph.getVertices()[0], 5);

      THEN("Existing edges indeed exist") {
        REQUIRE(graph.isEdgeBetween(graph.getVertices()[1],
                                    graph.getVertices()[0]) == true);
        REQUIRE(graph.isEdgeBetween(graph.getVertices()[0],
                                    graph.getVertices()[1]) == true);
      }

      THEN("A vertex does not have an edge to itsself") {
        REQUIRE(graph.isEdgeBetween(graph.getVertices()[0],
                                    graph.getVertices()[0]) == false);
        REQUIRE(graph.isEdgeBetween(graph.getVertices()[1],
                                    graph.getVertices()[1]) == false);
      }
    }
  }
}