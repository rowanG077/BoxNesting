#include <graph/Graph.hpp>

#include <algorithm>

namespace Graph
{

template <class T>
void Graph<T>::addVertex(const Vertex<T>& vertex) 
{
	adjacencyList.insert(std::make_pair(vertex, Edges()));
}

template <class T>
void Graph<T>::addEdge(const Vertex<T>& v1, const Vertex<T>& v2)
{
	adjacencyList[v1].insert(v2);
	adjacencyList[v2].insert(v1);
}

template <class T>
bool Graph<T>::isEdgeBetween(const Vertex<T> &source, const Vertex<T> &destination) const
{
	const auto edges = adjacencyList.find(source);
	if (edges!= adjacencyList.end())
	{
		return edges->second.find(destination) != edges->second.end();
	}
	return false;
}

template <class T>
const std::unordered_map<Vertex<T>, std::unordered_set<Vertex<T>, VertexHash<T>>, VertexHash<T>>& Graph<T>::getAdjacencyList() const
{
	return this->adjacencyList;
}

} // namespace Graph