#pragma once
#include "raylib.h"
#include <vector>
#include "MemoryTile.h"

using namespace std;

class MemoryGame
{
public:

#define GAP 16
#define WAIT_TIME 0.5
#define UI_HEIGHT 100

	static const int widthHeight = 800;
	int gridSize = 4; // how many tiles in rows and columns

	vector<MemoryTile> tiles;

	bool compareMode = false;
	float timeOfSecondClick = -1.0f;

	MemoryTile* tile1 = nullptr; // Want to say nothing in it
	MemoryTile* tile2 = nullptr; // Want to say nothing in it

	float gameStartTime = 0.0f;
	float elapsedTime = 0.0f;
	bool gameFinished = false;

	Rectangle resetButton = { 16, 20, 120, 50 };

	float bestTime = -1.0f;

	void Main(); 
	void Start(); 
	void Update(); 

	void DrawUI();
};

