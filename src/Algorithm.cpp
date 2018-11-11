#include <algorithm>

#include <box_nesting/Algorithm.hpp>

/**
 * @brief Contains code for the boxnesting problem
 */
namespace BoxNesting
{
uint16_t Algorithm::runAlgorithm(const std::vector<Box>& boxes)
{
	const auto graph = createGraphFromBoxes(boxes);

	// TO-DO: implementation of Berge's lemma

	return 0;
}

Graph::Graph<Box> Algorithm::createGraphFromBoxes(const std::vector<Box>& boxes)
{
	Graph::Graph<Box> graph;

	std::vector<Graph::Vertex<Box>> leftVertices;
	std::transform(boxes.begin(), boxes.end(), std::back_inserter(leftVertices),
		[](const auto& b) { return Graph::Vertex<Box>(b); });

	std::vector<Graph::Vertex<Box>> rightVertices;
	std::transform(boxes.begin(), boxes.end(), std::back_inserter(rightVertices),
		[](const auto& b) { return Graph::Vertex<Box>(b); });

	// Add two distinct vertices to the graph for each box
	for (const auto& v : leftVertices) {
		graph.addVertex(v);
	}

	for (const auto& v : rightVertices) {
		graph.addVertex(v);
	}

	// Create edges between left and right vertices if the left box can nest in
	// the right box
	for (const auto& v1 : leftVertices) {
		for (const auto& v2 : rightVertices) {
			if (v1.getContent().isNestable(v2.getContent())) {
				graph.addEdge(v1, v2);
			}
		}
	}

	return graph;
}

} // namespace BoxNesting