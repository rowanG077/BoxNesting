#ifndef EDGE_HPP
#define EDGE_HPP

/**
 * @brief Contains generic code that represents a graph and its properties
 */
namespace Graph {

template <class T> class Vertex;

/**
 * @brief template class representing an edge
 */
template <class T> class Edge {
public:
  /**
   * @brief Construct a new Edge object
   *
   * @param des the destination vertex of the edge
   * @param w the edge weight to be set
   */
  Edge(const Vertex<T> &des, double w);

  /**
   * @brief Get the Destination vertex
   *
   * @return const Vertex<T>& reference to the destination object
   */
  const Vertex<T> &getDestination() const;

  /**
   * @brief Getter for the weight of the edge
   *
   * @return double the edge weight
   */
  double getWeight() const;

  /**
   * @brief Getter for the visited status of the edge
   *
   * @return true if the edge has been visited
   * @return false if the edge has not been visited
   */
  bool isVisited() const;

private:
  /**
   * @brief a reference to the destination vertex
   */
  const Vertex<T> &destination;
  /**
   * @brief the edge weight
   */
  double weight;
  /**
   * @brief true if the edge has been visited
   */
  bool visited;
};

} // namespace Graph

#include <graph/Edge.ipp>

#endif // EDGE_HPP