#pragma once

#include <cstdint>
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
	explicit Vertex(T con) : id(++idCounter), content(std::move(con))
	{
	}

	/**
	 * @brief comparison operator
	 *
	 * @param rhs the other vertex object it should be compared to
	 * @return true if the id's are the same
	 * @return false if the id's aren't the same
	 */
	bool operator==(const Vertex<T>& rhs) const
	{
		return this->id == rhs.getId();
	}

	/**
	 * @brief getter for the Vertex-Type T content.
	 *
	 * @return T the information object
	 */
	[[nodiscard]] const T& getContent() const
	{
		return this->content;
	}

	/**
	 * @brief getter for the id of the vertex
	 *
	 * @return uint16_t the id
	 */
	[[nodiscard]] uint16_t getId() const
	{
		return this->id;
	}

private:
	/**
	 * @brief Static counter that is used to create new id
	 *        everytime a new vertex is constructed
	 */
	static uint16_t idCounter;

	/**
	 * @brief The id of the vertex
	 */
	const uint16_t id;

	/**
	 * @brief The content of the vertex
	 */
	const T content;
};

template<class T> uint16_t Vertex<T>::idCounter = 0;

} // namespace Graph
