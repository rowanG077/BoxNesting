#include <Graph/BipartiteGraph.hpp>

#include <algorithm>
#include <exception>

namespace Graph
{
template<class T>
BipartiteGraph<T>::BipartiteGraph(std::vector<Vertex<T>> leftVertices, std::vector<Vertex<T>> rightVertices) :
	leftVertices(std::move(leftVertices)), rightVertices(std::move(rightVertices)),
	adjacencyMatrix(AdjacencyMatrix<uint8_t>(this->leftVertices.size(), this->rightVertices.size()))
{
}

template<class T> void BipartiteGraph<T>::addEdge(uint16_t v1, uint16_t v2)
{
	this->adjacencyMatrix.at(v1, v2) = true;
}

template<class T> bool BipartiteGraph<T>::isEdgeBetween(uint16_t v1, uint16_t v2) const
{
	return this->adjacencyMatrix.at(v1, v2);
}

template<class T> const AdjacencyMatrix<uint8_t>& BipartiteGraph<T>::getAdjacencyMatrix() const noexcept
{
	return this->adjacencyMatrix;
}

template<class T> const std::vector<Vertex<T>>& BipartiteGraph<T>::getLeftVertices() const noexcept
{
	return this->leftVertices;
}

template<class T> const std::vector<Vertex<T>>& BipartiteGraph<T>::getRightVertices() const noexcept
{
	return this->rightVertices;
}

} // namespace Graph