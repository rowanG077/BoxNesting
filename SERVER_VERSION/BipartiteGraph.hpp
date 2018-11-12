#ifndef BIPARTITEGRAPH_HPP_
#define BIPARTITEGRAPH_HPP_

#include "AdjacencyMatrix.hpp"
#include "Vertex.hpp"

#include <vector>
#include <cstdint>

/**
 * @brief Contains generic code that represents a graph and its properties
 */
namespace Graph
{
/**
 * @brief template class representing a Bipartite graph
 *
 * @tparam T The type of the value to contain in the vertices.
 */
template<class T> class BipartiteGraph
{
public:
	/**
	 * @brief Construct a new empty bipartite graph
	 */
	BipartiteGraph() = default;

	/**
	 * @brief Construct a new Bipartite Graph object from two sets of vertices
	 *
	 * @param leftVertices The left part of the bipartite graph
	 * @param rightVertices The right aprt of the bipartite graph
	 */
	BipartiteGraph(std::vector<Vertex<T>> leftVertices, std::vector<Vertex<T>> rightVertices) :
		leftVertices(std::move(leftVertices)), rightVertices(std::move(rightVertices)),
		adjacencyMatrix(AdjacencyMatrix<std::uint16_t>(this->leftVertices.size(), this->rightVertices.size()))
		{
		}

	/**
	 * @brief function that adds an edge to the graph
	 *
	 * @throw std::logic_error If v1 or v2 are vertices that are not in the graph.
	 *
	 * @param v1 source vertex index of the edge must be in the left vertices
	 * @param v2 destination vertex index of the edge must be in the right vertices
	 */
	void addEdge(std::uint16_t v1, std::uint16_t v2)
	{
		this->adjacencyMatrix.at(v1, v2) = true;
	}

	/**
	 * @brief function that checks if there is an edge between two vertices.
	 *
	 * @throw std::logic_error If v1 or v2 are vertices that are not in the graph.
	 *
	 * @param v1 the source vertex index of the edge must be in the left vertices
	 * @param v2 the destination vertex index of the edge must be in the left vertices
	 * @return true if there is an edge
	 * @return false if there is no edge
	 */
	bool isEdgeBetween(std::uint16_t v1, std::uint16_t v2) const
	{
		return this->adjacencyMatrix.at(v1, v2);
	}

	/**
	 * @brief Getter for the adjacency list object
	 *
	 * @return The adjacency list by reference
	 */
	const AdjacencyMatrix<std::uint16_t>& getAdjacencyMatrix() const
	{
		return this->getAdjacencyMatrix;
	}

	/**
	 * @brief Get the left Vertices of the bipartite graph
	 *
	 * @return The left vertices of the bipartite graph
	 */
	const std::vector<Vertex<T>>& getLeftVertices() const
	{
		return this->leftVertices;
	}

	/**
	 * @brief Get the rigt Vertices of the bipartite graph
	 *
	 * @return The right vertices of the bipartite graph
	 */
	const std::vector<Vertex<T>>& getRightVertices() const
	{
		return this->rightVertices;
	}

private:
	/**
	 * @brief Contains the left vertices of the graph
	 */
	std::vector<Vertex<T>> leftVertices;

	/**
	 * @brief Contains the rights vertices of the graph
	 */
	std::vector<Vertex<T>> rightVertices;

	/**
	 * @brief Contains the edges between the left and right vertices
	 *        The vector specialization of bool is broken so we use uint16_t instead of bool
	 */
	AdjacencyMatrix<std::uint16_t> adjacencyMatrix;
};

} // namespace Graph

#endif