#include <Graph/Graph.hpp>

#include <algorithm>
#include <exception>

namespace Graph
{

template <class T>
void Graph<T>::addVertex(const Vertex<T>& vertex) 
{
	this->adjacencyList.emplace_back(AdjacencyList<T>{vertex, std::vector<std::uint16_t>()});
}

template <class T>
void Graph<T>::addEdge(const Vertex<T>& v1, const Vertex<T>& v2)
{
	auto e1 = std::find_if(this->adjacencyList.begin(), this->adjacencyList.end(),
			[&](const AdjacencyList<T>& e) { return e.vertex == v1; });
	auto e2 = std::find_if(this->adjacencyList.begin(), this->adjacencyList.end(),
			[&](const AdjacencyList<T>& e) { return e.vertex == v2; });
	
	if (e1 == this->adjacencyList.end()) {
		throw std::logic_error("addEdge, v1 vertex does not exist in adjacency list of graph.");
	}
	if (e2 == this->adjacencyList.end()) {
		throw std::logic_error("addEdge, v2 vertex does not exist in adjacency list of graph.");
	}

	e1->edges.emplace_back(e2 - this->adjacencyList.begin());
	e2->edges.emplace_back(e1 - this->adjacencyList.begin());
}

template <class T>
bool Graph<T>::isEdgeBetween(const Vertex<T> &v1, const Vertex<T> &v2) const
{
	auto e1 = std::find_if(this->adjacencyList.begin(), this->adjacencyList.end(),
			[&](const AdjacencyList<T>& e) { return e.vertex == v1; });
	auto e2 = std::find_if(this->adjacencyList.begin(), this->adjacencyList.end(),
			[&](const AdjacencyList<T>& e) { return e.vertex == v2; });
	
	if (e1 == this->adjacencyList.end()) {
		throw std::logic_error("isEdgeBetween, v1 vertex does not exist in adjacency list of graph.");
	}
	if (e2 == this->adjacencyList.end()) {
		throw std::logic_error("isEdgeBetween, v2 vertex does not exist in adjacency list of graph.");
	}

	auto requiredIndex = e2 - this->adjacencyList.begin();

	const auto founditerator = std::find(e1->edges.begin(), e1->edges.end(), requiredIndex);

	return founditerator != e1->edges.end();
}

template <class T>
const std::vector<AdjacencyList<T>>& Graph<T>::getAdjacencyList() const noexcept
{
	return this->adjacencyList;
}

} // namespace Graph