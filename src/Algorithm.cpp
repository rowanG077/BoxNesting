#include <algorithm>

#include <box_nesting/Algorithm.hpp>

/**
 * @brief Contains code for the boxnesting problem
 */
namespace BoxNesting
{
uint64_t Algorithm::runAlgorithm(const std::vector<Box>& boxes)
{
	const auto graph = createGraphFromBoxes(boxes);

	// TO-DO: implementation of Berge's lemma

	return 0;
}

const Graph::Graph<Box> Algorithm::createGraphFromBoxes(const std::vector<Box>& boxes)
{
	Graph::Graph<Box> graph;

	std::vector<Graph::Vertex<Box>> leftVertices;
	std::transform(boxes.begin(), boxes.end(), std::back_inserter(leftVertices),
		[](const auto& b) { return Graph::Vertex<Box>(b); });

	std::vector<Graph::Vertex<Box>> rightVertices;
	std::transform(boxes.begin(), boxes.end(), std::back_inserter(rightVertices),
		[](const auto& b) { return Graph::Vertex<Box>(b); });

	// // Add a directed edge from each box-vertex that nests inside another box-vertex
	for (const auto& v1 : leftVertices) {
		graph.addVertex(v1);
		for (const auto& v2 : rightVertices) {
			graph.addVertex(v2);
			if (v1.getContent().isNestable(v2.getContent())) {
				graph.addEdge(v1, v2);
			}
		}
	}
	return graph;
}

} // namespace BoxNesting