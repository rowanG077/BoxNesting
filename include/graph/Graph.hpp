#ifndef GRAPH_HPP
#define GRAPH_HPP

#include <graph/Vertex.hpp>

#include <unordered_map>
#include <unordered_set>

/**
 * @brief Contains generic code that represents a graph and its properties
 */
namespace Graph
{
/**
 * @brief template class representing a graph
 */
template<class T> class Graph
{
public:
	/**
	 * @brief each vertex in the adjacency list has a list of references that form the edges
	 */
	using Edges = std::unordered_set<Vertex<T>, VertexHash<T>>;
	/**
	 * @brief datatype for the adjacency list of the graph
	 */
	using VertexMap = std::unordered_map<Vertex<T>, Edges, VertexHash<T>>;

	/**
	 * @brief function that adds a vertex to the graph
	 *
	 * @param vertex the vertex to be added to the graph
	 */
	void addVertex(const Vertex<T>& vertex);

	/**
	 * @brief function that adds an edge to the graph
	 *
	 * @param v1 source of the edge
	 * @param v2 destination of the edge
	 */
	void addEdge(const Vertex<T>& v1, const Vertex<T>& v2);

	/**
	 * @brief function that checks if there is an edge between two vertices.
	 *
	 * @param source the source vertex of the edge
	 * @param destination the destination vertex of the edge
	 * @return true if there is an edge
	 * @return false if there is no edge
	 */
	bool isEdgeBetween(const Vertex<T>& source, const Vertex<T>& destination) const;

	/**
	 * @brief Getter for the adjacency list object
	 *
	 * @return const VertexMap& the adjacency list by reference
	 */
	const VertexMap& getAdjacencyList() const;

private:
	VertexMap adjacencyList;
};

} // namespace Graph

#include <graph/Graph.ipp>

#endif // GRAPH_HPP