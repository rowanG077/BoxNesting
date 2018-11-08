namespace Graph
{

template <class T>
Vertex<T>::Vertex(uint64_t newId, T con): id(newId), content(std::move(con)), visited(false)
{
}

template <class T>
bool Vertex<T>::operator==(const Vertex<T>& rhs) const
{
    return id == rhs.getId();
}

template <class T>
void Vertex<T>::addEdge(const Vertex<T>& destination, uint64_t weight)
{
    Edge<T> edge(destination, weight);
    adjacencyList.push_back(edge);
}

template <class T>
const T& Vertex<T>::getContent() const
{
    return this->content;
}

template <class T>
const std::vector<Edge<T>>& Vertex<T>::getAdjacencyList() const
{
    return this->adjacencyList;
}

template <class T>
bool Vertex<T>::hasEdgeTo(const Vertex<T> &destination) const
{
    for (const auto& edge: this->adjacencyList)
    {
        if (edge.getDestination() == destination)
        {
            return true;
        }
    }
    return false;
}

template <class T>
uint64_t Vertex<T>::getId() const
{
    return this->id;
}

} //namespace Graph