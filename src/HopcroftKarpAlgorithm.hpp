#pragma once

#include "Box.hpp"

#include <cstdint>
#include <limits>
#include <vector>

/**
 * @brief Contains code for the boxnesting problem
 */
namespace BoxNesting
{
/**
 * @brief class that contains the boxnesting algorithm
 */
class HopcroftKarpAlgorithm
{
public:
	/**
	 * @brief Deleted default constructor
	 */
	HopcroftKarpAlgorithm() = delete;

	/**
	 * @brief Construct a new Algorithm object
	 *
	 * @param boxes The boxes to generate the internal graph for
	 */
	explicit HopcroftKarpAlgorithm(const std::vector<Box>& boxes);

	/**
	 * @brief function that runs the boxNesting algorithm and returns the number
	 * of visible boxes
	 *
	 * @param boxes the set of boxes to be nested
	 * @return the number of visible boxes after running the nesting
	 * algorithm
	 */
	[[nodiscard]] int16_t runAlgorithm() const;

private:
	bool bfs() const;
	bool dfs(int16_t vertex) const;

private:
	/**
	 * @brief adjacencyList of left vertices generated from the boxes
	 *		  First index on vector is a vertex on the left side of the bipartite graph
	 *        and the vector on that index contains indices of vertex on the right side of
	 *        of the graph where an edge exists between them.
	 */
	std::vector<std::vector<int16_t>> graph;

	/**
	 * @brief The amount of vertices in the left side of the bipartite graph
	 */
	int16_t leftVerticesCount;

	/**
	 * @brief The amount of vertices in the left side of the bipartite graph
	 */
	int16_t rightVerticesCount;

	/**
	 * @brief The index of the NILL node in the left part of the bipartite graph  
	 */
	int16_t NILL; // NOLINT

	/**
	 * @brief Used as marker for infinite distance
	 */
	int16_t INFINITE = std::numeric_limits<int16_t>::max(); // NOLINT

	/**
	 * @brief Contains whether vertices on the left side of the bipartite graph are
	 *        currently part of a match. Where the index is the vertex index and the
	 *        the value is the index of the vertex in the right side of the graph that
	 *        is matched to it. -1 indicates no match
	 */
	mutable std::vector<int16_t> pairsLeft;

	/**
	 * @brief Contains whether vertices on the right side of the bipartite graph are
	 *        currently part of a match. Where the index is the vertex index and the
	 *        the value is the index of the vertex in the left side of the graph that
	 *        is matched to it. -1 indicates no match
	 */
	mutable std::vector<int16_t> pairsRight;

	/**
	 * @brief Stores distances of left vertices
	 */
	mutable std::vector<int16_t> distances;
};

} // namespace BoxNesting