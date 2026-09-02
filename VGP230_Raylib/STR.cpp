#include "AI.h"
#include <algorithm>
#include <queue>
#include <vector>
#include <unordered_map>

void AI::STR(Node* start, Node* end) {
	strTracedPath.clear();
		for (auto& row : grid)
			for (auto& node : row)
				node.Reset();

	auto Heuristic = [](Node* a, Node* b) {
		return abs(a->row - b->row) + abs(a->col - b->col);
		};

	auto Compare = [](Node* a, Node* b) {
		return a->fCost > b->fCost ||
			(a->fCost == b->fCost && a->hCost > b->hCost);
		};

	std::priority_queue<Node*, std::vector<Node*>, decltype(Compare)> openSet(Compare);

	std::unordered_map<Node*, float> gScore;

	for (auto& row : grid)
		for (auto& node : row) {
			gScore[&node] = FLT_MAX;
		}

	gScore[start] = 0;

	start->visited = true;
	start->step = 0;
	start->gCost = 0;
	start->hCost = Heuristic(start, end);
	start->fCost = start->gCost + start->hCost;

	openSet.push(start);

	while (!openSet.empty()) {

		Node* current = openSet.top();
		openSet.pop();

		if (current->atTheSameSpot(*end)) {
			while (current != nullptr) {
				strTracedPath.push_back(current);
				current = current->parent;
			}
			std::reverse(strTracedPath.begin(), strTracedPath.end());

			for (Node* node : strTracedPath) {
				if (node != start && node != end) {
					node->fillColor = aStarColor;
					//node->blocked = true;
					node->path = true;
				}
			}
			return;
		}

		for (Node* neighbor : GetNeighbors(current)) {
			if (neighbor->blocked && neighbor != end)
				continue;

			float movementCost = GetNodeCost(neighbor);
			float tentativeCost = current->gCost + movementCost;

			if (tentativeCost < gScore[neighbor]) {
				neighbor->parent = current;
				gScore[neighbor] = tentativeCost;

				neighbor->gCost = tentativeCost;
				neighbor->hCost = Heuristic(neighbor, end);
				neighbor->fCost = neighbor->gCost + neighbor->hCost;

				neighbor->step = current->step + 1;
				if (neighbor != end) 
					neighbor->txt = std::to_string(neighbor->step);
				//neighbor->visited = true;
				openSet.push(neighbor);
			}
		}
	}
}
