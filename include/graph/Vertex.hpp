#ifndef VERTEX_HPP
#define VERTEX_HPP

#include <vector>

/**
 * @brief Contains generic code that represents a graph and its properties
 */
namespace Graph
{
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
	 * @param con the object of customizable vertex-type T that contains the
	 * vertex content
	 */
	explicit Vertex(T con);

	/**
	 * @brief comparison operator
	 *
	 * @param rhs the other vertex object it should be compared to
	 * @return true if the id's are the same
	 * @return false if the id's aren't the same
	 */
	bool operator==(const Vertex<T>& rhs) const;

	/**
	 * @brief getter for the Vertex-Type T content.
	 *
	 * @return T the information object
	 */
	[[nodiscard]] const T& getContent() const;

	/**
	 * @brief getter for the id of the vertex
	 *
	 * @return uint16_t the id
	 */
	[[nodiscard]] uint16_t getId() const;

private:
	static uint16_t idCounter;
	const uint16_t id;
	const T content;
	bool visited;
};

/**
 * @brief hash specialization for the Vertex class
 */
template<class T> struct VertexHash
{
	/**
	 * @brief function that creates a hash for a vertex
	 *
	 * @param v the vertex where the hash will be creates for
	 * @return size_t the hash
	 */
	size_t operator()(const Vertex<T>& v) const
	{
		return static_cast<size_t>(v.getId());
	}
};

} // namespace Graph

#include <graph/Vertex.ipp>

#endif // VERTEX_HPP