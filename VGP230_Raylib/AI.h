#pragma once
#include "raylib.h"
#include <vector>
#include <string>
#include <float.h>

struct Hotspot
{
	int row;
	int col;
	int radius;
	float maxCost;


	Hotspot(int r, int c, int rad, float cost)
		: row(r), col(c), radius(rad), maxCost(cost) {

	}
};

struct Node
{
	int row, col;
	Vector2 position;
	Vector2 size;
	Color fillColor = GRAY;
	Color outlineColor;

	bool blocked = false;
	bool visited = false;
	Node* parent = nullptr;

	std::string txt = "";

	Node(int r, int c, Vector2 pos, Vector2 sze, Color OutLine) {
		this->row = r;
		this->col = c;
		this->position = pos;
		this->size = sze;
		this->outlineColor = OutLine;
	}

	float gCost = FLT_MAX;
	float hCost = FLT_MAX;
	float fCost = FLT_MAX;

	int step = -1;

	bool hotspot = false;
	bool path = false;

	void Draw() {
		if (blocked || hotspot || path)
			DrawRectangleV(position, size, fillColor);

		DrawRectangleLines(position.x,
			position.y,
			size.x,
			size.y,
			outlineColor);

		int textHeight = 20;
		int textWidth = MeasureText(txt.c_str(), textHeight);
		float textX = position.x + size.x / 2 - textWidth / 2;
		float textY = position.y + size.y / 2 - textHeight / 2;
		DrawText(txt.c_str(), textX, textY, textHeight, BLACK);
	}

	void Reset() {
		visited = false;
		parent = nullptr;
		step = -1;

		gCost = FLT_MAX;
		hCost = FLT_MAX;
		fCost = FLT_MAX;
	}

	bool atTheSameSpot(const Node& other) const
	{
		return row == other.row && col == other.col;
	}
};

class AI
{
public:
#define ROWS 20
#define COLS 40
#define NODE_SIZE 50

	std::vector<std::vector<Node>> grid;
	Node* start;
	Node* end;

	float bfsTimer = 0.0f; float bfsDelay = 0.5f;

	std::vector<Node*> BFSSearch;

	bool searching; int BFSCount = 1;

	// Final path stuff
	float pathTimer = 0.0f; float pathDelay = 0.1f;
	std::vector<Node*> finalPath;
	bool showingPath = false;
	int pathIndex = 0;

	void Main(); 
	void Start(); 
	void Update(); 

	std::vector<Node*> GetNeighbors(Node* node);

	std::vector<Hotspot> hotspots;

	float GetNodeCost(Node* node);

	// Assignment stuff - Breadth First Search
	//void BFSNeighbor(Node* node);
	//void BFSSearchSteps();
	//void ShowFinalPath();

	// Depth first search
	//void DFS(Node* start, Node* end);
	//std::vector<Node*> dfsTracedPath;

	// Djikstra first search
	//void DJK(Node* start, Node* end);
	//std::vector<Node*> djkTracedPath;

	// Astar first search
	void STR(Node* start, Node* end);
	std::vector<Node*> strTracedPath;
	Color aStarColor = Color{ 200, 200, 0, 100 };
};