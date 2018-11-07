#include <box_nesting/Algorithm.hpp>

/**
 * @brief Contains code for the boxnesting problem
 */
namespace BoxNesting
{
uint32_t Algorithm::runAlgorithm(const std::vector<Box>& boxes)
{
	auto graph = createGraphFromBoxes(boxes);

	// TO-DO: implementation of finding longest path (in Graph-namespace) and returning the result

	return 0;
}

Graph::Graph<Box> Algorithm::createGraphFromBoxes(const std::vector<Box>& boxes)
{
    Graph::Graph<Box> graph;

	// Set each box to be a vertex of the graph
	for (const auto& box : boxes) {
		graph.addVertex(box);
	}

	// Add a directed edge from each box-vertex that nests inside another box-vertex
	for (auto vertex = graph.getVertices().begin(); vertex != graph.getVertices().end(); ++vertex) {
		for (auto cVertex = graph.getVertices().begin(); cVertex != graph.getVertices().end(); ++cVertex) {
			if (vertex == cVertex || cVertex->hasEdgeTo(*vertex)) {
				continue;
			}
			if (vertex->getInfo().isNestable(cVertex->getInfo())) {
				graph.addEdge(*vertex, *cVertex, 1);
			}
		}
	}
    return graph;
}

} // namespace BoxNesting