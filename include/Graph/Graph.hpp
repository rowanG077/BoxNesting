#pragma once

#include <Graph/Vertex.hpp>

#include <unordered_map>
#include <unordered_set>

/**
 * @brief Contains generic code that represents a graph and its properties
 */
namespace Graph
{
/**
 * @brief Data structure to represent AdjacencyList of the graph
 *
 * @tparam T The type of the value to contain in the vertices.
 */
template<class T> struct AdjacencyList
{
	/**
	 * @brief The vertex for this adjacencyList
	 */
	Vertex<T> vertex;

	/**
	 * @brief The vertices the head vertex can travel to via an edge.
	 */
	std::vector<std::uint16_t> edges;
};

/**
 * @brief template class representing a graph
 *
 * @tparam T The type of the value to contain in the vertices.
 */
template<class T> class Graph
{
public:
	/**
	 * @brief function that adds a vertex to the graph
	 *
	 * @param vertex the vertex to be added to the graph
	 */
	void addVertex(const Vertex<T>& vertex);

	/**
	 * @brief function that adds an edge to the graph
	 *
	 * @throw std::logic_error If v1 or v2 are vertices that are not in the graph.
	 *
	 * @param v1 source of the edge
	 * @param v2 destination of the edge
	 */
	void addEdge(const Vertex<T>& v1, const Vertex<T>& v2);

	/**
	 * @brief function that checks if there is an edge between two vertices.
	 *
	 * @throw std::logic_error If v1 or v2 are vertices that are not in the graph.
	 *
	 * @param v1 the source vertex of the edge
	 * @param v2 the destination vertex of the edge
	 * @return true if there is an edge
	 * @return false if there is no edge
	 */
	bool isEdgeBetween(const Vertex<T>& v1, const Vertex<T>& v2) const;

	/**
	 * @brief Getter for the adjacency list object
	 *
	 * @return The e adjacency list by reference
	 */
	const std::vector<AdjacencyList<T>>& getAdjacencyList() const noexcept;

private:
	std::vector<AdjacencyList<T>> adjacencyList;
};

} // namespace Graph

#include <Graph/Graph.ipp>
