#include <box_nesting/Algorithm.hpp>

/**
 * @brief Contains code for the boxnesting problem
 */
namespace BoxNesting
{
uint64_t Algorithm::runAlgorithm(const std::vector<Box>& boxes)
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
	for (auto& vertex : graph.getVertices())
	{
		for (const auto& cVertex : graph.getVertices())
		{
			if (vertex == cVertex || cVertex.hasEdgeTo(vertex)) {
				continue;
			}
			if (vertex.getContent().isNestable(cVertex.getContent())) {
				graph.addEdge(vertex, cVertex, 1);
			}
		}
	}
    return graph;
}

} // namespace BoxNesting