#include "AI.h"
#include <time.h>
#include <string>
#include <algorithm>
#include <cmath>

Node* getUnblockedNode(std::vector<std::vector<Node>>& grid) {
	int RandomRow, RandomCol;

	do {
		RandomRow = GetRandomValue(0, grid.size() - 1);
		RandomCol = GetRandomValue(0, grid[0].size() - 1);
	} while (grid[RandomRow][RandomCol].blocked);

	return &grid[RandomRow][RandomCol];
}

Node* getHotspotCenter(std::vector<std::vector<Node>>& grid, int radius)
{
	Node* node;

	do
	{
		node = getUnblockedNode(grid);
	} while (node->row - radius < 0 ||
		node->row + radius >= grid.size() ||
		node->col - radius < 0 ||
		node->col + radius >= grid[0].size());

	return node;
}

void AI::Main() {
	Start();

	int width = COLS * NODE_SIZE;
	int height = ROWS * NODE_SIZE;

	InitWindow(width, height, "AI pathing learning");
	SetTargetFPS(60);

	while (!WindowShouldClose()) {
		BeginDrawing();
		ClearBackground(RAYWHITE);

		Update();

		EndDrawing();
	}
}

void AI::Start() {
	SetRandomSeed(time(0));

	grid.clear();

	for (int row = 0; row < ROWS; row++) 
	{
		std::vector<Node> rowNodes;
		float y = NODE_SIZE * row;
		for (int col = 0; col < COLS; col++) 
		{
			float x = NODE_SIZE * col;

			Node(node) = Node(row, col, { x, y }, { NODE_SIZE, NODE_SIZE }, DARKGRAY);
			rowNodes.push_back(node);
		}
		grid.push_back(rowNodes);
	}

	// Let's block 25% of them
	int twentyfivePercent = grid.size() * grid[0].size() * 0.25;
	for (int i = 0; i < twentyfivePercent; i++)
		getUnblockedNode(grid)->blocked = true;

	// Start node
	start = getUnblockedNode(grid);
	start->blocked = true; start->fillColor = BLUE; start->txt = "S"; 
	// End node
	end = getUnblockedNode(grid);
	end->blocked = true; end->fillColor = GREEN; end->txt = "E";

	hotspots.clear();
	for (int i = 0; i < 5; i++) {
		int radius = 3;
		Node* hotspot = getHotspotCenter(grid, radius);
		hotspots.push_back(Hotspot(hotspot->row, hotspot->col, radius, 5));

		for (int row = hotspot->row - radius; row <= hotspot->row + radius; row++)
		{
			for (int col = hotspot->col - radius; col <= hotspot->col + radius; col++)
			{
				int rowDistance = row - hotspot->row;
				int colDistance = col - hotspot->col;

				float distance = sqrtf(rowDistance * rowDistance + colDistance * colDistance);

				if (distance <= radius)
				{
					if (!grid[row][col].blocked)
					{
						grid[row][col].hotspot = true;
						if (&grid[row][col] != start && &grid[row][col] != end)
						{
							grid[row][col].fillColor = RED;
						}
					}
				}
			}
		}
	}

	STR(start, end);
	//BFSSearch.push_back(start);
}

void AI::Update() {
	for (auto row : grid)
		for (auto node : row)
			node.Draw();

	/*
	if (searching) {
		bfsTimer += GetFrameTime();
		if (bfsTimer >= bfsDelay) {
			bfsTimer = 0.0f;
			BFSSearchSteps();
		}
	}
	else if (showingPath) {
		pathTimer += GetFrameTime();
		if (pathTimer >= pathDelay) {
			pathTimer = 0.0f;

			if (pathIndex < finalPath.size()) {
				Node* node = finalPath[pathIndex];

				if (node != start && node != end) 
					node->fillColor = YELLOW;
				
				pathIndex++;
			}
			else {
				showingPath = false;
			}
		}
	}
	*/
}

std::vector<Node*> AI::GetNeighbors(Node* node)
{
	std::vector<Node*> neighbors;

	auto isWithinGrid = [&](int row, int col) -> bool
		{
			return row >= 0 &&
				col >= 0 &&
				row < ROWS &&
				col < COLS;
		};

	if (isWithinGrid(node->row - 1, node->col))
		neighbors.push_back(&grid[node->row - 1][node->col]); // Above

	if (isWithinGrid(node->row + 1, node->col))
		neighbors.push_back(&grid[node->row + 1][node->col]); // Below

	if (isWithinGrid(node->row, node->col - 1))
		neighbors.push_back(&grid[node->row][node->col - 1]); // Left

	if (isWithinGrid(node->row, node->col + 1))
		neighbors.push_back(&grid[node->row][node->col + 1]); // Right

	return neighbors;
}

float AI::GetNodeCost(Node* node)
{
	float cost = 1.0f;

	for (const Hotspot& hotspot : hotspots)
	{
		int rowDistance = abs(node->row - hotspot.row);
		int colDistance = abs(node->col - hotspot.col);
		float distance = sqrtf(rowDistance * rowDistance +colDistance * colDistance);

		if (distance > hotspot.radius)
			continue;

		float intensity = 1.0f - (distance / hotspot.radius);
		float hotspotCost = 1.0f + (hotspot.maxCost - 1.0f) * intensity;

		cost = std::max(cost, hotspotCost);
	}

	return cost;
}


/*
void AI::BFSNeighbor(Node* node) {
	// Looking at all four neighbors now
	std::vector<Node*> neighbors = GetNeighbors(node);

	for (Node* neighbor : neighbors) {
		// Wall check
		if (neighbor->blocked && neighbor != end)
			continue;
		// Visited check
		if (neighbor->visited)
			continue;

		neighbor->visited = true;
		neighbor->blocked = true;
		neighbor->parent = node;
		if (neighbor != end) {
			neighbor->fillColor = SKYBLUE;
			neighbor->txt = std::to_string(BFSCount);
		}
		BFSSearch.push_back(neighbor);
	}
}

void AI::BFSSearchSteps()
{
	for (int i = 0; i < BFSSearch.size(); i++) {
		Node* currentNode = BFSSearch[i];

		// Checking if end was found
		if (currentNode == end) {
			ShowFinalPath();
			searching = false; return;
		}

		// For each step search
		if (currentNode->txt == std::to_string(BFSCount - 1)) 
			BFSNeighbor(currentNode);

		// If it is start
		if (currentNode == start)
			BFSNeighbor(currentNode);
	}
	BFSCount++;
}

void AI::ShowFinalPath()
{
	finalPath.clear();

	Node* currentNode = end;

	while (currentNode != nullptr) {
		finalPath.push_back(currentNode);
		currentNode = currentNode->parent;
	}

	std::reverse(finalPath.begin(), finalPath.end());
	showingPath = true;
}
*/