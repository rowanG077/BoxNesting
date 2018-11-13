#pragma once

#include "BipartiteGraph.hpp"
#include "Box.hpp"

#include <cstdint>

/**
 * @brief Contains code for the boxnesting problem
 */
namespace BoxNesting
{
/**
 * @brief class that contains the boxnesting algorithm
 */
class Algorithm
{
public:
	/**
	 * @brief function that runs the boxNesting algorithm and returns the number
	 * of visible boxes
	 *
	 * @param boxes the set of boxes to be nested
	 * @return the number of visible boxes after running the nesting
	 * algorithm
	 */
	[[nodiscard]] uint16_t runAlgorithm(const std::vector<Box>& boxes) const;

	/**
	 * @brief function creates a bipartite graph from a vector of boxes
	 *        It will create two vertices for each box one in the left
	 *        and one in the right part of the graph
	 *        Then it will create edges between the left and the right part
	 *        of the graph if the box in the left vertex can nest inside
	 *        the box on the right vertex
	 *
	 * @param boxes the set of boxes that will be used to create the graph
	 *
	 * @return The constructed BipartiteGraph
	 */
	[[nodiscard]] Graph::BipartiteGraph<Box> createGraphFromBoxes(const std::vector<Box>& boxes) const;

private:
	/**
	 * @brief Run the kuhn algorithm. It's based on the DFS and will try to find
	 *        chains of maximum length.
	 *
	 * @param vertex The index of the vertex in the left part of the
	 *               Bipartite graph to start running the algorithm from
	 *
	 * @return Whether a chain could be made
	 */
	bool kuhn(uint16_t vertex) const;

private:
	/**
	 * @brief Graph generated from the boxes
	 */
	mutable Graph::BipartiteGraph<Box> graph;

	/**
	 * @brief Contains whether a vertex was allready explored during the current kuhn run
	 */
	mutable std::vector<bool> used;

	/**
	 * @brief Contains whether vertices on the right side of the bipartite graph are part
	 * 		  of a chain
	 */
	mutable std::vector<uint16_t> pairs;
};

} // namespace BoxNesting