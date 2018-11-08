#include <graph/Vertex.hpp>

namespace Graph
{

template <class T>
Edge<T>::Edge(const Vertex<T>& des, uint64_t w):
    destination(des), weight(w), visited(false)
{
}

template <class T>
const Vertex<T>& Edge<T>::getDestination() const
{
    return this->destination;
}

} //namespace Graph