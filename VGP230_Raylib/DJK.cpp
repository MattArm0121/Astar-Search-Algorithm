#include "AI.h"
#include <algorithm>
#include <queue>

/*
void AI::DJK(Node* start, Node* end) {
	djkTracedPath.clear();

	for (auto& row : grid)
		for (auto& node : row)
			node.Reset();

	struct Compare {
		bool operator()(Node* a, Node* b) const {
			return a->gCost > b->gCost;
		}
	};

	std::priority_queue<Node*, std::vector<Node*>> openSet;

	openSet.push(start);
	start->visited = true;
	start->txt = std::to_string(0);

	while (!openSet.empty()) {
		Node* current = openSet.top();

		openSet.pop();

		if (current->atSameSpot)


		for (Node* neighbor : GetNeighbors(current)) {
			if (neighbor->visited || neighbor->blocked)
				continue;

			float tentativeCost = current->gCost + 1;

			neighbor->visited = true;
			neighbor->parent = current;
			neighbor->txt = std::to_string(current->step + 1);
		}
	}
}
*/