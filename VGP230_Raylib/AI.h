#pragma once
#include "raylib.h"
#include <vector>
#include <string>

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

	void Draw() {
		if (blocked)
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

	void Main(); 
	void Start(); 
	void Update(); 

	std::vector<Node*> GetNeighbors(Node* node);

	void BFSNeighbor(Node* node);
	void BFSSearchSteps();
	void ShowFinalPath();
};