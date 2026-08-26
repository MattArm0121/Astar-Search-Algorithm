#include "AI.h"
#include <time.h>
#include <string>

Node* getUnblockedNode(std::vector<std::vector<Node>>& grid) {
	SetRandomSeed(time(0));
	int RandomRow, RandomCol;

	do {
		RandomRow = GetRandomValue(0, grid.size() - 1);
		RandomCol = GetRandomValue(0, grid[0].size() - 1);
	} while (grid[RandomRow][RandomCol].blocked);

	return &grid[RandomRow][RandomCol];
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

	// Let's block 20% of them
	int twentyPercent = grid.size() * grid[0].size() * 0.2;
	for (int i = 0; i < twentyPercent; i++)
		getUnblockedNode(grid)->blocked = true;

	// Start node
	start = getUnblockedNode(grid);
	start->blocked = true; start->fillColor = BLUE; start->txt = "S"; 
	// End node
	end = getUnblockedNode(grid);
	end->blocked = true; end->fillColor = GREEN; end->txt = "E";

	BFSSearch.push_back(start);
	searching = true;
}

void AI::Update() {
	for (auto row : grid)
		for (auto node : row)
			node.Draw();

	if (searching) {
		bfsTimer += GetFrameTime();
		if (bfsTimer >= bfsDelay) {
			bfsTimer = 0.0f;
			BFSSearchSteps();
		}
	}
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
	Node* currentNode = end;

	while (currentNode != nullptr) {
		if (currentNode != start && currentNode != end)
			currentNode->fillColor = YELLOW;
		currentNode = currentNode->parent;
	}
}
