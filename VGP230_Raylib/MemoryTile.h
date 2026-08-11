#pragma once
#include "raylib.h"
#include "MemoryTileStatus.h"
class MemoryTile
{
public:
	MemoryTile(int h, int v, int GAP, int UI_HEIGHT, int tileSize, int gridSize, int num, int widthHeight);

	Rectangle rect;
	int number;
	int fontSize = 60;

	MemoryTileStatus status = MemoryTileStatus::Hidden;

	void Draw();
};

