#ifndef VERTEX_HPP
#define VERTEX_HPP

#include <memory>
#include <utility>
#include <vector>

/**
 * @brief Contains generic code that represents a graph and its properties
 */
namespace Graph
{
template<class T> class Edge;

/**
 * @brief template class representation of a vertex of type T
 */
template<class T> class Vertex
{
public:
	/**
	 * @brief Explicit deletion of default constructor.
	 */
	Vertex() = delete;

	/**
	 * @brief Construct a new Vertex object.
	 *
	 * @param info the object of customizable vertex-type T that contains the
	 * vertex information
	 */
	Vertex(uint64_t newId, T info);

	/**
	 * @brief comparison operator
	 *
	 * @param rhs the other vertex object it should be compared to
	 * @return true if the id's are the same
	 * @return false if the id's aren't the same
	 */
	bool operator==(const Vertex<T>& rhs) const;

	/**
	 * @brief function that adds a directed edge to another vertex.
	 *
	 * @param destination reference to the destination vertex
	 * @param weight the edge weight
	 */
	void addEdge(const Vertex<T>& destination, double weight);

	/**
	 * @brief getter for the Vertex-Type T information.
	 *
	 * @return T the information object
	 */
	T getInfo() const;

	/**
	 * @brief Getter for the adjacency list.
	 *
	 * @return const std::vector<Edge<T>>& reference to the adjacency list object
	 */
	const std::vector<Edge<T>>& getAdjacencyList() const;

	/**
	 * @brief function that checks if a vertex has an edge to a specific vertex.
	 *
	 * @param destination the destination vertex
	 * @return true if the vertex has indeed an edge to the destination vertex
	 * @return false if there is no edge to the destination vertex
	 */
	bool hasEdgeTo(const Vertex<T>& destination) const;

	/**
	 * @brief getter for the id of the vertex
	 *
	 * @return uint64_t the id
	 */
	uint64_t getId() const;

private:
	uint64_t id;
	T information;
	bool visited;
	std::vector<Edge<T>> adjacencyList;
};

} // namespace Graph

#include <graph/Vertex.ipp>

#endif // VERTEX_HPP