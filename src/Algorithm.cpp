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
	this->graph = createGraphFromBoxes(boxes);

	// n is the amount of vertices in the left part and the right part
	// of the bipartite graph. and k the amount of vertices in the right part
	// of the graph. They are the same in our box case but could be different
	// in other cases

	// since we know graph size doesn't exceed uint16_t we can cast here safely
	auto n = static_cast<uint16_t>(graph.getLeftVertices().size());
	auto k = static_cast<uint16_t>(graph.getRightVertices().size());

	this->pairs = std::vector<int32_t>(n, -1);
	this->used = std::vector<bool>(k, false);

	// iterate through vertices of the left side
	// of the bipartate graph
	for (uint16_t i = 0; i < n; ++i) {
		fill(used.begin(), used.end(), false);
		kuhn(i);
	}

	return 0;
}

bool Algorithm::kuhn(uint16_t vertex) const
{
	if (this->used[vertex]) {
		return false;
	}
	this->used[vertex] = true;
	this->pairs[vertex] = static_cast<int32_t>(graph.getLeftVertices().size());

	return true;
}

Graph::BipartiteGraph<Box> Algorithm::createGraphFromBoxes(const std::vector<Box>& boxes) const
{
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
	Graph::BipartiteGraph<Box> graph(leftVertices, rightVertices);

	// Create edges between left and right vertices if the left box can nest in
	// the right box
	const auto& lv = graph.getLeftVertices();
	const auto& rv = graph.getRightVertices();
	for (uint16_t i = 0; i < lv.size(); ++i) {
		for (uint16_t j = 0; j < rv.size(); ++j) {
			auto& v1 = lv.at(i);
			auto& v2 = rv.at(j);

			if (v1.getContent().isNestable(v2.getContent())) {
				graph.addEdge(i, j);
			}
		}
	}

	return graph;
}

} // namespace BoxNesting