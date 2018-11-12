#pragma once

#include <exception>
#include <vector>

/**
 * @brief Contains generic code that represents a graph and its properties
 */
namespace Graph
{
/**
 * @brief Class that can be used to store a 2d array continously in memory
 *
 * @tparam T The type to store in the array
 */
template<class T> class AdjacencyMatrix
{
public:
	/**
	 * @brief Construct a new empty AdjacencyMatrix object
	 */
	AdjacencyMatrix() : data(0)
	{
	}

	/**
	 * @brief Construct a new AdjacencyMatrix object
	 *
	 * @param l The amount of left vertices
	 * @param r The amount of right vertices
	 */
	AdjacencyMatrix(size_t l, size_t r) : data(l * r), leftCount(l), rightCount(r)
    {
    }

    /**
     * @brief Get element at specified indices
     *
     * @param l The left vertex index
     * @param r The right vertex index
     *
     * @throws std::out_of_range if index is out of range
     *
     * @return Value at that index
     */
    [[nodiscard]] T& at(size_t l, size_t r)
	{
		return this->data.at(l * this->rightCount + r);
	}

	/**
	 * @brief Get const element at specified indices
	 *
	 * @param l The left vertex index
	 * @param r The right vertex index
	 *
	 * @throws std::out_of_range if index is out of range
	 *
	 * @return Const value at that index
	 */
	[[nodiscard]] const T& at(size_t l, size_t r) const { return this->data.at(l * this->rightCount + r); }

	private:
    /**
     * @brief Contains the data of the adjacencyMatrix
     */
    std::vector<T> data;

	/**
	 * @brief Contains the amount of left vertices
	 */
	size_t leftCount = 0;

	/**
	 * @brief Contains the amount of right vertices
	 */
	size_t rightCount = 0;
};

} // namespace Graph
