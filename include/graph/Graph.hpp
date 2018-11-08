#ifndef GRAPH_HPP
#define GRAPH_HPP

#include <graph/Edge.hpp>
#include <graph/Vertex.hpp>

#include <vector>

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
	 * @brief function that adds a new vertex of type T to the graph
	 *
	 * @param info the data the object of type T contains (the vertex type)
	 */
	void addVertex(const T& info);

	/**
	 * @brief function that adds an edge between two vertices of T to the graph
	 *
	 * @param source the source vertex of the edge
	 * @param destination the destination vertex of the edge
	 * @param weight the edge weight
	 */
	void addEdge(const Vertex<T>& source, const Vertex<T>& destination, uint64_t weight);

	/**
	 * @brief Getter for the vertices of the graph
	 *
	 * @return std::vector<Vertex<T>>& the list of vertices by reference
	 */
	[[nodiscard]] const std::vector<Vertex<T>>& getVertices() const;

	/**
	 * @brief function that checks if there is an edge between two vertices.
	 *
	 * @param source the source vertex of the edge
	 * @param destination the destination vertex of the edge
	 * @return true if there is an edge
	 * @return false if there is no edge
	 */
	bool isEdgeBetween(const Vertex<T>& source, const Vertex<T>& destination) const;
	
private:
	/**
	 * @brief the vector of vertices the graph exists out of
	 */
	std::vector<Vertex<T>> vertices;

	/**
	 * @brief counter that holds the unique id for the next vertex
	 */
	uint64_t idCounter = 0;
};

} // namespace Graph

#include <graph/Graph.ipp>

#endif // GRAPH_HPP