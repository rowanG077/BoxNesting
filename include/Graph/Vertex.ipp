namespace Graph
{

template <class T>
uint16_t Vertex<T>::idCounter = 0;

template <class T>
Vertex<T>::Vertex(T con): id(++idCounter), content(std::move(con))
{
}

template <class T>
bool Vertex<T>::operator==(const Vertex<T>& rhs) const
{
    return this->id == rhs.getId();
}

template <class T>
const T& Vertex<T>::getContent() const
{
    return this->content;
}

template <class T>
uint16_t Vertex<T>::getId() const
{
    return this->id;
}

} //namespace Graph