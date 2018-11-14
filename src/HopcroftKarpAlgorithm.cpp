#include "HopcroftKarpAlgorithm.hpp"

#include <algorithm>
#include <queue>

/**
 * @brief Contains code for the boxnesting problem
 */
namespace BoxNesting
{

const int16_t HopcroftKarpAlgorithm::NILL = 0; // NOLINT, because of formatting
const int16_t HopcroftKarpAlgorithm::INF = std::numeric_limits<int16_t>::max(); // NOLINT, because of formatting

HopcroftKarpAlgorithm::HopcroftKarpAlgorithm(const std::vector<Box>& boxes)
{
	// In the boxes case the left and right vertices are the same amount since
	// they are the amount of boxes. Since it never exceeds 5000 we can easily
	// cast here
	this->leftVerticesCount = static_cast<int16_t>(boxes.size());
	this->rightVerticesCount = this->leftVerticesCount;

	this->graph.resize(this->leftVerticesCount + 1);

	// This algorithm actually only requires the adjacency list
	// of the left part of the graph so we only construct
	// that. This is because in our boxes case the partitions
	// contain the same amount of vertices.
	for (int16_t i = 1; i <= this->leftVerticesCount; ++i) {
		this->graph[i].reserve(this->rightVerticesCount + 1);
		for (int16_t j = 1; j <= this->rightVerticesCount; ++j) {
			if (boxes[i - 1] < boxes[j - 1]) {
				this->graph[i].emplace_back(j);
			}
		}
		this->graph[i].shrink_to_fit();
	}
}

int16_t HopcroftKarpAlgorithm::runAlgorithm() const
{
	this->pairsLeft = std::vector<int16_t>(this->leftVerticesCount + 1, NILL);
	this->pairsRight = std::vector<int16_t>(this->rightVerticesCount + 1, NILL);
	this->distances = std::vector<int16_t>(this->leftVerticesCount + 1, 0);

	// We have the same amount of visible boxes as there
	// are vertices in the left partition
	// for each valid match (i.e. a box can nest inside another box)
	// we remove a visible box
	int16_t visibleBoxes = this->leftVerticesCount;

	while (bfs()) 
	{ 
		// Find a free vertex 
		for (int16_t i = 1; i <= leftVerticesCount; ++i)
		{
			if (pairsLeft[i] == NILL && this->dfs(i))
			{
				--visibleBoxes;
			}
		}
	}

	return visibleBoxes;
}

bool HopcroftKarpAlgorithm::dfs(int16_t vertex) const
{
	// Path ends if it visits the NILL vertex
	// because we can't traverse anywhere from it
	// It is a shorter path because we we are allready
	// iterating through shorter paths.
	if (vertex == NILL)
	{
		return true;
	}

	for (auto j : this->graph[vertex])
	{ 
		// Follow the distances set by BFS 
		if (this->distances[this->pairsRight[j]] == this->distances[vertex] + 1) 
		{ 
			// If dfs for pair of v also returns 
			// true then it means the path ends at a
			// NILL which means it is the shortest math
			if (dfs(this->pairsRight[j])) 
			{
				// At the matching
				this->pairsRight[j] = vertex;
				this->pairsLeft[vertex] = j;
				return true; 
			} 
		} 
	} 

	// We set distance to infinite here so we can ensure it will
	// not be used in a future path. We allready know this is not
	// the shortest path so it doesn't make sense to check this vertex
	// again.
	this->distances[vertex] = INF; 
	// No paths where found to NILL so it isn't
	// the shortest path
	return false; 
}

bool HopcroftKarpAlgorithm::bfs() const
{
	std::queue<int16_t> queue;

	// Iterate through first layer of the graph from the left
	// partition of the bipartite graph. If there is a vertex
	// that doesn't have a pair we add it to the queue
	// since we can use that vertex to traverse.
	// If it allready has a pair we set the distance to
	// to infinite because we can traverse it later from
	// left part of the graph
	for (int16_t i = 1; i <= this->leftVerticesCount; ++i) 
	{ 
		if (this->pairsLeft[i] == NILL) 
		{ 
			this->distances[i] = 0; 
			queue.push(i); 
		} 
		else
		{
			this->distances[i] = INF;
		}
	}

	// If find a shortest augmented path we end at NILL and thus
	// the distance would become the length of the path
	// We use this information to eleminate path that are not the shortest
	// since we can allready see that any path that is longer then this
	// distance is not the shortest path.
	this->distances[NILL] = INF;

	// Continue traversing through the layers
	// While nodes in the partition are unmatched
	// or have a previous match. If that is not the case
	// the next vertex is NILL and we are getting there first
	// time this run
	while (!queue.empty()) 
	{ 
		auto i = queue.front(); 
		queue.pop(); 

		if (this->distances[i] < this->distances[NILL]) 
		{ 
			for (auto j : this->graph[i])
			{
				if (this->distances[this->pairsRight[j]] == INF) 
				{ 
					this->distances[this->pairsRight[j]] = this->distances[i] + 1; 
					queue.push(this->pairsRight[j]); 
				} 
			} 
		} 
	} 

	// If we could come back to NIL using alternating path of distinct 
	// vertices that is shorter then before then distance to null must
	// be set
	return this->distances[NILL] != INF; 
}

} // namespace BoxNesting