#include <algorithm>

namespace Graph
{

template <class T>
void Graph<T>::addVertex(const T& info) 
{
	Vertex<T> vertex(idCounter, info);
	vertices.push_back(vertex);
	++ idCounter;
}

template <class T>
void Graph<T>::addEdge(const Vertex<T>& source, const Vertex<T>& destination, uint64_t weight)
{
	for (auto& vertex: vertices) {
		if (source == vertex) {
			vertex.addEdge(destination, weight);
		}
	}
}

template <class T>
const std::vector<Vertex<T>>& Graph<T>::getVertices() const
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