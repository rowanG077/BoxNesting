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
	 * @param newId the unique identifier of the Vertex
	 * @param con the object of customizable vertex-type T that contains the
	 * vertex content
	 */
	Vertex(uint64_t newId, T con);

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
	void addEdge(const Vertex<T>& destination, uint64_t weight);

	/**
	 * @brief getter for the Vertex-Type T content.
	 *
	 * @return T the information object
	 */
	[[nodiscard]] const T& getContent() const;

	/**
	 * @brief Getter for the adjacency list.
	 *
	 * @return const std::vector<Edge<T>>& reference to the adjacency list object
	 */
	[[nodiscard]] const std::vector<Edge<T>>& getAdjacencyList() const;

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
	[[nodiscard]] uint64_t getId() const;

private:
	uint64_t id;
	const T content;
	bool visited;
	std::vector<Edge<T>> adjacencyList;
};

} // namespace Graph

#include <graph/Vertex.ipp>

#endif // VERTEX_HPP