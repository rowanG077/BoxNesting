#include "Algorithm.hpp"

#include <algorithm>

/**
 * @brief Contains code for the boxnesting problem
 */
namespace BoxNesting
{
Algorithm::Algorithm(const std::vector<Box>& boxes)
{
	// In the boxes case left and right vertices are the same amount since
	// they are the amount of boxes
	this->leftVerticesCount = static_cast<int16_t>(boxes.size());
	this->rightVerticesCount = this->leftVerticesCount;

	this->pairsLeft = std::vector<int16_t>(this->leftVerticesCount, -1);
	this->pairsRight = std::vector<int16_t>(this->rightVerticesCount, -1);
	this->used = std::vector<bool>(this->leftVerticesCount, false);

	this->graph.resize(this->leftVerticesCount);
	for (int16_t i = 0; i < this->leftVerticesCount; ++i) {
		this->graph[i].reserve(this->rightVerticesCount);
		for (int16_t j = 0; j < this->rightVerticesCount; ++j) {
			if (boxes[i] < boxes[j]) {
				this->graph[i].emplace_back(j);
			}
		}
		this->graph[i].shrink_to_fit();
	}
}

int16_t Algorithm::runAlgorithm() const
{
	bool pathFound;
	do {
		fill(this->used.begin(), this->used.end(), false);
		pathFound = false;
		// remember to start only from free vertices which are not visited yet
		for (int16_t i = 0; i < this->leftVerticesCount; ++i) {
			if (this->pairsLeft[i] == -1 && !this->used[i]) {
				pathFound |= kuhn(i);
			}
		}
	} while (pathFound);

	// We have the same amount of visible boxes as there
	// are vertices in the left part of the bipartite graph
	// for each valid match (i.e. a box can nest inside another box)
	// we remove a visible box
	int16_t visibleBoxes = this->leftVerticesCount;
	for (int16_t i = 0; i < this->rightVerticesCount; ++i) {
		if (this->pairsRight[i] != -1) {
			--visibleBoxes;
		}
	}

	return visibleBoxes;
}

bool Algorithm::kuhn(int16_t vertex) const
{
	if (this->used[vertex]) {
		return false;
	}
	this->used[vertex] = true;

	auto sz = this->graph[vertex].size();
	for (int16_t i = 0; i < sz; ++i) {
		auto to = this->graph[vertex][i];
		if (this->pairsRight[to] == -1 || kuhn(this->pairsRight[to])) {
			this->pairsRight[to] = vertex;
			this->pairsLeft[vertex] = to;
			return true;
		}
	}
	return false;
}

} // namespace BoxNesting