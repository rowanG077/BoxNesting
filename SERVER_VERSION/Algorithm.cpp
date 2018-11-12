#include <algorithm>
#include <vector>

#include "Algorithm.hpp"

/**
 * @brief Contains code for the boxnesting problem
 */
namespace BoxNesting
{
std::uint16_t Algorithm::runAlgorithm(const std::vector<Box>& boxes) const
{
	this->graph = createGraphFromBoxes(boxes);

	// n is the amount of vertices in the left part of the bipartite graph
	// k the amount of vertices in the right part of the bipartite graph
	// They are the same in our boxes case but could be different
	// in other cases

	// since we know graph size doesn't exceed std::uint16_t we can cast here safely
	auto n = static_cast<std::uint16_t>(graph.getLeftVertices().size());
	auto k = static_cast<std::uint16_t>(graph.getRightVertices().size());

	// We use 0 for no pair and the index of the vertex + 1 for found pair
	this->pairs = std::vector<std::uint16_t>(n, 0);
	this->used = std::vector<bool>(k, false);

	// iterate through vertices of the left side
	// of the bipartate graph
	for (std::uint16_t i = 0; i < n; ++i) {
		fill(used.begin(), used.end(), false);
		kuhn(i);
	}

	std::uint16_t matches = 0;
	for (std::uint16_t i = 0; i < k; ++i) {
		if (pairs[i] != 0) {
			++matches;
		}
	}

	// amount of visible boxes is the total amount of boxes
	// minus the matches. Since a match means a box can nest inside another box
	return static_cast<std::uint16_t>(boxes.size() - matches);
}

bool Algorithm::kuhn(std::uint16_t vertex) const
{
	if (this->used[vertex]) {
		return false;
	}
	this->used[vertex] = true;

	auto sz = this->graph.getRightVertices().size();
	for (std::uint16_t i = 0; i < sz; ++i) {
		if (!this->graph.isEdgeBetween(vertex, i)) {
			continue;
		}
		// Correct for the NILL value by removing/adding one to convert to vertex index
		if (pairs[i] == 0 || kuhn(static_cast<std::uint16_t>(pairs[i] - 1))) {
			pairs[i] = static_cast<std::uint16_t>(vertex + 1);
			return true;
		}
	}
	return false;
}

Graph::BipartiteGraph<Box> Algorithm::createGraphFromBoxes(const std::vector<Box>& boxes) const
{
	std::vector<Graph::Vertex<Box>> leftVertices;
	std::transform(boxes.begin(), boxes.end(), std::back_inserter(leftVertices),
		[](const Box& b) { return Graph::Vertex<Box>(b); });

	std::vector<Graph::Vertex<Box>> rightVertices;
	std::transform(boxes.begin(), boxes.end(), std::back_inserter(rightVertices),
		[](const Box& b) { return Graph::Vertex<Box>(b); });

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
	for (std::uint16_t i = 0; i < lv.size(); ++i) {
		for (std::uint16_t j = 0; j < rv.size(); ++j) {
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