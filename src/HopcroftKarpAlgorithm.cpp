#include "HopcroftKarpAlgorithm.hpp"

#include <algorithm>
#include <queue>

/**
 * @brief Contains code for the boxnesting problem
 */
namespace BoxNesting
{
HopcroftKarpAlgorithm::HopcroftKarpAlgorithm(const std::vector<Box>& boxes)
{
	// In the boxes case left and right vertices are the same amount since
	// they are the amount of boxes
	this->leftVerticesCount = static_cast<int16_t>(boxes.size());
	this->rightVerticesCount = this->leftVerticesCount;

	this->NILL = this->leftVerticesCount;

	this->pairsLeft = std::vector<int16_t>(this->leftVerticesCount + 1, this->NILL);
	this->pairsRight = std::vector<int16_t>(this->rightVerticesCount + 1, this->NILL);
	this->distances = std::vector<int16_t>(this->leftVerticesCount + 1, 0);

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

int16_t HopcroftKarpAlgorithm::runAlgorithm() const
{
	// We have the same amount of visible boxes as there
	// are vertices in the left part of the bipartite graph
	// for each valid match (i.e. a box can nest inside another box)
	// we remove a visible box
	int16_t visibleBoxes = this->leftVerticesCount;

	while (bfs()) 
	{ 
		// Find a free vertex 
		for (int16_t i = 0; i < leftVerticesCount; ++i)
		{
			if (pairsLeft[i] == this->NILL && this->dfs(i))
			{
				--visibleBoxes;
			}
		}
	}

	return visibleBoxes;
}

bool HopcroftKarpAlgorithm::dfs(int16_t vertex) const
{
	if (vertex == this->NILL)
	{
		return true;
	}

	auto sz = this->graph[vertex].size();
	for (int16_t j = 0; j < sz; ++j)
	{ 
		// Follow the distances set by BFS 
		if (this->distances[this->pairsRight[j]] == this->distances[vertex] + 1) 
		{ 
			// If dfs for pair of v also returns 
			// true 
			if (dfs(this->pairsRight[j])) 
			{
				this->pairsRight[j] = vertex;
				this->pairsLeft[vertex] = j;
				return true; 
			} 
		} 
	} 

	// If there is no augmenting path beginning with u. 
	this->distances[vertex] = this->INFINITE; 
	return false; 
}

bool HopcroftKarpAlgorithm::bfs() const
{
	std::queue<int16_t> queue;

	// First layer of vertices (set distance as 0) 
	for (int16_t i = 0; i < this->leftVerticesCount; ++i) 
	{ 
		// If this is a free vertex, add it to queue 
		if (this->pairsLeft[i] == this->NILL) 
		{ 
			this->distances[i] = 0; 
			queue.push(i); 
		} 
		// Else set distance as infinite
		// so that this vertex 
		// is considered next time 
		else
		{
			this->distances[i] = this->INFINITE;
		}
	} 

	// Initialize distance to NIL as infinite 
	this->distances[this->NILL] = this->INFINITE;

	// the queue can only contain vertices off the left part of the bipartite graph  
	while (!queue.empty()) 
	{ 
		// Dequeue a vertex 
		auto i = queue.front(); 
		queue.pop(); 

		// If this node is not NIL and can provide a shorter path to NIL 
		if (this->distances[i] < this->distances[this->NILL]) 
		{ 
			// Get all adjacent vertices of the dequeued vertex u 
			auto sz = this->graph[i].size();
			for (int16_t j = 0; j < sz; ++j)
			{ 
				// If pair of v is not considered so far 
				// (v, pairV[V]) is not yet explored edge. 
				if (this->distances[this->pairsRight[j]] == this->INFINITE) 
				{ 
					// Consider the pair and add it to queue 
					this->distances[this->pairsRight[j]] = this->distances[i] + 1; 
					queue.push(this->pairsRight[j]); 
				} 
			} 
		} 
	} 

	// If we could come back to NIL using alternating path of distinct 
	// vertices then there is an augmenting path 
	return this->distances[this->NILL] != this->INFINITE; 
}

} // namespace BoxNesting