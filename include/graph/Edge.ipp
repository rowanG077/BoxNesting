#include <graph/Vertex.hpp>

namespace Graph
{

template <class T>
Edge<T>::Edge(const Vertex<T>& des, double w):
    destination(des), weight(w)
{
}

template <class T>
const Vertex<T>& Edge<T>::getDestination() const
{
    return this->destination;
}

} //namespace Graph