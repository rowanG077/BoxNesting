#include <graph/Graph.hpp>

#include <algorithm>
#include <exception>

namespace Graph
{

template <class T>
void Graph<T>::addVertex(const Vertex<T>& vertex) 
{
	adjacencyList.emplace_back(
		AdjacencyList<T>{std::make_pair(vertex, std::vector<std::uint16_t>())}
	);
}

template <class T>
void Graph<T>::addEdge(const Vertex<T>& v1, const Vertex<T>& v2)
{
	auto e1 = std::find_if(this->adjacencyList.begin(), this->adjacencyList.end(),
			[&](const AdjacencyList<T>& e) { return e.content.first == v1; });
	auto e2 = std::find_if(this->adjacencyList.begin(), this->adjacencyList.end(),
			[&](const AdjacencyList<T>& e) { return e.content.first == v2; });
	
	if (e1 == adjacencyList.end()) {
		throw std::logic_error("addEdge, v1 vertex does not exist in adjacency list of graph.");
	}
	if (e2 == adjacencyList.end()) {
		throw std::logic_error("addEdge, v2 vertex does not exist in adjacency list of graph.");
	}

	e1->content.second.emplace_back(e2 - this->adjacencyList.begin());
	e2->content.second.emplace_back(e1 - this->adjacencyList.begin());
}

template <class T>
bool Graph<T>::isEdgeBetween(const Vertex<T> &v1, const Vertex<T> &v2) const
{
	auto e1 = std::find_if(this->adjacencyList.begin(), this->adjacencyList.end(),
			[&](const AdjacencyList<T>& e) { return e.content.first == v1; });
	auto e2 = std::find_if(this->adjacencyList.begin(), this->adjacencyList.end(),
			[&](const AdjacencyList<T>& e) { return e.content.first == v2; });
	
	if (e1 == adjacencyList.end()) {
		throw std::logic_error("isEdgeBetween, v1 vertex does not exist in adjacency list of graph.");
	}
	if (e2 == adjacencyList.end()) {
		throw std::logic_error("isEdgeBetween, v2 vertex does not exist in adjacency list of graph.");
	}

	auto requiredIndex = e2 - this->adjacencyList.begin();

	const auto founditerator = std::find(e1->content.second.begin(), e1->content.second.end(), requiredIndex);

	return founditerator != e1->content.second.end();
}

template <class T>
const std::vector<AdjacencyList<T>>& Graph<T>::getAdjacencyList() const noexcept
{
	return this->adjacencyList;
}

} // namespace Graph