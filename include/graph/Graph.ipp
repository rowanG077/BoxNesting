#include <algorithm>

namespace Graph
{

template <class T>
void Graph<T>::addVertex(const T& info) 
{
	Vertex<T> vertex(idCounter, info);
	vertices.push_back(vertex);
	idCounter ++;
}

template <class T>
void Graph<T>::addEdge(Vertex<T>& source, const Vertex<T>& destination, double weight)
{
	source.addEdge(destination, weight);
}

template <class T>
std::vector<Vertex<T>>& Graph<T>::getVertices()
{
	return this->vertices;
}

template <class T>
bool Graph<T>::isEdgeBetween(const Vertex<T> &source, const Vertex<T> &destination) const
{
	auto foundVertex = std::find(vertices.begin(), vertices.end(), source);
	return (foundVertex == vertices.end() ? false : foundVertex->hasEdgeTo(destination));
}

} // namespace Graph