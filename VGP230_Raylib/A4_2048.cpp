#include "A4_2048.h"
#include <string>

// Render loop of the game
void A4_2048::Main() {
	Start();

	InitWindow(screenWidth, screenHeight, "2048 Game");
	SetTargetFPS(60);

	while (!WindowShouldClose()) {
		BeginDrawing();
		ClearBackground(RAYWHITE);

		Update();

		EndDrawing();
	}
}

void A4_2048::Start() {
	for (int i = 0; i < 4; i++) {
		for (int j = 0; j < 4; j++) {
			GridTile tle = GridTile(i, j);
			grid.push_back(tle);
		}
	}

	for (int i = 0; i < 3; i++) {
		PlayingTile tle = PlayingTile(GetRandomValue(0, 3), GetRandomValue(0, 3));
		tiles.push_back(tle);
	}
}

void A4_2048::Update() {


	for (int i = 0; i < tiles.size(); i++) {
		tiles[i].Draw();
	}
	for (int i = 0; i < grid.size(); i++) {
		grid[i].Draw();
	}
}