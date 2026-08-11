#include "MemoryGame.h"
void MemoryGame::Main() {
	Start();

	InitWindow(widthHeight, widthHeight, "Memory Game");
	SetTargetFPS(60);

	while (!WindowShouldClose()) {
		BeginDrawing();
		ClearBackground(RAYWHITE);

		Update();

		EndDrawing();
	}
}

void MemoryGame::Start() {
	tiles.clear();

	tile1 = nullptr;
	tile2 = nullptr;
	compareMode = false;
	gameFinished = false;
	gameStartTime = GetTime();
	elapsedTime = 0.0f;

	int totalSpaceForTiles = widthHeight - UI_HEIGHT - (gridSize+1) * GAP;
	int tileSize = totalSpaceForTiles / gridSize;

	std::vector<int> numbers;
	for (int i = 1; i <= gridSize * gridSize / 2; i++) {
		numbers.push_back(i);
		numbers.push_back(i);
	}

	for (int row = 0; row < gridSize; row++) {
		for (int col = 0; col < gridSize; col++) {
			int index = GetRandomValue(0, numbers.size() - 1);
			int num = numbers[index];

			MemoryTile tile = MemoryTile(row, col, GAP, UI_HEIGHT, tileSize, gridSize, num, widthHeight);
			tiles.push_back(tile);

			numbers.erase(numbers.begin() + index);
		}
	}
}

void MemoryGame::Update() {
	if (!gameFinished)
		elapsedTime = GetTime() - gameStartTime;

	if (CheckCollisionPointRec(GetMousePosition(), resetButton) && IsMouseButtonPressed(MOUSE_LEFT_BUTTON))
	{
		Start();
		return;
	}

	if (IsMouseButtonPressed(MOUSE_LEFT_BUTTON) && !compareMode) {
		Vector2 mouse = GetMousePosition();
		for (int i = 0; i < tiles.size(); i++) {
			if (CheckCollisionPointRec(mouse, tiles[i].rect)) {
				// Checking if clicked on one matched already
				if (tiles[i].status == MemoryTileStatus::Matched)
					continue;
				// Checking if clicking on same tile
				if (&tiles[i] == tile1)
					continue;

				tiles[i].status = MemoryTileStatus::Flipped;

				if (tile1 == nullptr)
					tile1 = &tiles[i];
				else
				{
					tile2 = &tiles[i];
					timeOfSecondClick = GetTime();
					compareMode = true;
				}
				break;
			}
		}
	}

	if (compareMode) {
		if (GetTime() > timeOfSecondClick + WAIT_TIME) {
			if (tile1->number == tile2->number)
				tile1->status = tile2->status = MemoryTileStatus::Matched;
			else
				tile1->status = tile2->status = MemoryTileStatus::Hidden;

			tile1 = tile2 = nullptr;
			compareMode = false;
		}
	}

	int matchedTiles = 0;

	for (MemoryTile tile : tiles) {
		tile.Draw();
		if (tile.status == MemoryTileStatus::Matched)
			matchedTiles++;
	}

	if (matchedTiles == tiles.size() && !gameFinished) {
		gameFinished = true;

		if (bestTime == -1.0f || elapsedTime < bestTime)
			bestTime = elapsedTime;
	}

	DrawUI();
}

void MemoryGame::DrawUI()
{
	// Background
	DrawRectangle(0, 0, widthHeight, UI_HEIGHT, BLACK);

	DrawRectangleRounded(resetButton, 0.2f, 8, BLUE);
	DrawText("RESET", 40, 32, 24, WHITE);

	DrawText(TextFormat("TIME: %.2f", elapsedTime), 200, 30, 30, WHITE);

	if (gameFinished) {
		DrawText("GAME WON!", 400, 30, 30, WHITE);
	}

	if (bestTime >= 0) {
		DrawText(TextFormat("BEST: %.2f", bestTime), 600, 30, 30, WHITE);
	}
	else {
		DrawText("BEST: --", 600, 30, 30, WHITE);
	}
}
