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
 *        Implemented with reference pseudocode from wikipedia:
 *        https://en.wikipedia.org/wiki/Hopcroft%E2%80%93Karp_algorithm#Pseudocode
 */
class HopcroftKarpAlgorithm
{
public:
	/**
	 * @brief Deleted default constructor
	 */
	HopcroftKarpAlgorithm() = delete;

	/**
	 * @brief Construct a new HopcroftKarpAlgorithm object
	 *
	 * @param boxes The boxes to generate the internal graph for
	 */
	explicit HopcroftKarpAlgorithm(const std::vector<Box>& boxes);

	/**
	 * @brief function that runs the boxNesting algorithm and returns the number
	 *        of visible boxes
	 *
	 * @param boxes the set of boxes to be nested
	 * @return the number of visible boxes after running the nesting
	 *         algorithm
	 */
	[[nodiscard]] int16_t runAlgorithm() const;

private:
	/**
	 * @brief We find all available shortest paths augmenting paths in the graph
	 *        
	 * @return True if any shortest augmenting path could be found. False if not 
	 */
	[[nodiscard]] bool bfs() const;

	/**
	 * @brief Use the results from bfs()
	 * (i.e. the distances traveled from a free vertex in the part of the bipartite graph)
	 * to find the shortest augmente path
	 * 
	 * @param vertex The vertex in the left partition to start dfs from
	 * @return True if the shortest augmented path was found
	 */
	[[nodiscard]] bool dfs(int16_t vertex) const;

private:
	/**
	 * @brief adjacencyList of left vertices generated from the boxes
	 *        First index on vector is a vertex on the left side of the bipartite graph
	 *        and the vector on that index contains indices of vertices on the right side of
	 *        of that are connected to the vertex on the current index.
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
	 * @brief Stores distances from left free vertex
	 */
	mutable std::vector<int16_t> distances;

	/**
	 * @brief The index of the NILL node in the left part of the bipartite graph
	 */
	static const int16_t NILL; // NOLINT, because of formatting

	/**
	 * @brief Used as marker for infinite distance
	 */
	static const int16_t INF; // NOLINT, because of formatting
};

} // namespace BoxNesting