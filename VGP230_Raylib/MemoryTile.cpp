#include "MemoryTile.h"
#include <string>

MemoryTile::MemoryTile(int row, int col, int GAP, int UI_HEIGHT, int tileSize, int gridSize, int num, int widthHeight)
{
	float gridWidth = gridSize * tileSize + (gridSize - 1) * GAP;
	float startX = (widthHeight - gridWidth) / 2;

	float x = startX + (tileSize + GAP) * col;
	float y = UI_HEIGHT + GAP + (tileSize + GAP) * row;

	rect = Rectangle{ x, y, (float)tileSize, (float)tileSize };
	this->number = num;
}

void MemoryTile::Draw() {

	std::string tileText = "";

	Vector2 cen = Vector2{
		rect.x + rect.width / 2,
		rect.y + rect.height / 2
	};

	Color bgColor = RAYWHITE;

	switch (status) {

	case MemoryTileStatus::Hidden:
		bgColor = RED;
		tileText = "?";
	break;

	case MemoryTileStatus::Flipped:
		bgColor = ORANGE;
		tileText = std::to_string(number);
	break;

	case MemoryTileStatus::Matched:
		bgColor = GREEN;
		tileText = ":D";
	break;

	default: break;
	}

	DrawRectangleRounded(rect, 0.2f, 8, bgColor);

	int textWidth = MeasureText(tileText.c_str(), fontSize);
	Vector2 txtOrigin = Vector2{
		cen.x - (float)textWidth / 2,
		cen.y - (float)fontSize / 2
	};

	DrawText(tileText.c_str(), txtOrigin.x, txtOrigin.y, fontSize, BLACK);
}