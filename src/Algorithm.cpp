#include <algorithm>
#include <vector>

#include <BoxNesting/Algorithm.hpp>

/**
 * @brief Contains code for the boxnesting problem
 */
namespace BoxNesting
{
uint16_t Algorithm::runAlgorithm(const std::vector<Box>& boxes) const
{
	const auto graph = createGraphFromBoxes(boxes);

	// n is the amount of vertices in the left part and the right part
	// of the bipartite graph. We know this is exactly the amount of vertices
	// divided by two since we for each box we create one vertex
	// in the left part of the graph and one in the right part of the graph

	// since we know graph size doesn't exceed uint16_t we can cast here safely
	auto n = static_cast<uint16_t>(graph.getAdjacencyList().size() / 2);

	// contains indices of the vertices in right part of the graph
	// on marked edges
	std::vector<int32_t> pairs(n, -1);
	// Contains whether a vertex
	std::vector<bool> used(n, false);

	// iterate through vertices of the left side
	// of the bipartate graph
	for (uint16_t i = 0; i < n; ++i) {
		fill(used.begin(), used.end(), false);
		kuhn(graph, i, used, pairs);
	}

	return 0;
}

bool Algorithm::kuhn(
	const Graph::Graph<Box>& graph, uint16_t vertex, std::vector<bool>& used, std::vector<int32_t>& pairs) const
{
	if (used[vertex]) {
		return false;
	}
	used[vertex] = true;
	const auto& neighbours = graph.getAdjacencyList().at(vertex).edges;
	for (uint16_t i = 0; i < neighbours.size(); ++i) {
		pairs[i] = 1;
	}

	return true;
}

Graph::Graph<Box> Algorithm::createGraphFromBoxes(const std::vector<Box>& boxes) const
{
	Graph::Graph<Box> graph;

	std::vector<Graph::Vertex<Box>> leftVertices;
	std::transform(boxes.begin(), boxes.end(), std::back_inserter(leftVertices),
		[](const auto& b) { return Graph::Vertex<Box>(b); });

	std::vector<Graph::Vertex<Box>> rightVertices;
	std::transform(boxes.begin(), boxes.end(), std::back_inserter(rightVertices),
		[](const auto& b) { return Graph::Vertex<Box>(b); });

	// Add two distinct vertices to the graph for each box
	// by constructing the graph this way we know that
	// the first half of the adjacency list belongs to
	// to the left side of the bipartite graph
	// and the second half of the adjacency list belongs
	// to the right side of the bipartite graph
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