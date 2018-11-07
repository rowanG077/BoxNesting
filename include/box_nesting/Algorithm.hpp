#include <box_nesting/Box.hpp>
#include <graph/Graph.hpp>

/**
 * @brief Contains code for the boxnesting problem
 */
namespace BoxNesting
{
/**
 * @brief class that contains the boxnesting algorithm
 */
class Algorithm
{
public:
	/**
	 * @brief Construct a new Algorithm object with the default constructor
	 */
	Algorithm() = default;

	/**
	 * @brief function that runs the boxNesting algorithm and returns the number
	 * of visible boxes
	 *
	 * @param boxes the set of boxes to be nested
	 * @return uint32_t the number of visible boxes after running the nesting
	 * algorithm
	 */
	uint32_t runAlgorithm(const std::vector<Box>& boxes);

	/**
	 * @brief function that appends data to an empty graph given a set of boxes.
	 * Every box represents a
	 * vertex in the graph where an edge is appended from vertex a to b if the box
	 * representing vertex a
	 * nests inside the box representing vertex b
	 *
	 * @param graph the graph where the data will be stored in
	 * @param boxes the set of boxes that will be used to create the graph
	 */
	void createGraphFromBoxes(Graph::Graph<Box>& graph, const std::vector<Box>& boxes);
};

} // namespace BoxNesting